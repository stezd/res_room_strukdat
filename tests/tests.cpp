#include <gtest/gtest.h>
#include "../include/BookingSystem.hpp"
#include "../include/RoomTabular.hpp"
#include "../include/Reservation.hpp"

// Test adding a room to the system
TEST(RoomTabularTests, AddRoom) {
    RoomTabular roomTabular;

    Room room("101", "Conference Hall", "08:00", "20:00", true);
    roomTabular.addRoom(room);

    const auto &rooms = roomTabular.getRooms();
    ASSERT_EQ(rooms.size(), 1);
    EXPECT_EQ(rooms[0].getId(), "101");
    EXPECT_EQ(rooms[0].getName(), "Conference Hall");
    EXPECT_TRUE(rooms[0].isReady());
}

// Test deleting a room from the system
TEST(RoomTabularTests, DeleteRoom) {
    RoomTabular roomTabular;
    roomTabular.addRoom(Room("202", "Meeting Room", "08:00", "18:00", true));

    roomTabular.deleteRoom("202");

    EXPECT_EQ(roomTabular.getRooms().size(), 0);
}

// Test adding a reservation to the queue
TEST(BookingSystemTests, AddReservationToQueue) {
    RoomTabular roomTabular;
    roomTabular.addRoom(Room("301", "Library Room", "09:00", "17:00", true));
    BookingSystem bookingSystem(roomTabular);

    Reservation rsv("", "Test User", "12345", "301", "2023-10-25", "10:00", "11:00", "Waiting");
    rsv.setId("RES001");

    bookingSystem.tambahReservasiKeAntrean(rsv);

    // Display the queue to check the reservation
    testing::internal::CaptureStdout();
    bookingSystem.tampilkanQueue();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("ID: RES001") != std::string::npos);
}

// Test detecting conflicting reservations
TEST(BookingSystemTests, DetectReservationConflict) {
    RoomTabular roomTabular;
    roomTabular.addRoom(Room("402", "Lab Room", "09:00", "17:00", true));
    BookingSystem bookingSystem(roomTabular);

    Reservation rsv1("", "User1", "11111", "402", "2023-10-26", "10:00", "11:00", "Waiting");
    rsv1.setId("RES002");
    bookingSystem.tambahReservasiKeAntrean(rsv1);

    // Add a conflicting reservation
    Reservation rsv2("", "User2", "22222", "402", "2023-10-26", "10:30", "11:30", "Waiting");
    rsv2.setId("RES003");

    testing::internal::CaptureStdout();
    bookingSystem.tambahReservasiKeAntrean(rsv2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Conflicting reservation exists") != std::string::npos);
}

// Test saving the system state
TEST(BookingSystemTests, SaveSystemState) {
    RoomTabular roomTabular;
    roomTabular.addRoom(Room("501", "Event Room", "10:00", "22:00", false));
    BookingSystem bookingSystem(roomTabular);

    Reservation rsv("", "Test User", "54321", "501", "2023-10-28", "12:00", "13:00", "Confirmed");
    rsv.setId("RES004");
    bookingSystem.tambahReservasi(rsv);

    testing::internal::CaptureStdout();
    bookingSystem.saveSystemState("test_state.json");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("System state has been saved") != std::string::npos);
}

// Test loading the system state
TEST(BookingSystemTests, LoadSystemState) {
    RoomTabular roomTabular;
    BookingSystem bookingSystem(roomTabular);

    testing::internal::CaptureStdout();
    bookingSystem.loadSystemState("test_state.json");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("System state has been successfully loaded") != std::string::npos);
}