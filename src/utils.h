#ifndef UTILS_H
#define UTILS_H

#include <string>

#define ANSI_RED "\033[1;31m"
#define ANSI_BLUE "\033[1;36m"
#define ANSI_GREEN "\033[1;32m"
#define ANSI_RESET "\033[0m"
#define ANSI_RED_ERR "\033[1;31mERROR\033[0m"
#define ANSI_BLUE_INFO "\033[1;36mINFO\033[0m"
#define ANSI_GREEN_SUCCESS "\033[1;32mSUCCESS\033[0m"

void log_success(std::string);
void log_info(std::string);
void log_error(std::string);

#endif /* UTILS_H */
