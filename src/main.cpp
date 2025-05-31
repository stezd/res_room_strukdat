#include "BookingSystem.hpp"
#include "Reservation.hpp"
#include "input_validator.hpp"
#include <iostream>
#include <string>
#include <memory>

#include "../include/utils/utils.hpp"

template<typename Validator>
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear remaining characters
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
    }
}

std::pair<std::string, std::string> promptTimeRange() {
    auto startTime = std::make_unique<std::string>();
    auto endTime = std::make_unique<std::string>();
    auto errorMsg = std::make_unique<std::string>();

    while (true) {
        *startTime = promptInput("Enter Start Time (HH:MM): ", InputValidator::validateTime);
        *endTime = promptInput("Enter End Time (HH:MM): ", InputValidator::validateTime);

        if (InputValidator::validateTimeRange(*startTime, *endTime, *errorMsg)) {
            return {*startTime, *endTime};
        }
        std::cout << "Error: " << *errorMsg << "\n";
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
    std::cout << "10. View Reservation Table\n";
    std::cout << "11. Sort Reservation Table\n";
    std::cout << "12. Delete Reservation by ID\n";\
    std::cout << "13. Undo Action\n";
    std::cout << "14. Exit\n";
    std::cout << "=============================================\n";
    std::cout << "Choice: ";
}

int main() {
    auto initialRooms = std::make_unique<RoomTabular>();
    auto bookingSystem = std::make_unique<BookingSystem>(*initialRooms);

    auto defaultFilename = std::make_unique<std::string>("save.json");
    try {
        bookingSystem->loadSystemState(*defaultFilename);
        std::cout << "System state auto-loaded from " << *defaultFilename << ".\n";
    } catch (const std::exception &) {
    }

    while (true) {
        displayMenu();
        int choice = promptIntInput("", 1, 13);

        if (choice == 1) {
            auto name = std::make_unique<std::string>(promptInput("Enter Name: ", InputValidator::validateName));
            auto nim = std::make_unique<std::string>(
                promptInput("Enter NIM (Numeric ID): ", InputValidator::validateNIM));
            auto room = std::make_unique<std::string>(promptInput("Enter Room: ", InputValidator::validateNotEmpty));
            auto date = std::make_unique<std::string>(
                promptInput("Enter Date (YYYY-MM-DD): ", InputValidator::validateDate));
            auto [startTime, endTime] = promptTimeRange();

            try {
                auto rsv = std::make_unique<Reservation>("", *name, *nim, *room, *date, startTime, endTime, "Waiting");
                rsv->setId(generateBookingCode(*rsv));
                bookingSystem->tambahReservasiKeAntrean(*rsv);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 2) {
            bookingSystem->tampilkanQueue();
        } else if (choice == 3) {
            try {
                bookingSystem->commitAntrean();
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 4) {
            auto id = std::make_unique<std::string>(promptInput("Enter Room ID: ", InputValidator::validateNotEmpty));
            auto name = std::make_unique<std::string>(promptInput("Enter Room Name: ", InputValidator::validateName));
            auto [openTime, closeTime] = promptTimeRange();
            bool ready = promptIntInput("Is the room ready? (1=Yes, 0=No): ", 0, 1);

            try {
                bookingSystem->tambahRuangan(*id, *name, openTime, closeTime, ready);
                std::cout << "Room successfully added!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 5) {
            std::cout << bookingSystem->getRoomTable();
        } else if (choice == 6) {
            auto roomId = std::make_unique<std::string>(
                promptInput("Enter Room ID to delete: ", InputValidator::validateNotEmpty));
            try {
                bookingSystem->deleteRoomById(*roomId);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 7) {
            auto filename = std::make_unique<std::string>(
                promptInput("Enter filename to save: ", InputValidator::validateNotEmpty));
            try {
                bookingSystem->saveSystemState(*filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 8) {
            auto filename = std::make_unique<std::string>(
                promptInput("Enter filename to load: ", InputValidator::validateNotEmpty));
            try {
                bookingSystem->loadSystemState(*filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 9) {
            bookingSystem->clearQueue();
            std::cout << "The queue has been cleared.\n";
        } else if (choice == 10) {
            bookingSystem->tampilkanTable();
        } else if (choice == 11) {
            std::cout << "Sort by:\n";
            std::cout << "1. Date\n";
            std::cout << "2. Start Time\n";
            std::cout << "3. Room Name\n";
            int sortChoice = promptIntInput("Enter sort criteria (1-3): ", 1, 3);

            std::string criteria;
            switch (sortChoice) {
                case 1: criteria = "date";
                    break;
                case 2: criteria = "jammulai";
                    break;
                case 3: criteria = "name";
                    break;
                default: criteria = "date";
                    break;
            }

            try {
                bookingSystem->sortReservationTable(criteria);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 12) {
            auto reservationId = std::make_unique<std::string>(
                promptInput("Enter Reservation ID to delete: ", InputValidator::validateNotEmpty));
            try {
                bookingSystem->deleteReservationById(*reservationId);
                std::cout << "Reservation successfully deleted!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        } else if (choice == 14) {
            std::cout << "Thank you for using the Room Reservation System!\n";
            break;
        } else if (choice == 13) {
            try {
                bookingSystem->undo();
                std::cout << "Undo operation performed.\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }

    return 0;
}
