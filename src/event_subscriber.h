#ifndef EVENT_SUBSCRIBER_H
#define EVENT_SUBSCRIBER_H

#include <functional>
#include <string>
#include <unistd.h>
#include <ev.h>
#include "subscription_data.h"

template<typename EventType>
class EventSubscriber {
    private:
        struct EventSubIO {
            ev_io io;
            std::function<void(EventType)> f;
        };
        struct EventSubIO watcher;
        std::string name;
        int read_fd = -1;
        int write_fd = -1;
        static void callback(struct ev_loop *_loop, ev_io *watcher, int revents) {
            char buff[sizeof(EventType)] = {0};
            read(watcher->fd, buff, sizeof(buff));
            struct EventSubIO *w = (EventSubIO*) watcher;
            w->f(*(static_cast<EventType*>((void*) buff)));
        }
    public:
        EventSubscriber(std::function<void(EventType)> f, std::string name = "") : name(name) {
            int rw_fds[2];
            if (pipe(rw_fds) < 0) {
                throw std::runtime_error("Failed to create event notification pipe!!");
            }
            this->read_fd = rw_fds[0];
            this->write_fd = rw_fds[1];
            this->watcher.f = f;
            struct ev_loop *loop = ev_default_loop(0);
            ev_io_init(&watcher.io, EventSubscriber<EventType>::callback, this->read_fd, EV_READ);
            ev_io_start(loop, &watcher.io);
        }
        SubscriptionData get_subscription_data() {
            return {this->write_fd, this->name};
        }
        int get_read_fd() {
            return this->read_fd;
        }
        int get_write_fd() {
            return this->write_fd;
        }
};

#endif /* EVENT_SUBSCRIBER_H */
