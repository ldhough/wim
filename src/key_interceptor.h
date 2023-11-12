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

class KeyInterceptor : public EventInterceptor<KeyInterceptor> {
    private:
        std::vector<std::function<void(void)>> actions;
#if defined(__MACH__)
        CFMachPortRef port;
//		int notification_read_fd;
//		int notification_write_fd;
//		bool started = false;
        friend CGEventRef key_interceptor_callback(CGEventTapProxy, CGEventType, CGEventRef, void*);
#endif
    public:
        KeyInterceptor();
        ~KeyInterceptor();
//        int start();
        int _start_internal();
        void disable();
        bool is_active();
        //int interceptor_fd();
        void add_intercept_action(Keycode, std::function<void(void)>);
        void remove_intercept_action(Keycode);
};

#endif /* KEY_INTERCEPTOR_H */
