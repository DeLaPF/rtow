#pragma once

#include <chrono>
#include <atomic>

using namespace std::chrono;

class Timer {
    public:
        Timer() { Reset(); }

        void Reset() { m_Start = high_resolution_clock::now(); }

        double Elapsed()
        {
            std::atomic_thread_fence(std::memory_order_relaxed);
            auto elapsed = duration_cast<nanoseconds>(high_resolution_clock::now() - m_Start).count();
            std::atomic_thread_fence(std::memory_order_relaxed);
            return static_cast<double>(elapsed);
        }

        double ElapsedSeconds() { return Elapsed() / 1000000000.0; }
    private:
        high_resolution_clock::time_point m_Start;
};
