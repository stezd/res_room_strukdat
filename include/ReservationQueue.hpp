#pragma once

#include "Reservation.hpp"
#include <Queue.hpp>

class ReservationQueue {
    Queue<Reservation> reservationQueue;

public:
    void enqueue_reservation(const Reservation &rsv) {
        reservationQueue.enqueue(rsv);
    }

    Reservation dequeue_reservation() {
        if (reservationQueue.empty()) {
            throw std::runtime_error("No reservations in the queue");
        }

        Reservation front_reservation = reservationQueue.peek();
        reservationQueue.dequeue();
        return front_reservation;
    }

    Reservation peek_reservation() const  {
        if (reservationQueue.empty()) {
            throw std::runtime_error("No reservations in the queue");
        }
        return reservationQueue.peek();
    }


    size_t queue_size() const {
        return reservationQueue.size();
    }

    bool is_queue_empty() const {
        return reservationQueue.empty();
    }
};