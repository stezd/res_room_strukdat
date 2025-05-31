#pragma once

#include <string>
#include <functional>
#include <iomanip>
#include <sstream>
#include "../Reservation.hpp"

inline std::string generateBookingCode(const Reservation &rsv) {
    constexpr std::hash<std::string> hasher;
    std::string const raw = rsv.getNama() + rsv.getNim() + rsv.getTanggal() +
                            rsv.getJamMulai() + rsv.getJamSelesai() + rsv.getRuangan();

    std::stringstream ss;
    ss << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << hasher(raw);
    return ss.str();
}

inline bool isValidTime(const std::string &time) {
    if (time.length() != 5) return false;
    if (time[2] != ':') return false;

    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));

    return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

inline bool isValidDate(const std::string &date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    try {
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        return year >= 2023 && month >= 1 && month <= 12 && day >= 1 && day <= 31;
    } catch (...) {
        return false;
    }
}
