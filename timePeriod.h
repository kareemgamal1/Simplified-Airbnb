#ifndef TIMEPERIOD_H
#define TIMEPERIOD_H
struct Time
{
    int time_mday; // day of month from 1 to 31
    int time_mon;  // month of year from 0 to 11
    int time_year; // year since 1900
};
class timePeriod
{
public:
    bool includesDate(Time t);
    bool includesPeriod();
};
#endif