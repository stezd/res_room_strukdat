#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

class Room {
public:
    Room() = default;

    Room(const std::string &id, const std::string &name,
         const std::string &open, const std::string &close, bool ready)
        : id_ruangan(id), nama_ruangan(name),
          jam_ruangan_open(open), jam_ruangan_close(close),
          ruangan_ready(ready) {
    }

    const std::string &getId() const { return id_ruangan; }
    const std::string &getName() const { return nama_ruangan; }
    const std::string &getOpenTime() const { return jam_ruangan_open; }
    const std::string &getCloseTime() const { return jam_ruangan_close; }
    bool isReady() const { return ruangan_ready; }

    void setId(const std::string &id) { id_ruangan = id; }
    void setName(const std::string &name) { nama_ruangan = name; }
    void setOpenTime(const std::string &open) { jam_ruangan_open = open; }
    void setCloseTime(const std::string &close) { jam_ruangan_close = close; }
    void setReady(bool ready) { ruangan_ready = ready; }

    std::string toString() const {
        return "ID: " + id_ruangan +
               " | Nama: " + nama_ruangan +
               " | Jam Buka: " + jam_ruangan_open +
               " | Jam Tutup: " + jam_ruangan_close +
               " | Siap: " + (ruangan_ready ? "Ya" : "Tidak");
    }

private:
    std::string id_ruangan;
    std::string nama_ruangan;
    std::string jam_ruangan_open;
    std::string jam_ruangan_close;
    bool ruangan_ready;
};

class RoomTabular {
public:
    void addRoom(const Room &room) {
        rooms.push_back(room);
    }

    void deleteRoom(const std::string &roomId) {
        auto it = std::ranges::find_if(rooms, [&roomId](const Room &room) {
            return room.getId() == roomId;
        });

        if (it == rooms.end()) {
            throw std::runtime_error("Room with ID '" + roomId + "' does not exist.");
        }

        rooms.erase(it);
        std::cout << "Room with ID '" << roomId << "' has been successfully deleted.\n";
    }

    const Room &getRoomById(const std::string &roomId) const {
        auto it = std::ranges::find_if(rooms, [&roomId](const Room &room) {
            return room.getId() == roomId;
        });

        if (it == rooms.end()) {
            throw std::runtime_error("Room with ID '" + roomId + "' does not exist.");
        }

        return *it;
    }

    const std::vector<Room> &getRooms() const {
        return rooms;
    }

    friend std::ostream &operator<<(std::ostream &os, const RoomTabular &rt) {
        os << "Daftar Ruangan:\n";
        for (const auto &room: rt.rooms) {
            os << room.toString() << std::endl;
        }
        return os;
    }

    void from_json(const nlohmann::json &j) {
        rooms.clear();
        for (const auto &item: j) {
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
        for (const auto &room: rooms) {
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
