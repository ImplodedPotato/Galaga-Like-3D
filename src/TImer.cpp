#include "Timer.h"

Timer::Timer(): active(false) {}

Timer::Timer(double duration, bool repeat, bool autostart, std::function<void()> func):
duration(duration), 
startTime(0), 
repeat(repeat),
func(func),
active(false) {
    if (autostart) {
        activate();
    }
}

void Timer::activate() {
    active = true;
    startTime = GetTime();
}

void Timer::deactivate() {
    active = false;
    startTime = 0.0;
    if (repeat) {
        activate();
    }
}

void Timer::update() {
    if (active) {
        if (GetTime() - startTime >= duration) {
            if (func) {
                func();
            }
            deactivate();
        }
    }
}