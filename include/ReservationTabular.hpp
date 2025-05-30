#pragma once

#include "Reservation.hpp"
#include "BookingSystem.hpp"
#include <vector>
#include <string>

class ReservationTabular {
    std::vector<Reservation> ReservationTable;

public:
    std::optional<Reservation> get_reservation_by_id(const std::string &id) const {
        const auto it =
                std::ranges::find_if(ReservationTable, [&id](const Reservation &rsv) {
                    return rsv.getId() == id;
                });
        if (it != ReservationTable.end()) {
            return *it;
        }
        return std::nullopt;
    }

    void push(const Reservation &rsv) {
        ReservationTable.push_back(rsv);
    }

    void erase(const std::string &id) {
        const auto it = std::ranges::find_if(ReservationTable.begin(), ReservationTable.end(),
                                       [&id](const Reservation &rsv) { return rsv.getId() == id; });
        if (it == ReservationTable.end()) {
            throw std::runtime_error("Reservation with given ID does not exist");
        }
        ReservationTable.erase(it);
    }
};
