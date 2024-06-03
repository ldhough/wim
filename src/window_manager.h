#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <vector>
#include "window_manager.h"
#include "display_manager.h"
#include "pid_observer.h"
#include "window_transformer.h"
#include "key_interceptor.h"
#include "keycodes.h"

class WindowManager {
	private:
		//DisplayManager display_manager;
		//DisplayStack
		//WindowStack
		PidObserver &pid_observer;
        KeyInterceptor &ki;
		Keycode active_verb; // [move] the
		Keycode active_adjective; // [top]
		Keycode active_noun; // [window]
		Keycode active_verb_adverb; // to the [right]
		bool scan_sentence();
        void erase_sentence();
        bool run_sentence();
	public:
		WindowManager(PidObserver&, KeyInterceptor&);
		~WindowManager();
		bool start();
};

#endif /* WINDOW_MANAGER_H */
