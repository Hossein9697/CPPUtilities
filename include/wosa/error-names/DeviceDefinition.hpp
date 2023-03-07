#ifndef DEVICE_DEFINITION_HPP
#define DEVICE_DEFINITION_HPP

#include <map>
#include <string>

#define WFS_TRACE_NONE                    0
#define LOCK_DEVICE_TIME_OUT              30 * 1000     // 30  Seconds
#define OPEN_DEVICE_TIME_OUT              2 * 60 * 1000 // 120 Seconds
#define GET_INFO_TIME_OUT                 3 * 60 * 1000 // 180 Seconds
#define EXECUTE_TIME_OUT                  3 * 60 * 1000 // 180 Seconds
#define INFINITE_TIME_OUT                 0             // Infinite
#define DEVICE_GENERAL_VERSION            0x01010203    // 3.00

#define WFS_GENERAL_ERROR                 (-99)

#define OPEN_COMMAND_NAME                 "WFSOpen"
#define CLOSE_COMMAND_NAME                "WFSClose"
#define REGISTER_COMMAND_NAME             "WFSRegister"
#define DEREGISTER_COMMAND_NAME           "WFSDeregister"
#define CANCEL_ASYNC_REQUEST_COMMAND_NAME "WFSCancelAsyncRequest"
#define CANCEL_BLOCKING_CALL_COMMAND_NAME "WFSCancelBlockingCall"
#define LOCK_COMMAND_NAME                 "WFSLock"
#define UNLOCK_COMMAND_NAME               "WFSUnlock"

typedef std::map<std::string, std::string> DeviceConfigs;

#endif // DEVICE_DEFINITION_HPP
