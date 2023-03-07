#include "timer/timer.hpp"

#include <ctime>

CallBackTimer::CallBackTimer()
{
    running = false;
}

CallBackTimer::~CallBackTimer()
{
    if (running.load(std::memory_order_acquire))
        stop();
}

void CallBackTimer::start(int interval, CallBackTimerFunction callbackFunction)
{
    if (running.load(std::memory_order_acquire))
        stop();

    running.store(true, std::memory_order_release);

    timerThread = std::thread(
        [this, interval, callbackFunction]()
        {
            while (running.load(std::memory_order_acquire))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                callbackFunction();
            }
        });
}

void CallBackTimer::stop()
{
    running.store(false, std::memory_order_release);
    if (timerThread.joinable())
        timerThread.join();
}

bool CallBackTimer::isRunning() const
{
    return (running.load(std::memory_order_acquire) && timerThread.joinable());
}

Timer::Timer()
{
    startTime = 0;
}

void Timer::start()
{
    startTime = clock();
}

ULONG Timer::elapsedTime() const
{
    return (ULONG(clock()) - startTime) / CLOCKS_PER_SEC;
}

bool Timer::isTimeout(ULONG seconds) const
{
    return seconds >= elapsedTime();
}
