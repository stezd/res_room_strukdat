#ifndef BOOKINGSYSTEM_HPP
#define BOOKINGSYSTEM_HPP

#include <queue>
#include "Reservation.hpp"

class BookingSystem {
private:
    std::queue<Reservation> waitingQueue;

public:
    void tambahReservasi(const Reservation &rsv);

    void tampilkanAntrean() const;
};

#endif
