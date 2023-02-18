#include <iostream>
#include <vector>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#include "pid_observer.h"

std::vector<pid_t> PidObserver::get_window_pids() {
    std::vector<pid_t> v;
    auto options = kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements;
    CFArrayRef window_info = CGWindowListCopyWindowInfo(options, kCGNullWindowID);
    CFIndex window_count = CFArrayGetCount(window_info);
    v.reserve(window_count);
    for (CFIndex idx = 0; idx < window_count; idx++) {
        CFDictionaryRef window_data = (CFDictionaryRef) CFArrayGetValueAtIndex(window_info, idx);
        CFNumberRef pid_num_ref = (CFNumberRef) CFDictionaryGetValue(window_data, kCGWindowOwnerPID);
        CFNumberRef layer_num_ref = (CFNumberRef) CFDictionaryGetValue(window_data, kCGWindowLayer);
        pid_t window_pid;
        int window_layer = -1;
        bool success = CFNumberGetValue(pid_num_ref, kCFNumberSInt32Type, &window_pid);
        bool success_2 = CFNumberGetValue(layer_num_ref, kCFNumberSInt32Type, &window_layer);
        // window layer 0 is standard window level
        if (success && success_2 && window_layer == 0) {
            v.push_back(window_pid);
        }
    }
    return v;
}




