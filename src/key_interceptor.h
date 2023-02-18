#ifndef KEY_INTERCEPTOR_H
#define KEY_INTERCEPTOR_H

#include <vector>
#include <functional>

#if defined(__MACH__)
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#endif

#include "keycodes.h"

class KeyInterceptor {
    private:
        std::vector<std::function<void(void)>> actions;
#if defined(__MACH__)
        CFMachPortRef port;
        friend CGEventRef key_interceptor_callback(CGEventTapProxy, CGEventType, CGEventRef, void*);
#endif
    public:
        KeyInterceptor();
        ~KeyInterceptor();
        void start();
        void disable();
        bool is_active();
        void add_intercept_action(Keycode, std::function<void(void)>);
        void remove_intercept_action(Keycode);
};

#endif /* KEY_INTERCEPTOR_H */
