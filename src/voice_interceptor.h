#ifndef VOICE_INTERCEPTOR_H
#define VOICE_INTERCEPTOR_H

//#include <whisper.h>
#include "event_interceptor.h"
#include "keycodes.h"

class VoiceInterceptor : EventInterceptor<VoiceInterceptor, Keycode> {
	private:
		//whisper_params params;
	public:
		VoiceInterceptor();
		~VoiceInterceptor();
		int _start_internal();
};

#endif /* VOICE_INTERCEPTOR_H */


