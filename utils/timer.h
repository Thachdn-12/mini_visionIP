#pragma once
#include <chrono>

#define NOW std::chrono::high_resolution_clock::now()

inline double MS(auto duration) {
    return std::chrono::duration<double, std::milli>(duration).count();
}