cmake_minimum_required(VERSION 3.20)
project(res_room_strukdat LANGUAGES CXX)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)
# Main application target
add_executable(res_room_strukdat
        src/main.cpp
)

# Add include directories for the main application
target_include_directories(res_room_strukdat PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/data_structures
        ${PROJECT_SOURCE_DIR}/include/utils
)

# Link libraries for the main application
target_link_libraries(res_room_strukdat PRIVATE nlohmann_json::nlohmann_json
)

set_target_properties(res_room_strukdat PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
)