#ifndef EVENT_INTERCEPTOR_H
#define EVENT_INTERCEPTOR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include "utils.h"
#include "subscription_data.h"

extern int errno;

template<typename EventInterceptorType, typename EventType>
class EventInterceptor {
	protected:
        std::vector<SubscriptionData> subscribers = {};
		bool started = false;
        void __write(const void *buf) {
            const size_t fd_count = this->subscribers.size();
            for (size_t idx = 0; idx < fd_count; idx++) {
                SubscriptionData subscriber = this->subscribers[idx];
                int write_fd = subscriber.write_fd;
                if (write_fd == -1) {
                    throw std::runtime_error("write_fd for subscriber " + subscriber.name + " unset!");
                }
                ssize_t bytes_written = write(write_fd, buf, event_size);
                if (bytes_written == -1) {
                    log_error(std::string(std::strerror(errno)));
                }
            }
        }
	public:
        const size_t event_size = sizeof(EventType);
		void start() {
            if (this->started) {
                throw std::runtime_error("EventInterceptor already started!");
            }
			bool started = static_cast<EventInterceptorType*>(this)->_start_internal();
            this->started = started;
		}
        void stop() {
            if (!this->started) {
                throw std::runtime_error("EventInterceptor not started, cannot stop!");
            }
            bool stopped = static_cast<EventInterceptorType*>(this)->_stop_internal();
            if (!stopped) {
                throw std::runtime_error("Failed to stop EventInterceptor!");
            }
            this->started = false;
        }
        void subscribe(SubscriptionData subscriber) {
            subscribers.push_back(subscriber);
        }
        void unsubscribe(int fd) {
            std::sort(this->subscribers.begin(), this->subscribers.end(),
                [](SubscriptionData a, SubscriptionData b) {
                    return a.write_fd < b.write_fd;
                }
            );
            auto lower = std::lower_bound(this->subscribers.begin(), this->subscribers.end(), fd);
            if (lower != this->subscribers.end() && lower != this->subscribers.begin()) {
                auto at = std::distance(this->subscribers.begin(), lower);
                this->subscribers.erase(this->subscribers.begin() + at);
            }
        }
};

#endif /* EVENT_INTERCEPTOR_H */
