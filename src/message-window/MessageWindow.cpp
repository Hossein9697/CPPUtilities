#include "message-window/MessageWindow.hpp"

#include <algorithm>

#include "logger/LoggerHeaders.hpp"
#include "logger/LoggerAppenders.hpp"

LRESULT CALLBACK MessageWindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(hwnd, message, wparam, lparam);
}

MessageWindow::MessageWindow()
{
    this->windowClassName.clear();
    this->windowClassTitle.clear();
    this->expectedMessages.clear();
}

MessageWindow::MessageWindow(std::string windowClassName, std::string windowClassTitle, MessageFunction messageFunction, ExpectedMessages expectedMessages)
{
    this->windowClassName = windowClassName;
    this->windowClassTitle = windowClassTitle;
    this->messageFunction = messageFunction;
    this->expectedMessages = expectedMessages;
}

void MessageWindow::setWindowInformation(std::string windowClassName, std::string windowClassTitle, MessageFunction messageFunction, ExpectedMessages expectedMessages)
{
    this->windowClassName = windowClassName;
    this->windowClassTitle = windowClassTitle;
    this->messageFunction = messageFunction;
    this->expectedMessages = expectedMessages;
}

void MessageWindow::createWindow()
{
    Logger::getInstance(DEVELOPER_APPENDER_ID).log(TRACE_LOG_LEVEL, L">> MessageWindow::createWindow");

    auto unicodeWindowClassName = QString(windowClassName.c_str()).toStdWString();
    auto unicodeWindowClassTitle = QString(windowClassTitle.c_str()).toStdWString();

    WNDCLASS wClass;
    HWND gHwnd = nullptr;
    HINSTANCE gHinstance = nullptr;

    ZeroMemory(&wClass, sizeof(WNDCLASS));

    wClass.hInstance = gHinstance;
    wClass.cbClsExtra = 0;
    wClass.cbWndExtra = 0;
    wClass.lpszClassName = unicodeWindowClassName.c_str();
    wClass.lpszMenuName = nullptr;
    wClass.lpfnWndProc = MessageWindowProc;
    wClass.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH));
    wClass.hCursor = LoadIcon(nullptr, IDC_ARROW);
    wClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wClass.style = CS_OWNDC;

    if (!RegisterClass(&wClass))
    {
        LOG4CPLUS_WARN(Logger::getInstance(DEVELOPER_APPENDER_ID), "Create Window - Result : Failed - Reason : Can not register class - Window Name : " << windowClassName.c_str() << " - Window Title : " << windowClassTitle.c_str());
        return;
    }

    ULONG nWindowWidth;
    ULONG nWindowHeight;
    DWORD dwStyle;

    auto bFullScreen = false;

    if (bFullScreen)
    {
        nWindowWidth = GetSystemMetrics(SM_CXSCREEN);
        nWindowHeight = GetSystemMetrics(SM_CYSCREEN);
        dwStyle = WS_POPUP;
    }
    else
    {
        nWindowWidth = 640;
        nWindowHeight = 480;
        dwStyle = WS_OVERLAPPED | WS_SYSMENU;
    }

    gHwnd = CreateWindow(unicodeWindowClassName.c_str(), unicodeWindowClassTitle.c_str(), dwStyle, 0, 0, nWindowWidth, nWindowHeight, GetDesktopWindow(), NULL, gHinstance, NULL);

    if (!gHwnd)
    {
        LOG4CPLUS_WARN(Logger::getInstance(DEVELOPER_APPENDER_ID), "Create Window - Result : Failed - Reason : Can not create window - Window Name : " << windowClassName.c_str() << " - Window Title : " << windowClassTitle.c_str());
        return;
    }

    LOG4CPLUS_INFO(Logger::getInstance(DEVELOPER_APPENDER_ID), "Create Window - Result : Successful - Class Name : " << windowClassName.c_str() << " - Window Title : " << windowClassTitle.c_str());
}

void MessageWindow::waitForEvents()
{
    Logger::getInstance(DEVELOPER_APPENDER_ID).log(TRACE_LOG_LEVEL, L">> MessageWindow::waitForEvents");

    MSG msg;
    SecureZeroMemory(&msg, sizeof(MSG));

    BOOL result;
    HWND windowHandle;
    SecureZeroMemory(&windowHandle, sizeof(HWND));

    windowHandle = FindWindow(QString(windowClassName.c_str()).toStdWString().c_str(), nullptr);

    LOG4CPLUS_DEBUG(Logger::getInstance(DEVELOPER_APPENDER_ID), "Start Listening For Incoming Events - Result : Successful - Window Class Name : " << windowClassName.c_str());

    while ((result = GetMessage(&msg, windowHandle, 0, 0)) != 0)
    {
        if (result == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            if (bool(std::find(expectedMessages.begin(), expectedMessages.end(), msg.message) != expectedMessages.end()))
                messageFunction(&msg);
        }
    }
}
