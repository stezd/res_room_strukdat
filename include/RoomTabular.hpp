#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

class Room {
public:
    Room() = default;
    Room(const std::string& id, const std::string& name,
         const std::string& open, const std::string& close, bool ready)
        : id_ruangan(id), nama_ruangan(name),
          jam_ruangan_open(open), jam_ruangan_close(close),
          ruangan_ready(ready) {}

    const std::string& getId() const { return id_ruangan; }
    const std::string& getName() const { return nama_ruangan; }
    const std::string& getOpenTime() const { return jam_ruangan_open; }
    const std::string& getCloseTime() const { return jam_ruangan_close; }
    bool isReady() const { return ruangan_ready; }

    void setId(const std::string& id) { id_ruangan = id; }
    void setName(const std::string& name) { nama_ruangan = name; }
    void setOpenTime(const std::string& open) { jam_ruangan_open = open; }
    void setCloseTime(const std::string& close) { jam_ruangan_close = close; }
    void setReady(bool ready) { ruangan_ready = ready; }

private:
    std::string id_ruangan;
    std::string nama_ruangan;
    std::string jam_ruangan_open;
    std::string jam_ruangan_close;
    bool ruangan_ready;
};

class RoomTabular {
public:
    void addRoom(const Room& room) {
        rooms.push_back(room);
    }

    const std::vector<Room>& getRooms() const {
        return rooms;
    }

    void printRooms() const {
        std::cout << "Daftar Ruangan:\n";
        for (const auto& room : rooms) {
            std::cout << "ID: " << room.getId()
                      << " | Nama: " << room.getName()
                      << " | Jam Buka: " << room.getOpenTime()
                      << " | Jam Tutup: " << room.getCloseTime()
                      << " | Siap: " << (room.isReady() ? "Ya" : "Tidak")
                      << std::endl;
        }
    }

    void from_json(const nlohmann::json& j) {
        rooms.clear();
        for (const auto& item : j) {
            rooms.emplace_back(
                item.at("id_ruangan").get<std::string>(),
                item.at("nama_ruangan").get<std::string>(),
                item.at("jam_ruangan_open").get<std::string>(),
                item.at("jam_ruangan_close").get<std::string>(),
                item.at("ruangan_ready").get<bool>()
            );
        }
    }

    nlohmann::json to_json() const {
        nlohmann::json j = nlohmann::json::array();
        for (const auto& room : rooms) {
            j.push_back({
                {"id_ruangan", room.getId()},
                {"nama_ruangan", room.getName()},
                {"jam_ruangan_open", room.getOpenTime()},
                {"jam_ruangan_close", room.getCloseTime()},
                {"ruangan_ready", room.isReady()}
            });
        }
        return j;
    }
private:
    std::vector<Room> rooms;
};

inline void to_json(nlohmann::json &j, const RoomTabular &r) {
    j = r.to_json();
}

inline void from_json(const nlohmann::json &j, RoomTabular &r) {
    r.from_json(j);
}