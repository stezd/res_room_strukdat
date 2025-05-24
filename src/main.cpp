#include "BookingSystem.hpp"
#include "Reservation.hpp"
#include <iostream>
#include <string>

#include "utils.hpp"

int main() {
    BookingSystem bookingSystem;
    int choice;

    while (true) {
        std::cout << "\nSistem Reservasi Ruangan\n";
        std::cout << "1. Tambah Reservasi\n";
        std::cout << "2. Tampilkan Antrean\n";
        std::cout << "3. Keluar\n";
        std::cout << "Pilihan: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string id, nama, nim, ruangan, tanggal, jamMulai, jamSelesai;
            std::cout << "Masukkan Nama: ";
            std::getline(std::cin >> std::ws, nama);
            std::cout << "Masukkan NIM: ";
            std::cin >> nim;
            std::cout << "Masukkan Ruangan: ";
            std::cin >> ruangan;
            std::cout << "Masukkan Tanggal: ";
            std::cin >> tanggal;
            std::cout << "Masukkan Jam Mulai: ";
            std::cin >> jamMulai;
            std::cout << "Masukkan Jam Selesai: ";
            std::cin >> jamSelesai;

            Reservation rsv("", nama, nim, ruangan, tanggal, jamMulai, jamSelesai, "Menunggu");
            rsv.setId(generateBookingCode(rsv));
            bookingSystem.tambahReservasi(rsv);
            std::cout << "Reservasi berhasil ditambahkan!\n";
        } else if (choice == 2) {
            bookingSystem.tampilkanAntrean();
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
