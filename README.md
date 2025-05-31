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

## Updated Compilation and Requirements

### Prerequisites

1. **C++ Compiler**
    - **C++20 Standard Support** required. Ensure you have a compatible compiler:
        - `g++` (version 10 or newer)
        - `clang++` (version 10 or newer)
        - **MSVC** (Visual Studio 2019 or newer)
    - Properly set up your environment variables for the selected compiler.

2. **CMake**
    - Version **3.5** or higher. Download and install from [here](https://cmake.org/download/).

3. **nlohmann/json Library**
    - Utilized for JSON data manipulation:
        - Automatically fetched and configured via **CMake FetchContent**.
    - Alternatively, you can manually integrate it by following the manual setup instructions below.

### Setting Up the Project

#### Option 1: Fully Automated Setup (Recommended)
The provided `CMakeLists.txt` already fetches and integrates the **nlohmann/json** library. Ensure that you have an active internet connection for the first build.

#### Option 2: Manual Setup for **nlohmann/json**
1. Download the library:
    - Fetch the **single header file** `json.hpp` from the [nlohmann/json GitHub repository](https://github.com/nlohmann/json).
2. Place it in your `include/` directory (under `include/utils` is recommended).
3. Adjust the `CMakeLists.txt` file if necessary to include the manual path, or directly include the file in your sources.

### Compilation Instructions

#### Building with CMake
1. Clone or download the project:
   ```bash
   git clone https://github.com/your-repository/room-reservation-system.git
   cd room-reservation-system
   ```
2. Execute this line of command
   ```bash
   cmake -S . -B build

   ```
3. Build with:
   ```bash
   cmake --build build
   ```
4. Navigate to your executable.
   ```bash
   cd .\build\build\Debug\
   ```
5. Run your application
    ```bash
    .\res_room_strukdat.exe
    ```
## License

This project is provided under MIT. Feel free to use and modify.
