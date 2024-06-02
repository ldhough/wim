#ifndef PID_OBSERVER_H
#define PID_OBSERVER_H

#include <functional>
#include <vector>

class PidObserver {
    private:
        std::function<void(pid_t)> callback;
    public:
        PidObserver(std::function<void(pid_t)>);
        bool start();
        bool stop();
        static std::vector<pid_t> get_window_pids();
};

#endif /* PID_OBSERVER_H */
