#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>

class Date
{
private:
    int day, month, year;
    static const int DEFAULT_DAY = 1, DEFAULT_MONTH = 1, DEFAULT_YEAR = 1970;
    static int maxDay(int y, int m);
public:
    Date(int y = DEFAULT_YEAR, int m = DEFAULT_MONTH, int d = DEFAULT_DAY);
    Date(std::string input_str);
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    void set(int y, int m, int d);
    std::string str() const;
};

#endif // DATE_H