#include "date.h"

/////////////////////////////////
/// class Date
////////////////////////////////

int Date::maxDay(int y, int m)
{
    if (y < 0)
        return 0;
    switch (m)
    {
    case 2:
        return 28 + ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 0;
    }
}
Date::Date(int y, int m, int d)
{
    set(y, m, d);
}
Date::Date(std::string input_str)
{
    std::stringstream ss(input_str);
    int d, m, y;
    char tmp;
    ss >> d >> tmp >> m >> tmp >> y;
    set(y, m, d);
}
void Date::setDay(int d)
{
    if (d < 1 || d > maxDay(year, month))
        day = DEFAULT_DAY;
    else
        day = d;
}
void Date::setMonth(int m)
{
    if (m < 1 || m > 12)
        month = DEFAULT_MONTH;
    else
        month = m;
}
void Date::setYear(int y)
{
    if (y < 0)
        year = DEFAULT_YEAR;
    else
        year = y;
}
void Date::set(int y, int m, int d)
{
    setYear(y);
    setMonth(m);
    setDay(d);
}
std::string Date::str() const
{
    return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
}
