#pragma once

#include "Reservation.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>

class ReservationTabular {
    std::vector<Reservation> ReservationTable;

public:
    std::optional<Reservation> get_reservation_by_id(const std::string &id) const {
        const auto it = std::ranges::find_if(ReservationTable, [&id](const Reservation &rsv) {
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

    std::vector<Reservation> show_all() const {
        return ReservationTable;
    }

    nlohmann::json to_json() const {
        nlohmann::json jsonArray = nlohmann::json::array();
        for (const auto &rsv : ReservationTable) {
            jsonArray.push_back(rsv.to_json());
        }
        return jsonArray;
    }

    void from_json(const nlohmann::json &jsonArray) {
        ReservationTable.clear();
        for (const auto &item : jsonArray) {
            ReservationTable.push_back(Reservation::from_json(item));
        }
    }

    void sort_reservations(const std::string &criteria) {
        if (criteria == "date") {
            std::ranges::sort(ReservationTable, [](const Reservation &a, const Reservation &b) {
                return a.getTanggal() < b.getTanggal();
            });
        } else if (criteria == "room") {
            std::ranges::sort(ReservationTable, [](const Reservation &a, const Reservation &b) {
                return a.getRuangan() < b.getRuangan();
            });
        } else if (criteria == "jammulai") {
            std::ranges::sort(ReservationTable, [](const Reservation &a, const Reservation &b) {
                return a.getJamMulai() < b.getJamMulai();
            });
        } else if (criteria == "id") {
            std::ranges::sort(ReservationTable, [](const Reservation &a, const Reservation &b) {
                return a.getId() < b.getId();
            });
        } else {
            throw std::invalid_argument("Invalid sorting criteria: " + criteria);
        }
    }
};