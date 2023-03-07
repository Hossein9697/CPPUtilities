#pragma once

#include "date-time/DateTimeUtility.hpp"
#include <chrono>
#include <gtest/gtest.h>

class DateTime : public ::testing::Test
{
    void SetUp() override
    {
        std::chrono::time_point t = std::chrono::system_clock::now();
        time_t t_time_t = std::chrono::system_clock::to_time_t(t);

        tm local_tm = *localtime(&t_time_t);

        day = std::to_string(local_tm.tm_mday);
        year = std::to_string(1900 + local_tm.tm_year);
        month = std::to_string(local_tm.tm_mon + 1);
        hour = std::to_string(local_tm.tm_hour);
        minute = std::to_string(local_tm.tm_min);
        second = std::to_string(local_tm.tm_sec);
    }

public:
    std::string day;
    std::string year;
    std::string month;
    std::string hour;
    std::string minute;
    std::string second;
};

TEST_F(DateTime, GetTime) { EXPECT_EQ(DateTimeUtility::getCurrentDateTime("yyyyMdhms"), year + month + day + hour + minute + second); }
