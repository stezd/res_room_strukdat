#ifndef BOOKINGSYSTEM_HPP
#define BOOKINGSYSTEM_HPP

#include "data_structures/Queue.hpp"
#include "Reservation.hpp"

class BookingSystem {
private:
    Queue<Reservation> waitingQueue;

public:
    void tambahReservasi(const Reservation &rsv);

    void tampilkanAntrean() const;
};

#endif
