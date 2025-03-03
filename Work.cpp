#include <iostream>
#include <ctime>
using namespace std;

struct StDate {
    int year;
    int month;
    int day;
    int dayOfWeek; // Monday = 1, ..., Sunday = 7
};

// Check if year is leap year
bool IsLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// Get number of days in month
int NumberOfDaysInMonth(int month, int year) {
    int daysInMonth[] = { 31, 28 + IsLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return daysInMonth[month - 1];
}

// Get today's date
StDate Today() {
    StDate today;
    time_t now = time(0);
    tm localTime;

    localtime_s(&localTime, &now);

    today.year = localTime.tm_year + 1900;
    today.month = localTime.tm_mon + 1;
    today.day = localTime.tm_mday;

    // تحويل النظام (0 = Sunday) إلى (1 = Monday, ..., 7 = Sunday)
    int systemDay = localTime.tm_wday;
    today.dayOfWeek = (systemDay == 0) ? 7 : systemDay; // عشان الأحد يبقى 7

    return today;
}

// Get day name
string DayName(int day) {
    string days[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    return days[day - 1];
}

// Is end of week (Sunday)
bool IsEndOfWeek(int day) {
    return (day == 7); // Sunday
}

// Is weekend (Saturday & Sunday)
bool IsWeekend(int day) {
    return (day == 6 || day == 7); // Saturday or Sunday
}

// Is business day (Monday to Friday)
bool IsBusinessDay(int day) {
    return (day >= 1 && day <= 5); // Mon-Fri
}

// Days until end of the week (until Sunday)
int DaysUntilEndOfWeek(StDate date) {
    return 7 - date.dayOfWeek;
}

// Days until end of the month
int DaysUntilEndOfMonth(StDate date) {
    return NumberOfDaysInMonth(date.month, date.year) - date.day;
}

// Days until end of the year
int DaysUntilEndOfYear(StDate date) {
    int days = DaysUntilEndOfMonth(date);
    for (int month = date.month + 1; month <= 12; ++month) {
        days += NumberOfDaysInMonth(month, date.year);
    }
    return days;
}

// Main program
int main() {
    StDate today = Today();
    cout << DayName(today.dayOfWeek) << " , " << today.year << "/" << today.month << "/" << today.day << endl;

    cout << "\nIs it End of Week? " << (IsEndOfWeek(today.dayOfWeek) ? "Yes" : "No") << endl;
    cout << "Is it Weekend? " << (IsWeekend(today.dayOfWeek) ? "Yes" : "No") << endl;
    cout << "Is it Business Day? " << (IsBusinessDay(today.dayOfWeek) ? "Yes" : "No") << endl;

    cout << "\nDays Until End of Week: " << DaysUntilEndOfWeek(today) << " day(s)" << endl;
    cout << "Days Until End of Month: " << DaysUntilEndOfMonth(today) << " day(s)" << endl;
    cout << "Days Until End of Year: " << DaysUntilEndOfYear(today) << " day(s)" << endl;

    return 0;
}
