#ifndef WINDOW_TRANSFORMER_H
#define WINDOW_TRANSFORMER_H

#include <utility>

#if defined(__MACH__)
#import <ApplicationServices/ApplicationServices.h>
#endif

class WindowTransformer {
    private:
        const pid_t pid;
#if defined(__MACH__)
        AXUIElementRef window_element;
#endif
    public:
        WindowTransformer(pid_t);
        void move(float, float);
        void resize(float, float);
        void set_position(float, float);
};

#endif /* WINDOW_TRANSFORMER_H */
