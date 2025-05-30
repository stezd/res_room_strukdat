#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <string>
#include <RoomTabular.hpp>
#include <Reservation.hpp>

// Function to save JSON data to a file
inline void saveToFile(const std::string& filename, const nlohmann::json& jsonData) {
    std::ofstream outFile(filename);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + filename);
    }
    outFile << jsonData.dump(4); // Format with 4-space indentation
    outFile.close();
}

// Function to load JSON data from a file
inline nlohmann::json loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Unable to open file for reading: " + filename);
    }
    nlohmann::json jsonData;
    inFile >> jsonData;
    return jsonData;
}

// Function to save a RoomTabular object to a JSON file
inline void saveRoomTabular(const std::string& filename, const RoomTabular& roomTabular) {
    saveToFile(filename, roomTabular.to_json());
}

// Function to load a RoomTabular object from a JSON file
inline RoomTabular loadRoomTabular(const std::string& filename) {
    nlohmann::json jsonData = loadFromFile(filename);
    RoomTabular roomTabular;
    roomTabular.from_json(jsonData);
    return roomTabular;
}

// Function to save a vector of Reservation objects to a JSON file
inline void saveReservations(const std::string& filename, const std::vector<Reservation>& reservations) {
    nlohmann::json jsonArray = nlohmann::json::array();
    for (const auto& reservation : reservations) {
        jsonArray.push_back(reservation.to_json());
    }
    saveToFile(filename, jsonArray);
}

// Function to load a vector of Reservation objects from a JSON file
inline std::vector<Reservation> loadReservations(const std::string& filename) {
    nlohmann::json jsonArray = loadFromFile(filename);
    std::vector<Reservation> reservations;
    for (const auto& item : jsonArray) {
        reservations.push_back(Reservation::from_json(item));
    }
    return reservations;
}