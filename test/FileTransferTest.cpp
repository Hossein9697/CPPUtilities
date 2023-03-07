#include <gtest/gtest.h>
#include "file-transfer/FileTransferUtility.hpp"

TEST(FileTransfer_Tests, check_conncetion_using_ip_and_port)
{
    std::string error;
    EXPECT_TRUE(FileTransferUtility::checkConnection("192.168.54.52", "8080", error)) << error;
    EXPECT_FALSE(FileTransferUtility::checkConnection("wrongIp", "8080", error));
    EXPECT_FALSE(FileTransferUtility::checkConnection("192.168.54.52", "wrongPort", error)) << error;
}

TEST(FileTransfer_Tests, check_conncetion_using_url)
{
    std::string error;
    EXPECT_TRUE(FileTransferUtility::checkConnection("192.168.54.52:8080/portalserver/atm/index", error)) << error;
    EXPECT_FALSE(FileTransferUtility::checkConnection("wrongUrl", error)) << error;
}