#pragma once

#include "Reservation.hpp"
#include <string>
#include <Queue.hpp>

class ReservationQueue {
    Queue<Reservation> ReservationQueue;

public:
    void enqueue_reservation(const Reservation &rsv) {
        ReservationQueue.enqueue(rsv);
    }

    Reservation dequeue_reservation() {
        if (ReservationQueue.empty()) {
            throw std::runtime_error("No reservations in the queue");
        }

        Reservation front_reservation = ReservationQueue.peek();
        ReservationQueue.dequeue();
        return front_reservation;
    }

    Reservation peek_reservation() const  {
        if (ReservationQueue.empty()) {
            throw std::runtime_error("No reservations in the queue");
        }
        return ReservationQueue.peek();
    }


    size_t queue_size() const {
        return ReservationQueue.size();
    }

    bool is_queue_empty() const {
        return ReservationQueue.empty();
    }
};