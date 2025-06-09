#include <iostream>
#include <vector>
#include <ctime>
#include "plant.hxx"

int main (int argc, char **argv) {
	std::cout << "Welcome to PlantCareApp.\n";
	Plants plants;
	std::string filePath{""};
	std::cout << "Enter address of database (/path/to/database.db): " << std::flush;
	// getline(cin, filePath);
	filePath = "testData/database.csv"; // temporary testing data
	plants.fetchData(filePath);
	while (true) {
		std::cout
			<< "Enter choice\n"
			<< "1 - Show Plant Details\n"
			<< "2 - Add New Plant\n"
			<< "3 - Edit Plant\n"
			<< "4 - Remove Plant\n"
			<< "5 - Save & Exit\n"
			<< "6 - Exit w/o Saving\n"
			<< std::flush;
		char choice{'\0'};
		std::cin >> choice;
		std::cin.ignore();
		std::cout << "\n";
		switch(choice) {
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
				std::cout<<"Enter th
				e plant ID: "<<std::flush;
				std::cin>>plantId
				plants.removePlant(plantId);
				break;
			}
			case '5': {
				plants.writeData(filePath);
				std::cout << "Changes have been Saved.\nThanks for using PlantCareApp." << std::endl;
				return 0;
			}
			case '6': {
				std::cout << "Exiting w/o Saving.\nThanks for using PlantCareApp." << std::endl;
				return 0;
			}
			default: {
				std::cerr << "Invalid Choice!\n";
				break;
			}
		}
	}
	return 0;
}
