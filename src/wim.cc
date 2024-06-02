#include <iostream>
#include <string>
#include <vector>
#include <sys/select.h>
#include <ev.h>
#include <unistd.h>
#include "pid_observer.h"
#include "display_manager.h"
#include "key_interceptor.h"
#include "window_transformer.h"
//#include "window_manager.h"
#include "keycodes.h"

#ifdef USING_VOICE_COMMANDS
#include "voice_interceptor.h"
#endif

using std::cout, std::endl, std::string;

void key_press_callback(struct ev_loop *_loop, ev_io *watcher, int revents) {
	static unsigned int cb_2_counter = 0;
	//cout << "key_press_callback(): event on fd: " << watcher->fd << endl;
	char buff[2] = {0};
	read(watcher->fd, buff, sizeof(buff));
	cout << "buff is: " << (Keycode) buff[0] << endl;
	cb_2_counter++;
}

int main(int argc, const char **argv) {
    cout << "wim initializing" << endl;
    auto window_pids = PidObserver::get_window_pids();
    for (auto pid : window_pids) {
        //cout << "Window pid: " << pid << endl;
    }
    PidObserver po([](pid_t pid) {
        cout << "Top pid is: " << pid << endl;
    });
    po.start();
    cout << "Creating key interceptor object" << endl;
    KeyInterceptor ki;
	int notification_fd = ki.start();
#ifdef USING_VOICE_COMMANDS
	VoiceInterceptor vi;
	int status = vi.start();
#endif
	cout << "notification_fd is: "<< notification_fd << endl;
    struct ev_loop *loop = ev_default_loop(0);
	ev_io key_press_watcher;
	ev_io_init(&key_press_watcher, key_press_callback, notification_fd, EV_READ);
	ev_io_start(loop, &key_press_watcher);
    ev_set_timeout_collect_interval(loop, 0.01f);
    ev_run(loop, 0);
    return 0;
}
