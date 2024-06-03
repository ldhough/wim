#include <unistd.h>
#include <errno.h>
#include <functional>
#include <thread>
#include <iostream>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#include "key_interceptor.h"
#include "event_interceptor.h"
#include "keycodes.h"

using std::cout, std::endl;

extern int errno;

CGEventRef key_interceptor_callback(CGEventTapProxy proxy, CGEventType event_type, CGEventRef event, void *data) {
    int64_t code = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    KeyInterceptor *ki = (KeyInterceptor*) data;
    char notification_code = (char) code;
    ki->__write(&notification_code);
    return event;
}

KeyInterceptor::KeyInterceptor() {}

KeyInterceptor::~KeyInterceptor() {}

bool KeyInterceptor::_start_internal() {
    if (this->started) return false;
    CGEventMask mask(1 << kCGEventKeyDown);
    this->port = CGEventTapCreate(kCGHIDEventTap,
                                  kCGHeadInsertEventTap,
                                  kCGEventTapOptionDefault,
                                  mask, &key_interceptor_callback, this);
    if (!this->port) {
        throw std::runtime_error("Failed to create key down event tap!");
    }
    std::thread rlt([this]() {
        CGEventTapEnable(this->port, true);
        CFRunLoopSourceRef rls = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, this->port, 0);
        CFRunLoopAddSource(CFRunLoopGetCurrent(), rls, kCFRunLoopCommonModes);
        CFRunLoopRun();
    });
    rlt.detach();
    return true;
}

bool KeyInterceptor::_stop_internal() {
    // TODO: implement
    return false;
}
