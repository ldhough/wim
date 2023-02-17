#include <iostream>
#include <string>
#include <vector>
#include <sys/select.h>
#include <ev.h>
#include <unistd.h>
#include "pid_observer.h"
#include "display_manager.h"
#include "key_interceptor.h"

using std::cout, std::endl, std::string;

void stdin_callback(struct ev_loop *_loop, ev_io *watcher, int revents) {
    cout << "stdin cb logging" << endl;
}

int main(int argc, const char **argv) {
    cout << "wim initializing" << endl;
//    bool wim_on = true;
//    fd_set fds;
//    int command_fd = 0;

    KeyInterceptor ki;

    struct ev_loop *loop = ev_default_loop(0);
    ev_io stdin_watcher;
    // esc watcher
    // ev_init(&esc_watcher, esc_callback
    ev_io_init(&stdin_watcher, stdin_callback, STDIN_FILENO, EV_READ);
    ev_io_start(loop, &stdin_watcher);
    ev_set_timeout_collect_interval(loop, 0.01f);
    ev_run(loop, 0);

//    while (wim_on) {
//        FD_ZERO(&fds);
//        FD_SET(command_fd, &fds);
//        if (select(command_fd+1, &fds, NULL, NULL, NULL) > 0) {
//        }
//    }
    return 0;
}
