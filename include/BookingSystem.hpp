#pragma once

#include "data_structures/Queue.hpp"
#include "Reservation.hpp"
#include <iostream>
class BookingSystem {
    Queue<Reservation> waitingQueue;

public:
    void tambahReservasi(const Reservation &rsv) {
            waitingQueue.enqueue(rsv);
        }

        void tampilkanAntrean() const {
            if (waitingQueue.empty()) {
                std::cout << "Antrean kosong" << std::endl;
                return;
            }

            Queue<Reservation> tempQueue = waitingQueue;
            int idx = 1;
            std::cout << "\nDaftar Antrean Reservasi:\n" << std::endl;

            while (!tempQueue.empty()) {
                const Reservation &rsv = tempQueue.peek();
                std::cout << idx << ". "
                        << "ID: " << rsv.getId()
                        << " | Nama: " << rsv.getNama()
                        << " | NIM: " << rsv.getNim()
                        << " | Ruangan: " << rsv.getRuangan()
                        << " | Tanggal: " << rsv.getTanggal()
                        << " | Waktu: " << rsv.getJamMulai() << "-" << rsv.getJamSelesai()
                        << " | Status: " << rsv.getStatus() << std::endl;
                tempQueue.dequeue();
                ++idx;
            }
            std::cout << std::endl;
        }
};