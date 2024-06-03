#ifndef SUBSCRIPTION_DATA_H
#define SUBSCRIPTION_DATA_H

#include <string>

struct SubscriptionData {
    int write_fd = -1;
    std::string name = "";
};

#endif /* SUBSCRIPTION_DATA_H */
