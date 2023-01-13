#include <iostream>
#include <string>
#include <vector>
#include <sys/select.h>
#include <ev.h>
#include "pid_observer.h"
#include "display_manager.h"

using std::cout, std::endl, std::string;

int main(int argc, const char **argv) {
    cout << "wim initializing" << endl;
    bool wim_on = true;
    fd_set fds;
    int command_fd = 0;
    while (wim_on) {
        FD_ZERO(&fds);
        FD_SET(command_fd, &fds);
        if (select(command_fd+1, &fds, NULL, NULL, NULL) > 0) {
        }
    }
    return 0;
}
