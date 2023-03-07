#ifndef MEMORY_MAPPED_FILE_HPP
#define MEMORY_MAPPED_FILE_HPP

#include "windows.h"
#include <QtCore>

#define MAX_MESSAGE_SIZE 8000 // Byte

// Windows API
bool WINAPI PutMessageInMemoryMappedFile(void* data, int dataSize, TCHAR* memoryMapppedFileName);
bool __cdecl GetMessageFromMemoryMappedFile(void* data, int dataSize, TCHAR* memoryMapppedFileName);
bool WINAPI UnMapFile(TCHAR* memoryMapppedFileName);
HANDLE CreateMapFile(LPTSTR memoryMapppedFileName, DWORD maximumObjectSize, DWORD minimumObjectSize);
HANDLE OpenMapFile(LPTSTR memoryMapppedFileName);

class MemoryMappedFileManager
{

public:
    static bool GetMessages(std::string memoryMapppedFileName, void* data, int dataSize);
    static bool PutMessages(std::string memoryMapppedFileName, void* data, int dataSize);

protected:
private:
};

#endif // MEMORY_MAPPED_FILE_HPP
