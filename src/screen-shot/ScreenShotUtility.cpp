#include "screen-shot/ScreenShotUtility.hpp"

bool ScreenShotUtility::takeScreenShot(std::string fileName)
{
    try
    {
        HDC hdc[2];
        RECT rect;
        HBITMAP bitmapHandle;
        HWND desktopWindowHandle;

        desktopWindowHandle = GetDesktopWindow();
        GetWindowRect(desktopWindowHandle, &rect);
        hdc[0] = GetWindowDC(desktopWindowHandle);
        rect.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        rect.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);

        bitmapHandle = CreateCompatibleBitmap(hdc[0], rect.right, rect.bottom);
        hdc[1] = CreateCompatibleDC(hdc[0]);
        auto tempBitmap = SelectObject(hdc[1], bitmapHandle);
        BitBlt(hdc[1], 0, 0, rect.right, rect.bottom, hdc[0], 0, 0, SRCCOPY);
        bitmapHandle = (HBITMAP)SelectObject(hdc[1], tempBitmap);
        if (bitmapHandle != NULL)
            saveBitmap(hdc[1], bitmapHandle, fileName.c_str());

        DeleteDC(hdc[0]);
        ReleaseDC(NULL, hdc[0]);
        DeleteDC(hdc[1]);
        ReleaseDC(NULL, hdc[1]);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool ScreenShotUtility::saveBitmap(HDC handelOfDeviceContext, HBITMAP bitmap, const char* path)
{
    DWORD error;
    FILE* fp = NULL;
    fp = fopen(path, "wb");
    if (fp == NULL)
        return false;

    BITMAP Bm;
    BITMAPINFO BitInfo;
    ZeroMemory(&BitInfo, sizeof(BITMAPINFO));
    BitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BitInfo.bmiHeader.biBitCount = 0;

    if (!::GetDIBits(handelOfDeviceContext, bitmap, 0, 0, NULL, &BitInfo, DIB_RGB_COLORS))
    {
        fclose(fp);
        return false;
    }

    Bm.bmHeight = BitInfo.bmiHeader.biHeight;
    Bm.bmWidth = BitInfo.bmiHeader.biWidth;

    BITMAPFILEHEADER BmHdr;
    BmHdr.bfType = 0x4d42; // 'BM' WINDOWS_BITMAP_SIGNATURE
    BmHdr.bfSize = (((3 * Bm.bmWidth + 3) & ~3) * Bm.bmHeight) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    BmHdr.bfReserved1 = BmHdr.bfReserved2 = 0;
    BmHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    BitInfo.bmiHeader.biCompression = 0;
    // Writing Bitmap File Header ////
    size_t size = fwrite(&BmHdr, sizeof(BITMAPFILEHEADER), 1, fp);
    if (size < 1)
        error = GetLastError();

    size = fwrite(&BitInfo.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    if (size < 1)
        error = GetLastError();

    BYTE* pData = new BYTE[BitInfo.bmiHeader.biSizeImage + 5];
    if (!::GetDIBits(handelOfDeviceContext, bitmap, 0, Bm.bmHeight, pData, &BitInfo, DIB_RGB_COLORS))
    {
        fclose(fp);
        delete pData;
        return false;
    }
    if (pData != NULL)
        fwrite(pData, 1, BitInfo.bmiHeader.biSizeImage, fp);

    fclose(fp);
    delete pData;
    pData = nullptr;

    return true;
}
