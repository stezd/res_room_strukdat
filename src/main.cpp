#include "BookingSystem.hpp"
#include "Reservation.hpp"
#include <iostream>
#include <string>

#include "../include/utils/utils.hpp"

void displayMenu() {
    std::cout << "\n========== Room Reservation System ==========\n";
    std::cout << "1. Add Reservation\n";
    std::cout << "2. Display Queue\n";
    std::cout << "3. Commit Queue (Finalize Reservations)\n";
    std::cout << "4. Add Room\n";
    std::cout << "5. View Room List\n";
    std::cout << "6. Delete Room\n";
    std::cout << "7. Save System (Save to File)\n";
    std::cout << "8. Load System (Load from File)\n";
    std::cout << "9. Clear Queue\n";
    std::cout << "10. Exit\n";
    std::cout << "=============================================\n";
    std::cout << "Choice: ";
}

int main() {
    RoomTabular initialRooms;
    BookingSystem bookingSystem(initialRooms);

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 1) {
            std::string name, id, room, date, startTime, endTime;
            std::cout << "Enter Name: ";
            std::getline(std::cin >> std::ws, name);
            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "Enter Room: ";
            std::cin >> room;
            std::cout << "Enter Date (YYYY-MM-DD): ";
            std::cin >> date;
            std::cout << "Enter Start Time (HH:MM): ";
            std::cin >> startTime;
            std::cout << "Enter End Time (HH:MM): ";
            std::cin >> endTime;

            try {
                Reservation rsv("", name, id, room, date, startTime, endTime, "Waiting");
                rsv.setId(generateBookingCode(rsv));
                bookingSystem.tambahReservasiKeAntrean(rsv);
                std::cout << "Reservation successfully added to queue!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            bookingSystem.tampilkanQueue();

        } else if (choice == 3) {
            try {
                bookingSystem.commitAntrean();
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 4) {
            std::string id, name, openTime, closeTime;
            bool ready;
            std::cout << "Enter Room ID: ";
            std::cin >> id;
            std::cout << "Enter Room Name: ";
            std::getline(std::cin >> std::ws, name);
            std::cout << "Enter Opening Time (HH:MM): ";
            std::cin >> openTime;
            std::cout << "Enter Closing Time (HH:MM): ";
            std::cin >> closeTime;
            std::cout << "Is the room ready? (1 = Yes, 0 = No): ";
            std::cin >> ready;

            try {
                bookingSystem.tambahRuangan(id, name, openTime, closeTime, ready);
                std::cout << "Room successfully added!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 5) {
            std::cout << bookingSystem.getRoomTable();

        } else if (choice == 6) {
            std::string roomId;
            std::cout << "Enter Room ID to delete: ";
            std::cin >> roomId;

            try {
                bookingSystem.deleteRoomById(roomId);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 7) {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::cin >> filename;

            try {
                bookingSystem.saveSystemState(filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 8) {
            std::string filename;
            std::cout << "Enter filename to load: ";
            std::cin >> filename;

            try {
                bookingSystem.loadSystemState(filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 9) {
            bookingSystem.clearQueue();
            std::cout << "The queue has been cleared.\n";

        } else if (choice == 10) {
            std::cout << "Thank you for using the Room Reservation System!\n";
            break;

        } else {
            std::cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}