#pragma once

#include "Reservation.hpp"
#include <Queue.hpp>
#include <nlohmann/json.hpp>

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

    nlohmann::json to_json() const {
        nlohmann::json jsonArray = nlohmann::json::array();

        auto tempQueue = reservationQueue;
        while (!tempQueue.empty()) {
            jsonArray.push_back(tempQueue.peek().to_json());
            tempQueue.dequeue();
        }

        return jsonArray;
    }

    void from_json(const nlohmann::json &jsonArray) {
        for (const auto &item : jsonArray) {
            Reservation reservation = Reservation::from_json(item);
            enqueue_reservation(reservation);
        }
    }

};