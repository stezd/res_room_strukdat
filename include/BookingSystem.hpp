#pragma once

#include "RoomTabular.hpp"
#include "ReservationTabular.hpp"
#include "Reservation.hpp"
#include "ReservationQueue.hpp"
#include "Stack.hpp"
#include <iostream>
#include <IO.hpp>
#include <string>
#include <functional>

class BookingSystem {
    RoomTabular roomTable;
    ReservationTabular reservationTable;
    ReservationQueue reservationQueue;
    Stack<std::function<void()>> undoStack;

public:
    explicit BookingSystem(const RoomTabular &rooms) : roomTable(rooms) {
    }

    const RoomTabular &getRoomTable() const {
        return roomTable;
    }

    void tambahRuangan(const std::string &id, const std::string &name,
                       const std::string &openTime, const std::string &closeTime, bool ready) {
        try {
            Room room(id, name, openTime, closeTime, ready);
            roomTable.addRoom(room);

            undoStack.push([this, id]() {
                this->roomTable.deleteRoom(id); // Reverse: delete the room added
                std::cout << "Undo: Room with ID '" << id << "' has been deleted.\n";
            });

            std::cout << "Ruangan berhasil ditambahkan: " << room.toString() << "\n";
        } catch (const std::runtime_error &e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (...) {
            std::cerr << "Error: Terjadi kesalahan yang tidak diketahui.\n";
        }
    }

    void tambahReservasi(const Reservation &rsv) {
        if (!checkRoomExists(rsv.getRuangan())) {
            std::cerr << "Room does not exist: " << rsv.getRuangan() << "\n";
            return;
        }
        if (checkReservationConflict(rsv) || checkQueueConflict(rsv)) {
            throw std::runtime_error("Conflicting reservation exists for room " + rsv.getRuangan()
                                     + " at " + rsv.getTanggal() + " between "
                                     + rsv.getJamMulai() + " and " + rsv.getJamSelesai() + ".\n");
        }

        undoStack.push([this, id = rsv.getId()]() {
            this->reservationTable.erase(id); // Reverse: remove the reservation
            std::cout << "Undo: Reservation with ID '" << id << "' has been removed.\n";
        });

        reservationTable.push(rsv);
        std::cout << "Reservation added successfully!\n";
    }

    void deleteReservationById(const std::string &reservationId) {
        try {
            // Fetch the reservation using its ID
            auto reservationOpt = reservationTable.get_reservation_by_id(reservationId);

            // Ensure the reservation exists
            if (!reservationOpt.has_value()) {
                throw std::runtime_error("Error: Reservation with ID '" + reservationId + "' not found!");
            }

            // Extract the actual reservation from the optional
            Reservation reservationToDelete = reservationOpt.value();

            // Erase the reservation from the table
            reservationTable.erase(reservationId);

            // Push the reverse action for undo
            undoStack.push([this, reservationToDelete]() {
                this->reservationTable.push(reservationToDelete); // Restore the reservation
                std::cout << "Undo: Reservation with ID '" << reservationToDelete.getId() << "' has been restored.\n";
            });

            std::cout << "Reservation with ID '" << reservationId << "' has been successfully deleted.\n";

        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }


void deleteRoomById(const std::string &roomId) {
        try {
            std::optional<Room> roomToDelete;
            for (const auto &room: roomTable.getRooms()) {
                if (room.getId() == roomId) {
                    roomToDelete = room;
                    break;
                }
            }

            if (!roomToDelete) {
                throw std::runtime_error("Error: Room with ID '" + roomId + "' not found!");
            }

            roomTable.deleteRoom(roomId);

            undoStack.push([this, room = *roomToDelete]() {
                this->roomTable.addRoom(room);
                std::cout << "Undo: Room with ID '" << room.getId() << "' has been restored.\n";
            });

            std::cout << "Room with ID '" << roomId << "' has been successfully deleted.\n";
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    void undo() {
        if (undoStack.empty()) {
            std::cerr << "Error: Nothing to undo!\n";
            return;
        }

        auto lastAction = undoStack.peek();
        undoStack.pop();
        lastAction(); // Execute the undo action
    }

    void tampilkanTable() const {
        auto reservations = reservationTable.show_all();
        if (reservations.empty()) {
            std::cout << "No reservations in Reservation Table.\n";
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

    // implementasi queue yang wajib tapi sebenarnya kagak perlu
    // capek gweh
    void tambahReservasiKeAntrean(const Reservation &rsv) {
        if (!checkRoomExists(rsv.getRuangan())) {
            throw std::runtime_error("Room does not exist: " + rsv.getRuangan());
        }

        if (checkReservationConflict(rsv) || checkQueueConflict(rsv)) {
            throw std::runtime_error("Conflicting reservation exists for room " + rsv.getRuangan()
                                     + " at " + rsv.getTanggal() + " between "
                                     + rsv.getJamMulai() + " and " + rsv.getJamSelesai() + ".\n");
        }

        reservationQueue.enqueue_reservation(rsv);
        std::cout << "Reservation added to the queue successfully.\n";
    }

    void commitAntrean() {
        while (!reservationQueue.is_queue_empty()) {
            Reservation rsv = reservationQueue.dequeue_reservation();
            reservationTable.push(rsv);
            std::cout << "Reservation ID: " << rsv.getId() << " has been committed.\n";
        }
        std::cout << "All reservations from the queue have been committed.\n";
    }

    void tampilkanQueue() const {
        if (reservationQueue.is_queue_empty()) {
            std::cout << "No reservations in queue.\n";
            return;
        }

        size_t queueSize = reservationQueue.queue_size();
        std::cout << "Reservations in the queue (" << queueSize << "):\n";

        auto tempQueue = reservationQueue; // Create a temporary copy of the queue
        while (!tempQueue.is_queue_empty()) {
            Reservation rsv = tempQueue.dequeue_reservation();
            std::cout << "ID: " << rsv.getId()
                    << " | Name: " << rsv.getNama()
                    << " | Room: " << rsv.getRuangan()
                    << " | Date: " << rsv.getTanggal()
                    << " | Start: " << rsv.getJamMulai()
                    << " | End: " << rsv.getJamSelesai()
                    << " | Status: " << rsv.getStatus() << "\n";
        }
    }

    void clearQueue() {
        while (!reservationQueue.is_queue_empty()) {
            reservationQueue.dequeue_reservation();
        }
        std::cout << "The queue has been cleared.\n";
    }

    // aduh sorting lagi
    void sortReservationTable(const std::string &criteria) {
        try {
            reservationTable.sort_reservations(criteria);
            std::cout << "Reservations have been sorted by " << criteria << ".\n";
        } catch (const std::invalid_argument &e) {
            std::cerr << "Sorting error: " << e.what() << "\n";
        }
    }

    // implementasi permanence atau save/load system state
    void saveSystemState(const std::string &filename) const {
        nlohmann::json jsonData;
        jsonData["rooms"] = roomTable.to_json();
        jsonData["reservations"] = reservationTable.to_json();
        jsonData["queue"] = reservationQueue.to_json();

        io::saveToFile(filename, jsonData);
        std::cout << "System state has been saved to " << filename << ".\n";
    }

    void loadSystemState(const std::string &filename) {
        try {
            nlohmann::json jsonData = io::loadFromFile(filename);

            roomTable.from_json(jsonData.at("rooms"));
            reservationTable.from_json(jsonData.at("reservations"));
            reservationQueue.from_json(jsonData.at("queue"));

            std::cout << "System state has been successfully loaded from " << filename << ".\n";
        } catch (const nlohmann::json::exception &e) {
            std::cerr << "JSON parsing error: " << e.what() << "\n";
        } catch (const std::exception &e) {
            std::cerr << "Error loading system state: " << e.what() << "\n";
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
        auto reservations = reservationTable.get_reservation_by_id(rsv.getRuangan());
        for (const auto &res: reservations) {
            if (res.getTanggal() == rsv.getTanggal() &&
                !(rsv.getJamMulai() >= res.getJamSelesai() ||
                  rsv.getJamSelesai() <= res.getJamMulai())) {
                return true;
            }
        }
        return false;
    }

    bool checkQueueConflict(const Reservation &rsv) const {
        auto tempQueue = reservationQueue; // Create a temporary copy of the queue
        while (!tempQueue.is_queue_empty()) {
            Reservation queuedReservation = tempQueue.dequeue_reservation();
            if (queuedReservation.getRuangan() == rsv.getRuangan() &&
                queuedReservation.getTanggal() == rsv.getTanggal() &&
                !(rsv.getJamMulai() >= queuedReservation.getJamSelesai() ||
                  rsv.getJamSelesai() <= queuedReservation.getJamMulai())) {
                return true;
            }
        }
        return false;
    }
};
