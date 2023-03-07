#pragma once

#include <list>
#include <QThread>
#include <Windows.h>

typedef std::list<UINT> ExpectedMessages;
typedef std::function<void(LPMSG)> MessageFunction;

class MessageWindow : public QObject
{
    Q_OBJECT

public:
    MessageWindow();
    MessageWindow(std::string windowClassName, std::string windowClassTitle, MessageFunction messageFunction, ExpectedMessages expectedMessages);
    void setWindowInformation(std::string windowClassName, std::string windowClassTitle, MessageFunction messageFunction, ExpectedMessages expectedMessages);

public slots:
    void createWindow();
    void waitForEvents();

private:
    QThread thread;
    std::string windowClassName;
    std::string windowClassTitle;
    MessageFunction messageFunction;
    ExpectedMessages expectedMessages;
};
