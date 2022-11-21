//! Some simple timer implementations.

#include <chrono>
#include <iostream>

namespace chrono = std::chrono;

template<class Clock = chrono::system_clock, class Duration = chrono::duration<double, std::milli>>
class ScopeTimer {
    const char* title;
    chrono::time_point<Clock> start;

  public:
    ScopeTimer(const char* title): title(title), start(Clock::now()) {}

    ~ScopeTimer() {
        auto now = Clock::now();
        auto duration = chrono::duration_cast<Duration>(now - this->start);
        std::cerr << ">>>>> " << this->title << ": " << duration << std::endl;
    }
};

template<class Clock = chrono::system_clock, class Duration = chrono::duration<double, std::milli>>
class TickTimer {
    chrono::time_point<Clock> start;

  public:
    TickTimer(): start(Clock::now()) {}

    void tick(const char* title) {
        auto now = Clock::now();
        auto duration = chrono::duration_cast<Duration>(now - this->start);
        std::cerr << ">>>>> " << title << ": " << duration << std::endl;
        this->start = now;
    }
};
