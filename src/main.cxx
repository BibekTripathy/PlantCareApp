#include "plant.hxx"
#include <QApplication>
#include <QFileDialog>
#include <QString>
#include <ctime>
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  std::cout << "Welcome to PlantCareApp.\n";
  Plants plants;
  std::cout
      << "Press Enter to select the database file to fetch the data from: "
      << std::flush;
  std::cin.get();

  QApplication app(argc, argv);

  /* Open file-picker to handle input for file address */
  QString qFilePath = QFileDialog::getOpenFileName(
      nullptr, "Select SQLite Database", "",
      "SQLite Database (*.db *.sqlite *.sqlite3);;All Files (*)");
  if (qFilePath.isEmpty()) {
    // User cancelled
    return 0;
  }

  std::string filePath = qFilePath.toStdString();

  /* Old cli-only input handling for file address */
  // std::string filePath{""};
  // std::cout << "Enter address of database (/path/to/database.db): " <<
  // std::flush; getline(std::cin, filePath);
  plants.fetchData(filePath);

  while (true) {
    std::cout << "1 - Show Plant Details\n"
              << "2 - Add New Plant\n"
              << "3 - Edit Plant\n"
              << "4 - Remove Plant\n"
              << "5 - Filter Plants\n"
              << "6 - Save & Exit\n"
              //<< "7 - Exit without Saving\n"
              << "Enter choice: " << std::flush;
    char choice{'\0'};
    std::cin >> choice;
    std::cin.ignore();
    std::cout << "\n";

    switch (choice) {
    case '1': {
      plants.showDetails();
      break;
    }

    case '2': {
      plants.addPlant();
      break;
    }

    case '3': {
      plants.editPlant();
      break;
    }

    case '4': {
      int plantId{0};
      std::cout << "Enter the plant ID: " << std::flush;
      std::cin >> plantId;
      plants.removePlant(plantId);
      break;
    }

    case '5': {
      std::cout << "\nFilter-by Options:\n"
                << "1 - Name/Species\n"
                << "2 - Health-Status\n"
                << "3 - Species\n"
                << "Enter choice: " << std::flush;
      char searchChoice{'\0'};
      std::cin >> searchChoice;
      std::cin.ignore();

      switch (searchChoice) {
      case '1': {
        std::string query;
        std::cout << "Enter Name/Species: ";
        std::getline(std::cin, query);
        plants.searchPlants(query);
        break;
      }

      case '2': {
        std::string healthStatus;
        std::cout << "Enter Health-Status (e.g., healthy): ";
        std::getline(std::cin, healthStatus);
        plants.filterByHealth(healthStatus);
        break;
      }

      case '3': {
        std::string species;
        std::cout << "Enter Species: ";
        std::getline(std::cin, species);
        plants.filterBySpecies(species);
        break;
      }

      default: {
        std::cerr << "Invalid Filter option\n";
      }
      }
      break;
    }
    case '6': {
      plants.writeData(filePath);
      std::cout << "Changes have been Saved.\nThanks for using PlantCareApp."
                << std::endl;
      return 0;
    }

      /*case '7': {
              std::cout << "Exiting without Saving.\nThanks for using
      PlantCareApp." << std::endl; return 0;
      } */

    default: {
      std::cerr << "Invalid Choice!\n";
      break;
    }
    }
  }
  return 0;
}
