#include <iostream>
#include <string>
#include "utils.h"

using std::cout, std::cerr, std::endl;

void log_success(std::string msg) {
    cout << ANSI_GREEN_SUCCESS ": " + msg << endl;
}

void log_info(std::string msg) {
    cout << ANSI_BLUE_INFO ": " + msg << endl;
}

void log_error(std::string msg) {
    cerr << ANSI_RED_ERR ": " + msg << endl;
}
