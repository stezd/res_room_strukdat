#include "BookingSystem.hpp"
#include "Reservation.hpp"
#include <iostream>
#include <string>

#include "../include/utils/utils.hpp"

void displayMenu() {
    std::cout << "\n========== Sistem Reservasi Ruangan ==========\n";
    std::cout << "1. Tambah Reservasi\n";
    std::cout << "2. Tampilkan Antrean\n";
    std::cout << "3. Commit Antrean (Jadikan Reservasi Tetap)\n";
    std::cout << "4. Tambah Ruangan\n";
    std::cout << "5. Lihat Daftar Ruangan\n";
    std::cout << "6. Hapus Ruangan\n";
    std::cout << "7. Simpan Sistem (Save to File)\n";
    std::cout << "8. Muat Sistem (Load from File)\n";
    std::cout << "9. Bersihkan Antrean\n";
    std::cout << "10. Keluar\n";
    std::cout << "===============================================\n";
    std::cout << "Pilihan: ";
}

int main() {
    RoomTabular initialRooms;
    BookingSystem bookingSystem(initialRooms);

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 1) {
            // Add a new reservation
            std::string nama, nim, ruangan, tanggal, jamMulai, jamSelesai;
            std::cout << "Masukkan Nama: ";
            std::getline(std::cin >> std::ws, nama);
            std::cout << "Masukkan NIM: ";
            std::cin >> nim;
            std::cout << "Masukkan Ruangan: ";
            std::cin >> ruangan;
            std::cout << "Masukkan Tanggal (YYYY-MM-DD): ";
            std::cin >> tanggal;
            std::cout << "Masukkan Jam Mulai (HH:MM): ";
            std::cin >> jamMulai;
            std::cout << "Masukkan Jam Selesai (HH:MM): ";
            std::cin >> jamSelesai;

            try {
                Reservation rsv("", nama, nim, ruangan, tanggal, jamMulai, jamSelesai, "Menunggu");
                rsv.setId(generateBookingCode(rsv));
                bookingSystem.tambahReservasiKeAntrean(rsv);
                std::cout << "Reservasi berhasil ditambahkan ke antrean!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 2) {
            // Display the reservation queue
            bookingSystem.tampilkanQueue();

        } else if (choice == 3) {
            // Commit reservations in the queue
            bookingSystem.commitAntrean();

        } else if (choice == 4) {
            // Add a new room
            std::string id, name, openTime, closeTime;
            bool ready;
            std::cout << "Masukkan ID Ruangan: ";
            std::cin >> id;
            std::cout << "Masukkan Nama Ruangan: ";
            std::getline(std::cin >> std::ws, name);
            std::cout << "Masukkan Jam Buka (HH:MM): ";
            std::cin >> openTime;
            std::cout << "Masukkan Jam Tutup (HH:MM): ";
            std::cin >> closeTime;
            std::cout << "Apakah ruangan siap digunakan? (1 = Ya, 0 = Tidak): ";
            std::cin >> ready;

            try {
                bookingSystem.tambahRuangan(id, name, openTime, closeTime, ready);
                std::cout << "Ruangan berhasil ditambahkan!\n";
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 5) {
            // Display all rooms
            std::cout << bookingSystem.getRoomTable();

        } else if (choice == 6) {
            // Delete a room
            std::string roomId;
            std::cout << "Masukkan ID Ruangan yang ingin dihapus: ";
            std::cin >> roomId;

            try {
                bookingSystem.deleteRoomById(roomId);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 7) {
            // Save system state to file
            std::string filename;
            std::cout << "Masukkan nama file untuk disimpan: ";
            std::cin >> filename;

            try {
                bookingSystem.saveSystemState(filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 8) {
            std::string filename;
            std::cout << "Masukkan nama file untuk dimuat: ";
            std::cin >> filename;

            try {
                bookingSystem.loadSystemState(filename);
            } catch (const std::exception &e) {
                std::cerr << "Error: " << e.what() << "\n";
            }

        } else if (choice == 9) {
            // Clear the reservation queue
            bookingSystem.clearQueue();
            std::cout << "Antrean telah dibersihkan.\n";

        } else if (choice == 10) {
            // Exit the application
            std::cout << "Terima kasih telah menggunakan Sistem Reservasi Ruangan!\n";
            break;

        } else {
            std::cout << "Pilihan tidak valid! Silakan coba lagi.\n";
        }
    }

    return 0;
}