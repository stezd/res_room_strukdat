#pragma once

#include "Reservation.hpp"
#include "Stack.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <optional>
#include <nlohmann/json.hpp>

class ReservationTabular {
    std::vector<Reservation> ReservationTable;
    Stack<std::pair<std::string, Reservation>> undoStack; // Undo stack to store actions

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
        // Save this addition to the undo stack for reversal
        undoStack.push({"add", rsv});
        ReservationTable.push_back(rsv);
    }

    void erase(const std::string &id) {
        const auto it = std::ranges::find_if(ReservationTable.begin(), ReservationTable.end(),
                                       [&id](const Reservation &rsv) { return rsv.getId() == id; });
        if (it == ReservationTable.end()) {
            throw std::runtime_error("Reservation with given ID does not exist");
        }
        // Save this removal to the undo stack for reversal
        undoStack.push({"delete", *it});
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

    nlohmann::json to_json() const {
        nlohmann::json jsonArray = nlohmann::json::array();
        for (const auto &rsv : ReservationTable) {
            jsonArray.push_back(rsv.to_json()); // Use Reservation's to_json
        }
        return jsonArray;
    }

    void from_json(const nlohmann::json &jsonArray) {
        ReservationTable.clear(); // Clear existing table before loading
        for (const auto &item : jsonArray) {
            ReservationTable.push_back(Reservation::from_json(item)); // Use Reservation's from_json
        }
    }

    // Undo the last operation (add or delete)
    void undo() {
        if (undoStack.empty()) {
            throw std::runtime_error("Undo stack is empty. No actions to undo.");
        }

        auto [action, reservation] = undoStack.peek(); // Get the last action
        undoStack.pop(); // Remove it from the stack

        if (action == "add") {
            // Undo an add operation by removing the added reservation
            auto it = std::ranges::find_if(ReservationTable.begin(), ReservationTable.end(),
                                           [&reservation](const Reservation &rsv) {
                                               return rsv.getId() == reservation.getId();
                                           });
            if (it != ReservationTable.end()) {
                ReservationTable.erase(it);
            }
        } else if (action == "delete") {
            // Undo a delete operation by re-adding the reservation
            ReservationTable.push_back(reservation);
        }
    }

    // Implement sorting to maintain previous functionality
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