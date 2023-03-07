#ifndef POWER_UTILITY_HPP
#define POWER_UTILITY_HPP

#define BASE_RETURN_CODE_NUMBER            1000
#define LOGGER_INITIALIZATION_FAILED       BASE_RETURN_CODE_NUMBER + 1
#define APPLICATION_ALREADY_RUNNING_FAILED BASE_RETURN_CODE_NUMBER + 2
#define AGENT_INITIALIZATION_FAILED        BASE_RETURN_CODE_NUMBER + 3
#define RUN_AGENT_FAILED                   BASE_RETURN_CODE_NUMBER + 4
#define UNEXPECTED_EXCEPTION               BASE_RETURN_CODE_NUMBER + 5

class PowerUtility
{

public:
    static void quit();
    static void exit(int returnCode);
    static void restart();
    static void shutdown();
};

#endif // POWER_UTILITY_HPP