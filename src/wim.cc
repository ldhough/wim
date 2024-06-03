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
#include "window_manager.h"
#include "event_subscriber.h"
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
    PidObserver po([](pid_t pid) {
        cout << "Top pid is: " << pid << endl;
    });
    po.start();
    KeyInterceptor ki;
    ki.start();
    EventSubscriber<Keycode> es(
        [](Keycode kc) {
            cout << "EventSubscriber keycode: " << kc << endl;
        }
    );
    ki.subscribe(es.get_subscription_data());
#ifdef USING_VOICE_COMMANDS
	VoiceInterceptor vi;
	int status = vi.start();
#endif
    struct ev_loop *loop = ev_default_loop(0);
    ev_set_timeout_collect_interval(loop, 0.01f);
    ev_run(loop, 0);
    return 0;
}
