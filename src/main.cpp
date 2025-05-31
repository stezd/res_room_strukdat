#include "BookingSystem.hpp"
#include "Reservation.hpp"
#include "input_validator.hpp"
#include <iostream>
#include <string>

#include "../include/utils/utils.hpp"

template <typename Validator>
std::string promptInput(const std::string &promptMessage, Validator validator) {
    std::string input, errorMsg;
    while (true) {
        std::cout << promptMessage;
        std::getline(std::cin >> std::ws, input);
        if (validator(input, errorMsg)) {
            return input;
        }
        std::cout << "Error: " << errorMsg << "\n";
    }
}

int promptIntInput(const std::string &promptMessage, int min, int max) {
    int value;
    while (true) {
        std::cout << promptMessage;
        std::cin >> value;

        if (!std::cin.fail() && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
    }
}

std::pair<std::string, std::string> promptTimeRange() {
    std::string startTime, endTime, errorMsg;

    while (true) {
        startTime = promptInput("Enter Start Time (HH:MM): ", InputValidator::validateTime);
        endTime = promptInput("Enter End Time (HH:MM): ", InputValidator::validateTime);

        if (InputValidator::validateTimeRange(startTime, endTime)) {
            return {startTime, endTime};
        }
        std::cout << "Error: Start time must be earlier than end time.\n";
    }
}

void displayMenu() {
    std::cout << "\n========== Room Reservation System ==========\n";
    std::cout << "1. Enqueue Reservation\n";
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

    while (true) {
        displayMenu();
        int choice = promptIntInput("", 1, 10);

        if (choice == 1) {
            std::string name = promptInput("Enter Name: ", InputValidator::validateName);
            std::string nim = promptInput("Enter NIM (Numeric ID): ", InputValidator::validateNIM);
            std::string room = promptInput("Enter Room: ", InputValidator::validateNotEmpty);
            std::string date = promptInput("Enter Date (YYYY-MM-DD): ", InputValidator::validateDate);
            auto [startTime, endTime] = promptTimeRange();

            try {
                Reservation rsv("", name, nim, room, date, startTime, endTime, "Waiting");
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
            std::string id = promptInput("Enter Room ID: ", InputValidator::validateNotEmpty);
            std::string name = promptInput("Enter Room Name: ", InputValidator::validateName);
            auto [openTime, closeTime] = promptTimeRange();
            bool ready = promptIntInput("Is the room ready? (1=Yes, 0=No): ", 0, 1);

            try {
                bookingSystem.tambahRuangan(id, name, openTime, closeTime, ready);
                std::cout << "Room successfully added!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 5) {
            std::cout << bookingSystem.getRoomTable();

        } else if (choice == 6) {
            std::string roomId = promptInput("Enter Room ID to delete: ", InputValidator::validateNotEmpty);
            try {
                bookingSystem.deleteRoomById(roomId);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 7) {
            std::string filename = promptInput("Enter filename to save: ", InputValidator::validateNotEmpty);
            try {
                bookingSystem.saveSystemState(filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 8) {
            std::string filename = promptInput("Enter filename to load: ", InputValidator::validateNotEmpty);
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
        }
    }

    return 0;
}