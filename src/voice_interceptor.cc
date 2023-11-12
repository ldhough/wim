#include <thread>
#include <iostream>
#include <cstdint>
//#include <whisper.h>
#include "event_interceptor.h"
#include "voice_interceptor.h"

using std::cout, std::cerr, std::endl;

VoiceInterceptor::VoiceInterceptor() {}
VoiceInterceptor::~VoiceInterceptor() {}

int _start_internal() {
//	int32_t length_ms = 3e3;
//	int32_t capture_id = -1;
//	audio_async audio(length_ms);
//	if (!audio.init(capture_id, WHISPER_SAMPLE_RATE)) {
//		cerr << "Could not initialize audio!" << endl;
//		return -1;
//	} else {
//		cout << "Successfully initialized audio!" << endl;
//	}
//	audio.resume();
	return 1;
//	std::thread voice_thread([this]() {
//	});
}
