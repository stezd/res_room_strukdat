#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include "Reservation.hpp"

class IO {
private:
    static bool fileExists(const std::string &filename) {
        return std::filesystem::exists(filename);
    }

public:
    static void writeToJson(const std::string &filename, const Reservation &reservation) {
        nlohmann::json j = reservation;
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        file << j.dump(4);
    }

    static void writeToJson(const std::string &filename, const std::vector<Reservation> &reservations) {
        nlohmann::json j = nlohmann::json::array();
        for (const auto &reservation: reservations) {
            j.push_back(reservation);
        }
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        file << j.dump(4);
    }

    static Reservation readFromJson(const std::string &filename) {
        if (!fileExists(filename)) {
            throw std::runtime_error("File does not exist: " + filename);
        }
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        nlohmann::json j;
        file >> j;
        return j.get<Reservation>();
    }

    static std::vector<Reservation> readReservationsFromJson(const std::string &filename) {
        if (!fileExists(filename)) {
            throw std::runtime_error("File does not exist: " + filename);
        }
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        nlohmann::json j;
        file >> j;
        std::vector<Reservation> reservations;
        for (const auto &item: j) {
            reservations.push_back(item.get<Reservation>());
        }
        return reservations;
    }
};
