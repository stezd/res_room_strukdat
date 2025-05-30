#pragma once

#include "data_structures/Queue.hpp"
#include "Reservation.hpp"

class BookingSystem {
    Queue<Reservation> waitingQueue;

public:
    void tambahReservasi(const Reservation &rsv) {
        waitingQueue.enqueue(rsv);
    }

    Queue<Reservation> getAntrean() const {
        return waitingQueue;
    }

    bool isAntreanKosong() const {
        return waitingQueue.empty();
    }

    Reservation prosesReservasi() {
        if (waitingQueue.empty()) {
            throw std::runtime_error("Antrean kosong");
        }
        Reservation rsv = waitingQueue.peek();
        waitingQueue.dequeue();
        return rsv;
    }
};