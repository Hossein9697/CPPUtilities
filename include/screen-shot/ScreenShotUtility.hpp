#ifndef SCREEN_SHOT_UTILITY_HPP
#define SCREEN_SHOT_UTILITY_HPP

#include <string>
#include <Windows.h>

#define SCREEN_SHOT_EXTENSION ".bmp"

class ScreenShotUtility
{

public:
    static bool takeScreenShot(std::string fileName);

private:
    static bool saveBitmap(HDC handelOfDeviceContext, HBITMAP bitmap, const char* path);
};

#endif // SCREEN_SHOT_UTILITY_HPP
