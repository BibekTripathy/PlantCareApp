#include <iostream>
#include <QApplication>
#include <QFileDialog>
#include <QString>
#include <sqlite3.h>
#include <string>
#include "plant.hxx"
#include "mainWindow.hxx"

int main(int argc, char *argv[]) {
	// std::cout
	// 	<< "Welcome to PlantCareApp.\n"
	// 	<< "Press Enter to select the database file to fetch the data from: "
	// 	<< std::flush;
	// std::cin.get();

	QApplication app(argc, argv);
	MainWindow window;
	window.show();

	/* Main method needs to be rewritten to adjust flow of actions
	 * due to change in paradigm of code functioning. */
	/*
	std::string filePath = window.getAddress();

	Plants plants;
	plants.fetchData(filePath);

	while (true) {
		std::cout
			<< "1 - Show Plant Details\n"
			<< "2 - Add New Plant\n"
			<< "3 - Edit Plant\n"
			<< "4 - Remove Plant\n"
			<< "5 - Filter Plants\n"
			<< "6 - Save & Exit\n"
			<< "Enter choice: "
			<< std::flush;
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
				std::cout
					<< "\nFilter-by Options:\n"
					<< "1 - Name/Species\n"
					<< "2 - Health-Status\n"
					<< "3 - Species\n"
					<< "Enter choice: "
					<< std::flush;
				char searchChoice{'\0'};
				std::cin >> searchChoice;
				std::cin.ignore();
			*/                
                /*Filter plant on basis of selected properties*/
			/*
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
				std::cout << "Changes have been automatically saved to the database.\n";
				std::cout << "Thanks for using PlantCareApp." << std::endl;
				plants.closeDatabase();
				return 0;
			}

			default: {
				std::cerr << "Invalid Choice!\n";
				break;
			}
		}
	}
	*/
	return app.exec();
}
