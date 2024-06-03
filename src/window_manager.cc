#include "window_manager.h"
#include "pid_observer.h"
#include "key_interceptor.h"
#include "keycodes.h"

WindowManager::WindowManager(PidObserver &pi, KeyInterceptor &ki) : pid_observer(pi), ki(ki) {}

//bool WindowManager::subscribe_event_interceptor(EventInterceptor) {}

bool WindowManager::start() {
	// TODO: add functionality for subscribing to change in focused physical display 
	// TODO: add functionality for subscribing to change in focused window
    return true;
}

bool WindowManager::scan_sentence() {
    return false;
}

void WindowManager::erase_sentence() {
    this->active_verb = Keycode::EMPTY;
    this->active_adjective = Keycode::EMPTY;
    this->active_noun = Keycode::EMPTY;
    this->active_verb_adverb = Keycode::EMPTY;
}

bool WindowManager::run_sentence() {
    return false;
}
