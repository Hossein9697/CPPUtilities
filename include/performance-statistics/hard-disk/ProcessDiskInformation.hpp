#ifndef PROCESS_DISK_INFORMATION_HPP
#define PROCESS_DISK_INFORMATION_HPP

#include <Windows.h>
#include <string>
#include <vector>
#include <sstream>

inline std::string addSeperator(std::string value, int count, char seperator)
{
    if (value.length() <= count)
        return value;

    int i = value.length();
    std::string buffer = "";
    auto j = 0;
    do
    {
        buffer.insert(0, value.substr(i--, 1));
        if (j == count && i > -1)
        {
            buffer = seperator + buffer;
            j = 0;
        }
        j++;
    } while (i > -1);
    return buffer;
}

inline std::string ULONGLONGToString(ULONGLONG number)
{
    std::stringstream stringStream;
    stringStream << ULONGLONG(number);
    return addSeperator(stringStream.str(), 3, '.');
}

struct ProcessDiskInformation
{
    ProcessDiskInformation()
    {
        readOperationCount = 0;
        writeOperationCount = 0;
        otherOperationCount = 0;
        readTransferCount = 0;
        writeTransferCount = 0;
        otherTransferCount = 0;
    }

    explicit ProcessDiskInformation(HANDLE processHandle)
    {
        IO_COUNTERS ioCounters = {0};
        if (GetProcessIoCounters(processHandle, &ioCounters))
        {
            readOperationCount = ioCounters.ReadOperationCount;
            writeOperationCount = ioCounters.WriteOperationCount;
            otherOperationCount = ioCounters.OtherOperationCount;
            readTransferCount = ioCounters.ReadTransferCount;
            writeTransferCount = ioCounters.WriteTransferCount;
            otherTransferCount = ioCounters.OtherTransferCount;
        }
        else
        {
            readOperationCount = 0;
            writeOperationCount = 0;
            otherOperationCount = 0;
            readTransferCount = 0;
            writeTransferCount = 0;
            otherTransferCount = 0;
        }
    }

    explicit ProcessDiskInformation(IO_COUNTERS ioCounters)
    {
        readOperationCount = ioCounters.ReadOperationCount;
        writeOperationCount = ioCounters.WriteOperationCount;
        otherOperationCount = ioCounters.OtherOperationCount;
        readTransferCount = ioCounters.ReadTransferCount;
        writeTransferCount = ioCounters.WriteTransferCount;
        otherTransferCount = ioCounters.OtherTransferCount;
    }

    ProcessDiskInformation(ULONGLONG readOperationCount, ULONGLONG writeOperationCount, ULONGLONG otherOperationCount, ULONGLONG readTransferCount, ULONGLONG writeTransferCount, ULONGLONG otherTransferCount)
    {
        this->readOperationCount = readOperationCount;
        this->writeOperationCount = writeOperationCount;
        this->otherOperationCount = otherOperationCount;
        this->readTransferCount = readTransferCount;
        this->writeTransferCount = writeTransferCount;
        this->otherTransferCount = otherTransferCount;
    }

    ProcessDiskInformation operator+(ProcessDiskInformation& processDiskInformation)
    {
        processDiskInformation.readOperationCount += readOperationCount;
        processDiskInformation.writeOperationCount += writeOperationCount;
        processDiskInformation.otherOperationCount += otherOperationCount;
        processDiskInformation.readTransferCount += readTransferCount;
        processDiskInformation.writeTransferCount += writeTransferCount;
        processDiskInformation.otherTransferCount += otherTransferCount;
        return processDiskInformation;
    }

    std::vector<std::string> toString(ProcessDiskInformation processDiskInformation) const
    {
        std::vector<std::string> information;
        information.push_back("The Number Of Read Operations Performed : " + ULONGLONGToString(processDiskInformation.readOperationCount));
        information.push_back("The Number Of Write Operations Performed : " + ULONGLONGToString(processDiskInformation.writeOperationCount));
        information.push_back("The Number Of I/O Operations Performed, Other Than Read And Write Operations : " + ULONGLONGToString(processDiskInformation.otherOperationCount));
        information.push_back("The Number Of Bytes Read : " + ULONGLONGToString(processDiskInformation.readTransferCount));
        information.push_back("The Number Of Bytes Written : " + ULONGLONGToString(processDiskInformation.writeTransferCount));
        information.push_back("The Number Of Bytes Transferred During Operations Other Than Read And Write Operations : " + ULONGLONGToString(processDiskInformation.otherTransferCount));
        information.push_back("Total Bytes Of Read And Written : " + ULONGLONGToString(processDiskInformation.readTransferCount + processDiskInformation.writeTransferCount));
        return information;
    }

    std::vector<std::string> toString() const
    {
        std::vector<std::string> information;
        information.push_back("The Number Of Read Operations Performed : " + ULONGLONGToString(readOperationCount));
        information.push_back("The Number Of Write Operations Performed : " + ULONGLONGToString(writeOperationCount));
        information.push_back("The Number Of I/O Operations Performed, Other Than Read And Write Operations : " + ULONGLONGToString(otherOperationCount));
        information.push_back("The Number Of Bytes Read : " + ULONGLONGToString(readTransferCount));
        information.push_back("The Number Of Bytes Written : " + ULONGLONGToString(writeTransferCount));
        information.push_back("The Number Of Bytes Transferred During Operations Other Than Read And Write Operations : " + ULONGLONGToString(otherTransferCount));
        information.push_back("Total Bytes Of Read And Written : " + ULONGLONGToString(readTransferCount + writeTransferCount));
        return information;
    }

    ULONGLONG readOperationCount;
    ULONGLONG writeOperationCount;
    ULONGLONG otherOperationCount;
    ULONGLONG readTransferCount;
    ULONGLONG writeTransferCount;
    ULONGLONG otherTransferCount;
};

#endif // PROCESS_DISK_INFORMATION_HPP
