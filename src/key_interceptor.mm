#include <functional>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#include "key_interceptor.h"
#include "keycodes.h"

CGEventRef key_interceptor_callback(CGEventTapProxy proxy, CGEventType event_type, CGEventRef event, void *data) {
    int64_t code = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    KeyInterceptor *ki = (KeyInterceptor*) data;
    if (code >= ki->actions.size()) return event;
    auto action = ki->actions[code];
    if (action == nullptr) return event;
    action();
    return nullptr;
}

KeyInterceptor::KeyInterceptor() {}

KeyInterceptor::~KeyInterceptor() {
    this->disable();
}

void KeyInterceptor::start() {
    CGEventMask mask(1 << kCGEventKeyDown);
    this->port = CGEventTapCreate(kCGHIDEventTap, kCGHeadInsertEventTap, kCGEventTapOptionDefault, mask, &key_interceptor_callback, this);
}

void KeyInterceptor::disable() {}

bool KeyInterceptor::is_active() {
    return false;
}

void KeyInterceptor::add_intercept_action(Keycode code, std::function<void(void)> action_cb) {
    if (code >= this->actions.size()) {
        this->actions.resize(code + 1, nullptr);
    }
    this->actions[code] = action_cb;
}

void KeyInterceptor::remove_intercept_action(Keycode code) {}

