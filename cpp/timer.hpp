//! A simple RAII timer.

#include <chrono>
#include <iostream>

namespace chrono = std::chrono;

template<class Clock = chrono::system_clock, class Duration = chrono::duration<double, std::milli>>
class Timer {
    const char* title;
    chrono::time_point<Clock> start;
    bool has_ended;

  public:
    Timer(const char* title): title(title), start(Clock::now()), has_ended(false) {}

    /// Useful for measuring variable constructions.
    void early_end() {
        this->~Timer();
        this->has_ended = true;
    }

    ~Timer() {
        if (this->has_ended) return;
        auto duration = chrono::duration_cast<Duration>(Clock::now() - this->start);
        std::cout << ">>>>> " << this->title << ": " << duration << std::endl;
    }
};
