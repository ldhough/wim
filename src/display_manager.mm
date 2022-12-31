#include <iostream>
#include <vector>
#include <cstdint>
#import <CoreGraphics/CoreGraphics.h>
#include "display_manager.h"

#define MAX_DISPLAYS 16

using std::vector, std::cout, std::cerr, std::endl;

vector<uint32_t> DisplayManager::get_display_ids() {
    uint32_t *online = (uint32_t*) calloc(MAX_DISPLAYS, sizeof(uint32_t));
    uint32_t display_count;
    auto result = CGGetOnlineDisplayList(MAX_DISPLAYS, online, &display_count);
    if (result != 0) {
        cerr << "Error: Couldn't get list of active displays!" << endl;
    }
    vector<uint32_t> v;
    v.insert(v.end(), &online[0], &online[display_count]);
    free(online);
    return v;
}
