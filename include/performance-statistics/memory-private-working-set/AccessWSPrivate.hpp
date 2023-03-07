#pragma once

#include <Windows.h>

class AccessWSPrivate
{
    static int compare(const void* Val1, const void* Val2);

public:
    static DWORD calculateWSPrivate(DWORD processID);
};
