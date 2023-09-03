#include <unistd.h>
#include <errno.h>
#include <functional>
#include <thread>
#include <iostream>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#include "key_interceptor.h"
#include "keycodes.h"

using std::cout, std::endl;

extern int errno;

CGEventRef key_interceptor_callback(CGEventTapProxy proxy, CGEventType event_type, CGEventRef event, void *data) {
    int64_t code = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    KeyInterceptor *ki = (KeyInterceptor*) data;
    //if (code >= ki->actions.size()) return event;
    cout << "Pressed code: " << code << endl;
    char notification_code = 'N';
    write(ki->notification_write_fd, &notification_code, 1);
    //auto action = ki->actions[code];
    //if (action == nullptr) return event;
    //action();
    return event;
}

KeyInterceptor::KeyInterceptor() {}

KeyInterceptor::~KeyInterceptor() {
    this->disable();
}

int KeyInterceptor::start() {
    if (this->started) return -1;
    CGEventMask mask(1 << kCGEventKeyDown);
    this->port = CGEventTapCreate(kCGHIDEventTap,
                                  kCGHeadInsertEventTap,
                                  kCGEventTapOptionDefault,
                                  mask, &key_interceptor_callback, this);
    if (!this->port) {
        throw std::runtime_error("Failed to create key down event tap!");
    }
    int pipe_fds[2];
    if (pipe(pipe_fds) < 0) {
        throw std::runtime_error("Failed to create event notification pipe!");
    }
    this->notification_read_fd = pipe_fds[0];
    this->notification_write_fd = pipe_fds[1];
    std::thread rlt([this]() {
        CGEventTapEnable(this->port, true);
        CFRunLoopSourceRef rls = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, this->port, 0);
        CFRunLoopAddSource(CFRunLoopGetCurrent(), rls, kCFRunLoopCommonModes);
        CFRunLoopRun();
    });
    rlt.detach();
    this->started = true;
    return this->notification_read_fd;
}

void KeyInterceptor::disable() {
    this->started = false;
}

bool KeyInterceptor::is_active() {
    return false;
}

int KeyInterceptor::interceptor_fd() {
    //return this->kq_fd;
    return this->notification_read_fd;
}

void KeyInterceptor::add_intercept_action(Keycode code, std::function<void(void)> action_cb) {
    if (code >= this->actions.size()) {
        this->actions.resize(code + 1, nullptr);
    }
    this->actions[code] = action_cb;
}

void KeyInterceptor::remove_intercept_action(Keycode code) {}

