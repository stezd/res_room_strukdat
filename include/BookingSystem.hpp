#pragma once

#include "RoomTabular.hpp"
#include "ReservationTabular.hpp"
#include "Reservation.hpp"
#include <iostream>
#include <string>

class BookingSystem {
    RoomTabular roomTable;
    ReservationTabular reservationTable;

public:
    BookingSystem(const RoomTabular &rooms) : roomTable(rooms) {
    }

    void tambahReservasi(const Reservation &rsv) {
        if (!checkRoomExists(rsv.getRuangan())) {
            std::cerr << "Room does not exist: " << rsv.getRuangan() << "\n";
            return;
        }
        if (checkReservationConflict(rsv)) {
            std::cerr << "Conflicting reservation exists for room " << rsv.getRuangan();
            return;
        }

        reservationTable.push(rsv);
        std::cout << "Reservation added successfully!\n";
    }

    void tampilkanAntrean() const {
        auto reservations = reservationTable.show_all();
        if (reservations.empty()) {
            std::cout << "No reservations in queue.\n";
            return;
        }
        for (const auto &rsv: reservations) {
            std::cout << "ID: " << rsv.getId()
                    << " | Name: " << rsv.getNama()
                    << " | Room: " << rsv.getRuangan()
                    << " | Date: " << rsv.getTanggal()
                    << " | Start: " << rsv.getJamMulai()
                    << " | End: " << rsv.getJamSelesai()
                    << " | Status: " << rsv.getStatus() << "\n";
        }
    }

private:
    bool checkRoomExists(const std::string &roomId) const {
        const auto &rooms = roomTable.getRooms();
        for (const auto &room: rooms) {
            if (room.getId() == roomId) {
                return true;
            }
        }
        return false;
    }

    bool checkReservationConflict(const Reservation &rsv) const {
        auto reservations = reservationTable.show_by_ruangan(rsv.getRuangan());
        for (const auto &res: reservations) {
            if (res.getTanggal() == rsv.getTanggal() &&
                !(rsv.getJamMulai() >= res.getJamSelesai() ||
                  rsv.getJamSelesai() <= res.getJamMulai())) {
                return true;
            }
        }
        return false;
    }
};
