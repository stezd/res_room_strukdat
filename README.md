# Room Reservation System

This project implements a **Room Reservation System** in C++ with support for **object permanence** using JSON serialization. It allows users to manage rooms and reservations through an interactive command-line interface.

## Features

- **Room Management**:
    - Add, view, and manage room details (ID, name, operating hours, availability status).
    - Save and restore room data to/from JSON.

- **Reservation Management**:
    - Add reservations with details (name, NIM, room, date, time, and status).
    - Save and restore reservations to/from JSON files.

- **Object Permanence**:
    - Data is stored persistently in JSON files and can be reloaded across application runs.

- **Interactive CLI**:
    - Menu-driven system for an intuitive user experience.

## Example Workflow

1. Add rooms to the system.
2. Add a reservation by selecting a room, providing user details, and entering the time slot.
3. Save data to JSON files:
    - Rooms are saved to `rooms.json`.
    - Reservations are saved to `reservations.json`.
4. Reload the data on subsequent application runs, preserving changes.

## Compilation and Requirements
### Prerequisites
1. **C++ Compiler**
    - A compiler supporting at least **C++17** (e.g., `g++`, `clang++`, MSVC).
    - Ensure your environment variables are correctly set up for the compiler.

2. **CMake**
    - CMake (version 3.16 or newer) for building the project.
    - Download and install CMake from [here](https://cmake.org/download/).

3. **nlohmann/json Library**
    - The library is used for JSON handling.
    - You can add it to the project via vcpkg or manually include the single header file.

### Setting Up the JSON Library
#### Option 1: Using vcpkg (Recommended)
1. Install **vcpkg** by following the instructions [here](https://github.com/microsoft/vcpkg).
2. Install the `nlohmann-json` library using the following command:
``` bash
   vcpkg install nlohmann-json
```
1. Link vcpkg to your build system. For example:
``` bash
   cmake -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake ..
```
#### Option 2: Add the Single Header Manually
1. Download the `json.hpp` header from the [nlohmann/json GitHub repository](https://github.com/nlohmann/json).
2. Place the `json.hpp` file in your project's include directory.

### Compilation Steps
#### If Using CMake:
1. Clone the project or extract the files to your working directory.
``` bash
   git clone https://github.com/your-repository/room-reservation-system.git
   cd room-reservation-system
```
1. Create a build directory:
``` bash
   mkdir build && cd build
```
1. Generate build files using CMake:
``` bash
   cmake ..
```
1. Build the project:
``` bash
   cmake --build .
```
#### If Manually Compiling with g++:
1. Use the following command to compile the project:
``` bash
   g++ -std=c++17 -Ipath/to/json/include -o main main.cpp
```
Replace `path/to/json/include` with the directory containing the `json.hpp` header.
### Running the Application
After building the project, you can run the compiled executable:
``` bash
./main
```
Follow the interactive menu to add reservations, display room information, and more.

## License

This project is provided under MIT. Feel free to use and modify.
