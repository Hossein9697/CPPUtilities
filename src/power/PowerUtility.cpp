#include "power/PowerUtility.hpp"

#include <windows.h>
#include <QtCore/qcoreapplication.h>

void PowerUtility::quit()
{
    QCoreApplication::quit();
}

void PowerUtility::exit(int returnCode)
{
    QCoreApplication::exit(returnCode);
}

void PowerUtility::shutdown()
{
    system("shutdown -s -f -t 00");
    while (true)
    {
    }
}

void PowerUtility::restart()
{
    system("shutdown -r -f -t 00");
    while (true)
    {
    }
}
