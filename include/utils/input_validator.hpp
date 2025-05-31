#pragma once

#include <regex>
#include <string>
#include <sstream>
#include "../RoomTabular.hpp"

namespace InputValidator {
    inline bool validateNotEmpty(const std::string &input, std::string &errorMsg) {
        if (input.empty()) {
            errorMsg = "Field cannot be empty.";
            return false;
        }
        return true;
    }

    inline bool validateNIM(const std::string &nim, std::string &errorMsg) {
        if (!std::regex_match(nim, std::regex("\\d+"))) {
            errorMsg = "NIM must be numeric!";
            return false;
        }
        return true;
    }

    inline bool validateName(const std::string &name, std::string &errorMsg) {
        if (!std::regex_match(name, std::regex("[A-Za-z\\s\\-]+"))) {
            errorMsg = "Name must consist of letters, spaces, and hyphens only!";
            return false;
        }
        return true;
    }

    inline bool validateDate(const std::string &date, std::string &errorMsg) {
    if (!std::regex_match(date, std::regex("\\d{4}-\\d{2}-\\d{2}"))) {
        errorMsg = "Date must be in YYYY-MM-DD format!";
        return false;
    }

    int year, month, day;
    char sep1, sep2;
    std::istringstream iss(date);
    if (!(iss >> year >> sep1 >> month >> sep2 >> day) || sep1 != '-' || sep2 != '-') {
        errorMsg = "Invalid date format.";
        return false;
    }

    if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1) {
        errorMsg = "Date is out of valid range!";
        return false;
    }

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDay = daysInMonth[month - 1];

    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        maxDay = 29; // Leap year
    }

    if (day > maxDay) {
        errorMsg = "Invalid day for the given month.";
        return false;
    }

    return true;
}


    inline bool validateTime(const std::string &time, std::string &errorMsg) {
        if (!std::regex_match(time, std::regex("\\d{2}:\\d{2}"))) {
            errorMsg = "Time must be in HH:MM format!";
            return false;
        }
        int hour, minute;
        char sep;
        std::istringstream iss(time);
        if (!(iss >> hour >> sep >> minute) || sep != ':') {
            errorMsg = "Time format is invalid!";
            return false;
        }
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            errorMsg = "Time must be between 00:00 and 23:59.";
            return false;
        }
        return true;
    }
    inline bool validateTimeRange(const std::string &start, const std::string &end, std::string &errorMsg) {
        if (start >= end) {
            errorMsg = "Start time must be earlier than end time.";
            return false;
        }
        return true;
    }

}