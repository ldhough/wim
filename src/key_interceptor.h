#ifndef KEY_INTERCEPTOR_H
#define KEY_INTERCEPTOR_H

#include <vector>
#include <functional>
#include "event_interceptor.h"

#if defined(__MACH__)
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#endif

#include "keycodes.h" // TODO: figure out why putting this before Foundation/CG includes breaks build

class KeyInterceptor : public EventInterceptor<KeyInterceptor, Keycode> {
    private:
#if defined(__MACH__)
        CFMachPortRef port;
        friend CGEventRef key_interceptor_callback(CGEventTapProxy, CGEventType, CGEventRef, void*);
#endif
    public:
        KeyInterceptor();
        ~KeyInterceptor();
        bool _start_internal();
        bool _stop_internal();
};

#endif /* KEY_INTERCEPTOR_H */
