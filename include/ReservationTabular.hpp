#pragma once

#include "Reservation.hpp"
#include <vector>
#include <string>
#include <stdexcept>

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

    std::vector<Reservation> show_all() const {
        return ReservationTable;
    }

    std::vector<Reservation> show_by_nim(const std::string &nim) const {
        std::vector<Reservation> result;
        std::ranges::copy_if(ReservationTable, std::back_inserter(result),
                             [&nim](const Reservation &rsv) { return rsv.getNim() == nim; });
        return result;
    }

    std::vector<Reservation> show_by_ruangan(const std::string &ruangan) const {
        std::vector<Reservation> result;
        std::ranges::copy_if(ReservationTable, std::back_inserter(result),
                             [&ruangan](const Reservation &rsv) { return rsv.getRuangan() == ruangan; });
        return result;
    }

    std::vector<Reservation> show_by_tanggal(const std::string &tanggal) const {
        std::vector<Reservation> result;
        std::ranges::copy_if(ReservationTable, std::back_inserter(result),
                             [&tanggal](const Reservation &rsv) { return rsv.getTanggal() == tanggal; });
        return result;
    }

    //implementasi sorting biar nilai bagus dikit
    void sort_reservations(const std::string &criteria) {
        if (criteria == "tanggal") {
            std::ranges::sort(ReservationTable, [](const Reservation &a, const Reservation &b) {
                return a.getTanggal() < b.getTanggal();
            });
        } else if (criteria == "ruangan") {
            std::ranges::sort(ReservationTable, [](const Reservation &a, const Reservation &b) {
                return a.getRuangan() < b.getRuangan();
            });
        } else if (criteria == "jam_mulai") {
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
