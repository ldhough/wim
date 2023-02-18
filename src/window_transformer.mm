#import <ApplicationServices/ApplicationServices.h>
#include "window_transformer.h"
#include "utils.h"

WindowTransformer::WindowTransformer(pid_t pid) : pid(pid) {
    AXUIElementRef accessibility_app = AXUIElementCreateApplication(pid);
    CFTypeRef *window_data = nullptr;
    AXError error = AXUIElementCopyAttributeValue(accessibility_app, kAXWindowsAttribute, window_data);
    switch (error) {
        case kAXErrorAPIDisabled:
            log_error("Assistive applications are not enabled in System Preferences.");
            break;
        default:
            break;
    };

}

void WindowTransformer::move(float delta_x, float delta_y) {}

void WindowTransformer::resize(float width, float height) {}

void WindowTransformer::set_position(float x, float y) {}
