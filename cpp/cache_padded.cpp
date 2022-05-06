//! An example showing that 128-byte alignment may outperform 64-byte alignment
//! in some cases on Intel (but not on AMD).
//!
//! This example is about true sharing between pairs of threads that uses
//! adjacent lines of memory.
//!
//! Ref: https://stackoverflow.com/questions/72126606

#include <atomic>
#include <thread>

alignas(128) std::atomic<int> counter[1024]{};

void update(int idx) {
    for (int j = 0; j < 100000000; ++j) ++counter[idx];
}

int main() {
    std::thread t1(update, 0);
    std::thread t2(update, 0);
    std::thread t3(update, 16);  // -> 32
    std::thread t4(update, 16);  // -> 32
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
