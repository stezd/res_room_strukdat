#include "utils.hpp"
#include <functional>

std::string generateBookingCode(const Reservation& rsv) {
    constexpr std::hash<std::string> hasher;
    std::string const raw = rsv.getNama() + rsv.getNim() + rsv.getTanggal() + rsv.getTanggal();
    return std::to_string(hasher(raw));
}