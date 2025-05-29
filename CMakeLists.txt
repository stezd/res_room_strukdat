cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(res_room_strukdat)

set(CMAKE_CXX_STANDARD 20)
find_package(nlohmann_json CONFIG REQUIRED)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_SOURCE_DIR}/include/data_structures)


add_executable(res_room_strukdat src/main.cpp
        src/Reservation.cpp
        src/BookingSystem.cpp
        src/utils.cpp
        include/data_structures/Stack.hpp
)

target_link_libraries(res_room_strukdat PRIVATE nlohmann_json::nlohmann_json)