#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "pid_observer.h"
#include "display_manager.h"

using std::cout, std::endl, std::string;

int main(int argc, const char **argv) {
    cout << "wim initializing" << endl;
    auto display_ids = DisplayManager::get_display_ids();
    cout << display_ids.size() << " displays detected" << endl;
    return 0;
}
