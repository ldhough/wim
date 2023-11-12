#ifndef VOICE_INTERCEPTOR_H
#define VOICE_INTERCEPTOR_H

//#include <whisper.h>
#include "event_interceptor.h"

class VoiceInterceptor : EventInterceptor<VoiceInterceptor> {
	private:
		//whisper_params params;
	public:
		VoiceInterceptor();
		~VoiceInterceptor();
		int _start_internal();
};

#endif /* VOICE_INTERCEPTOR_H */


