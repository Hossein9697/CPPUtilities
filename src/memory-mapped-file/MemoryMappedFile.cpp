#include "memory-mapped-file/MemoryMappedFile.hpp"

#include "convertor/type/TypeConvertor.hpp"

bool MemoryMappedFileManager::GetMessages(std::string memoryMapppedFileName, void* data, int dataSize)
{
    auto name = TypeConvertor::stringToTChar(memoryMapppedFileName);
    auto result = GetMessageFromMemoryMappedFile(data, dataSize, name);
    delete name;
    return result;
}

bool MemoryMappedFileManager::PutMessages(std::string memoryMapppedFileName, void* data, int dataSize)
{
    auto* name = TypeConvertor::stringToTChar(memoryMapppedFileName);
    auto result = PutMessageInMemoryMappedFile(data, dataSize, name);
    delete name;
    return result;
}

bool WINAPI PutMessageInMemoryMappedFile(void* data, int dataSize, TCHAR* memoryMapppedFileName)
{
    auto namedFileMappingHandle = CreateMapFile(memoryMapppedFileName, 0, MAX_MESSAGE_SIZE);
    if (namedFileMappingHandle == nullptr || namedFileMappingHandle == INVALID_HANDLE_VALUE)
        return false;

    auto memoryData = LPBYTE(MapViewOfFile(namedFileMappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, MAX_MESSAGE_SIZE));
    if (memoryData == nullptr)
    {
        CloseHandle(namedFileMappingHandle);
        return false;
    }

    CopyMemory(PVOID(memoryData), data, dataSize);

    UnmapViewOfFile(memoryData);
    // CloseHandle(namedFileMappingHandle);

    return true;
}

bool __cdecl GetMessageFromMemoryMappedFile(void* data, int dataSize, TCHAR* memoryMapppedFileName)
{
    auto namedFileMappingHandle = OpenMapFile(memoryMapppedFileName);
    if (namedFileMappingHandle == nullptr || namedFileMappingHandle == INVALID_HANDLE_VALUE)
        return false;

    auto memoryData = LPBYTE(MapViewOfFile(namedFileMappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, MAX_MESSAGE_SIZE));
    if (memoryData == nullptr)
    {
        CloseHandle(namedFileMappingHandle);
        return false;
    }

    // memcpy(data, memoryData, sizeof(dataSize));;
    CopyMemory(PVOID(data), memoryData, dataSize);

    UnmapViewOfFile(memoryData);
    CloseHandle(namedFileMappingHandle);

    return true;
}

bool WINAPI UnMapFile(TCHAR* memoryMapppedFileName)
{
    auto namedFileMappingHandle = CreateMapFile(memoryMapppedFileName, 0, MAX_MESSAGE_SIZE);
    if (namedFileMappingHandle == nullptr || namedFileMappingHandle == INVALID_HANDLE_VALUE)
        return false;

    auto memoryData = LPBYTE(MapViewOfFile(namedFileMappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, MAX_MESSAGE_SIZE));
    if (memoryData == nullptr)
    {
        CloseHandle(namedFileMappingHandle);
        return false;
    }

    UnmapViewOfFile(memoryData);
    CloseHandle(namedFileMappingHandle);

    return true;
}

HANDLE CreateMapFile(LPTSTR memoryMapppedFileName, DWORD maximumObjectSize, DWORD minimumObjectSize)
{
    auto namedFileMappingHandle = CreateFileMapping(INVALID_HANDLE_VALUE,   // use paging file
                                                    NULL,                   // default security
                                                    PAGE_READWRITE,         // read/write access
                                                    maximumObjectSize,      // maximum object size (high-order DWORD)
                                                    minimumObjectSize,      // maximum object size (low-order DWORD)
                                                    memoryMapppedFileName); // name of mapping object
    return namedFileMappingHandle;
}

HANDLE OpenMapFile(LPTSTR memoryMapppedFileName)
{
    auto namedFileMappingHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS,    // read/write access
                                                  FALSE,                  // do not inherit the name
                                                  memoryMapppedFileName); // name of mapping object
    return namedFileMappingHandle;
}
