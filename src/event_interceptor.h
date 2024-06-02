#ifndef EVENT_INTERCEPTOR_H
#define EVENT_INTERCEPTOR_H

#include <iostream>
#include <unistd.h>

template<typename T>
class EventInterceptor {
	protected:
		int notification_read_fd = -1;
		int notification_write_fd = -1;
		bool started = false;
	public:
		int start() {
			int pipe_fds[2];
			if (pipe(pipe_fds) < 0) {
				throw std::runtime_error("Failed to create event notification pipe!");
			}
			this->notification_read_fd = pipe_fds[0];
			this->notification_write_fd = pipe_fds[1];
			return static_cast<T*>(this)->_start_internal();
		}
		int get_interceptor_fd() {
			return this->notification_read_fd;
		}
};

#endif /* EVENT_INTERCEPTOR_H */
