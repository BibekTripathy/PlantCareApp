# PlantCareApp

**PlantCareApp** is a Qt6 desktop application that helps you monitor and manage your indoor plants. It uses an `sqlite3` database to store detailed information about each plant, including its name, type, watering schedule, health status, and last care date.

---

## Features

* Add, edit, and delete plant records
* Monitor plant health
* Data persisted using a local SQLite3 database
* Cross-platform GUI built with Qt6

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
git clone https://github.com/BibekTripathy/PlantCareApp.git
cd PlantCareApp

# Create build directory
mkdir build
cd build

# Configure cmake
cmake ..

# Build the program
cmake --build .

# Run the program
./bin/PlantCareApp
```

---

## Screenshots

*(T.B.A)*

> ![image_stub](/path/to/screenshot.jpg)

---

## Reporting Issues

If you encounter any bugs or have suggestions for improvements, please open an issue on the [GitHub Issues page](https://github.com/BibekTripathy/PlantCareApp/issues).

---

## License

This project is licensed under the GPL-3.0 License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgements

* Developed using the **Qt6** framework
* Data powered by **SQLite3**
* Inspired by the love for indoor gardening 🌱

---
