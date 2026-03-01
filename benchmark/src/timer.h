//
// Created by Lloyd Brown on 8/30/19.
//
// Portable high-resolution timer using std::chrono. Works on all architectures
// (x86, ARM64/aarch64, etc.). Reports time in nanoseconds; suitable for
// relative performance comparison (e.g. baseline vs DSE extension).
//

#ifndef PANCAKE_TIMER_H
#define PANCAKE_TIMER_H

#include <chrono>
#include <cstdint>

namespace {

inline uint64_t get_steady_ns() {
    using clock = std::chrono::steady_clock;
    auto now = clock::now().time_since_epoch();
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

}  // namespace

// Capture current time in nanoseconds (monotonic). Same API as legacy rdtscll
// so call sites need no changes. "Ticks" here are nanoseconds.
#define rdtscll(val) do { (val) = get_steady_ns(); } while (0)

// Return "ticks per microsecond" so that (ticks_per_ns = rdtscuhz()/1000) gives
// ticks_per_ns = 1.0 and (end-start)/ticks_per_ns = duration in nanoseconds.
// Portable: we use nanosecond ticks, so 1000 "ticks"/us = 1 tick/ns.
inline unsigned long long rdtscuhz(void) {
    return 1000u;
}

#endif // PANCAKE_TIMER_H
