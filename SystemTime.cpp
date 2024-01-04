#include "SystemTime.h"

void SystemTime::getSystemTime()
{
    time_t t = time(nullptr);
    localtime_s(tm_info, &t);// 将时间格式化为字符串
    strftime(cYear_Month_Date, sizeof(cYear_Month_Date), "%Y年%m月%d日", tm_info);
    strftime(cHour_Mniute_Second, sizeof(cHour_Mniute_Second), "%H:%M:%S", tm_info);
    char y[10], m[10], d[10], w[10], H[10], M[10], S[10];
    strftime(y, sizeof(y), "%Y", tm_info);
    strftime(m, sizeof(m), "%m", tm_info);
    strftime(d, sizeof(d), "%d", tm_info);
    strftime(w, sizeof(w), "%w", tm_info);
    strftime(H, sizeof(H), "%H", tm_info);
    strftime(M, sizeof(M), "%M", tm_info);
    strftime(S, sizeof(S), "%S", tm_info);
    year = stol(y);
    month = stol(m);
    day = stol(d);
    dayOfWeek = stol(w);
    hour = stol(H);
    minute = stol(M);
    second = stol(S);

}

int SystemTime::getYear()
{
    return year;
}

int SystemTime::getMonth()
{
    return month;
}

int SystemTime::getDay()
{
    return day;
}

int SystemTime::getDayOfWeek()
{
    return dayOfWeek;
}

int SystemTime::getHour()
{
    return hour;
}

int SystemTime::getMinute()
{
    return minute;
}

int SystemTime::getSecond()
{
    return second;
}

void SystemTime::showTime()
{
    settextcolor(BLACK);
    settextstyle(30, 0, ("微软雅黑"));
    char output[100];
    strcpy_s(output, cYear_Month_Date);
    strcat_s(output, cHour_Mniute_Second);
    ::outtextxy(10, 10, output);
    settextstyle(20, 0, ("微软雅黑"));
    settextcolor(WHITE);
}

tm* SystemTime::get_tm_info()
{
    return tm_info;
}
char SystemTime::cYear_Month_Date[50] = { 0 };
char SystemTime::cHour_Mniute_Second[50] = { 0 };
time_t SystemTime::t = time(nullptr);
tm SystemTime::tm_info[50] = { 0 };
int SystemTime::year = 0;
int SystemTime::month = 0;
int SystemTime::day = 0;
int SystemTime::dayOfWeek = 0;
int SystemTime::hour = 0;
int SystemTime::minute = 0;
int SystemTime::second = 0;

