#ifndef CALL_BACK_TIMER_HPP
#define CALL_BACK_TIMER_HPP

#include <windows.h>
#include <string.h>
#include <functional>
#include <atomic>
#include <thread>
#include <type_traits>

typedef std::function<void(void)> CallBackTimerFunction;

class CallBackTimer
{

public:
    CallBackTimer();
    ~CallBackTimer();

    void start(int interval /* Miliseconds */, CallBackTimerFunction callbackFunction);
    void stop();
    bool isRunning() const;

private:
    std::atomic<bool> running;
    std::thread timerThread;
};

class Timer
{

public:
    Timer();

    void start();
    ULONG elapsedTime() const;
    bool isTimeout(ULONG seconds) const;

private:
    ULONG startTime;
};

#endif // CALL_BACK_TIMER_HPP
