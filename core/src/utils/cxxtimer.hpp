#pragma once
#include <chrono>

// cxxtimer 

namespace heartCore {

using ns  = std::chrono::nanoseconds;
using us  = std::chrono::microseconds;
using ms  = std::chrono::milliseconds;
using s   = std::chrono::seconds;
using min = std::chrono::minutes;
using h   = std::chrono::hours;

class Timer {

public:

    Timer(bool start = false);
    Timer(const Timer& other) = default;
    Timer(Timer&& other) = default;
    virtual ~Timer() = default;

    Timer& operator=(const Timer& other) = default;
    Timer& operator=(Timer&& other) = default;

    
    void start();
    void stop();
    void reset();
    template <class duration_t = ms>
    typename duration_t::rep count() const;

private:

    bool started_;
    bool paused_;
    std::chrono::steady_clock::time_point reference_;
    std::chrono::duration<long double> accumulated_;
};

}


inline heartCore::Timer::Timer(bool start) :
        started_(false), paused_(false),
        reference_(std::chrono::steady_clock::now()),
        accumulated_(std::chrono::duration<long double>(0)) {
    if (start) {
        this->start();
    }
}

inline void heartCore::Timer::start() {
    if (!started_) {
        started_ = true;
        paused_ = false;
        accumulated_ = std::chrono::duration<long double>(0);
        reference_ = std::chrono::steady_clock::now();
    } else if (paused_) {
        reference_ = std::chrono::steady_clock::now();
        paused_ = false;
    }
}

inline void heartCore::Timer::stop() {
    if (started_ && !paused_) {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        accumulated_ = accumulated_ + std::chrono::duration_cast< std::chrono::duration<long double> >(now - reference_);
        paused_ = true;
    }
}

inline void heartCore::Timer::reset() {
    if (started_) {
        started_ = false;
        paused_ = false;
        reference_ = std::chrono::steady_clock::now();
        accumulated_ = std::chrono::duration<long double>(0);
    }
}

template <class duration_t>
typename duration_t::rep heartCore::Timer::count() const {
    if (started_) {
        if (paused_) {
            return std::chrono::duration_cast<duration_t>(accumulated_).count();
        } else {
            return std::chrono::duration_cast<duration_t>(
                    accumulated_ + (std::chrono::steady_clock::now() - reference_)).count();
        }
    } else {
        return duration_t(0).count();
    }
}