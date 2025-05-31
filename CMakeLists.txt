cmake_minimum_required(VERSION 3.5)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(res_room_strukdat)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
find_package(nlohmann_json CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Define the main executable first
add_executable(res_room_strukdat src/main.cpp)

# Add include directories for the main executable
target_include_directories(res_room_strukdat PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
        ${PROJECT_SOURCE_DIR}/include/data_structures
        ${PROJECT_SOURCE_DIR}/include/utils)

# Link the libraries required for the main executable
target_link_libraries(res_room_strukdat PRIVATE nlohmann_json::nlohmann_json)

# Define the test target
add_executable(test_res_room tests/test_main.cpp)

# Link Google Test and other necessary libraries to the test target
target_link_libraries(test_res_room PRIVATE GTest::gtest GTest::gtest_main nlohmann_json::nlohmann_json)

# Register the test
add_test(NAME ExampleTests COMMAND test_res_room)