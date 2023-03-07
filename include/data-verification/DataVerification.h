#ifndef DATA_VERIFICATION_H_
#define DATA_VERIFICATION_H_

#include <string>

class DataVerification
{
public:
    enum class ReturnCodes
    {
        INPUT_FILE_PATH_NOT_EXIST,
        HASH_NOT_EQUAL,
        UNKNOWN,
        OK,
        COULD_NOT_OPEN_MAIN_HASH_FILE
    };
    static ReturnCodes createVerificationFilesFromFileOfPaths(const std::string& thePathOfFilePathes);
    static ReturnCodes verifyAllConfigFiles(const std::string& thePathOfFilePathes);
};

#endif
