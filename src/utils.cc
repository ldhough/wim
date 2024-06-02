#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <ctime>
#include <random>
#include "utils.h"

using std::cout, std::cerr, std::endl;

void log_success(std::string msg) {
    cout << ANSI_GREEN_SUCCESS ": " + msg << endl;
}

void log_info(std::string msg) {
    cout << ANSI_BLUE_INFO ": " + msg << endl;
}

void log_error(std::string msg) {
    cerr << ANSI_RED_ERR ": " + msg << endl;
}

void benchmark(std::function<void(void)> cb, std::string tag, size_t n = 1) {
	auto start = std::chrono::system_clock::now();
	for (size_t idx = 0; idx < n; idx++) {
		cb();
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Ran " << tag << " " << n
		<< " times in " << elapsed_seconds.count()
        << " seconds." << endl;
}
