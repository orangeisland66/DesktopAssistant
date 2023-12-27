#pragma once
#include"header.h"
class SystemTime
{
public:
    static void getSystemTime();
    static int getYear();
    static int getMonth();
    static int getDay();
    static int getDayOfWeek();
    static int getHour();
    static int getMinute();
    static int getSecond();
    static void showTime();
    static tm* get_tm_info();
private:
    static char cYear_Month_Date[50], cHour_Mniute_Second[50];
    static time_t t;
    static tm tm_info[50];
    static int year, month, day, dayOfWeek, hour, minute, second;
};

