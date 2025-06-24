# QtPlantly

<div align="center">
  <img src="https://raw.githubusercontent.com/BibekTripathy/QtPlantly/refs/heads/main/assets/icons/qtplantly.png" alt="qtplantly" width="200"/>
</div>

**QtPlantly** is a Qt6 desktop application that helps you monitor and manage your indoor plants. It uses an `sqlite3` database to store detailed information about each plant, including its name, type, watering schedule, health status, and last care date.

---

## Screenshots

> ![QtPlantly_Preview_Screenshot](https://raw.githubusercontent.com/BibekTripathy/QtPlantly/refs/heads/main/assets/media/QtPlantly_Preview_Screenshot.png)

---

## Features

* Add, edit, and delete plant records
* Search & Filter through plants
* Monitor plant health
* Data persisted using a local SQLite3 database
* Supports multiple databases
* Cross-platform GUI built with Qt6

---

## Installation

### Windows
- Go into [Releases](https://github.com/BibekTripathy/QtPlantly/releases) and download the .zip file for Windows
- Extract it into an appropriate directory
- Run `QtPlantly.exe` to start the application

### Linux
- Go into [Releases](https://github.com/BibekTripathy/QtPlantly/releases) and download the .zip file for Linux
- Extract it into an appropriate directory
- Make sure to have `Qt6` and `Sqlite3` installed from your Distro's package manager
- Run `QtPlantly` to start the application

---

## Build Instructions

### Dependencies

Ensure the following are installed on your system:

* [Qt6](https://www.qt.io/)
* [SQLite3](https://sqlite.org/index.html)
* [CMake](https://cmake.org/) (version 3.16+ recommended)
* A C++17 compatible compiler

### Steps

```sh
# Clone the repository
git clone https://github.com/BibekTripathy/QtPlantly.git
cd QtPlantly

# Create build directory
mkdir build
cd build

# Configure cmake
cmake ..

# Build the program
cmake --build .

# Run the program
./bin/QtPlantly
```

---

## Reporting Issues

If you encounter any bugs or have suggestions for improvements, please open an issue on the [GitHub Issues page](https://github.com/BibekTripathy/QtPlantly/issues).

---

## License

This project is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

* Developed using the **Qt6** framework
* Data powered by **SQLite3**
* Inspired by the love for indoor gardening 🌱

---
