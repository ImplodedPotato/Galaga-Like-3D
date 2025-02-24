#pragma once
#include <functional>
#include <tuple>
#include <utility>
#include "raylib.h"

class Timer {
    private:
        double duration;
        double startTime;
        bool repeat;
        std::function<void()> func;

    public:
        bool active;
        Timer();

        Timer(double duration, bool repeat, bool autostart, std::function<void()> func);

        void activate();


        void deactivate();


        void update();
};