#include <iostream>
#include <vector>
#include <ctime>
#include "plant.hxx"

int main(int argc, char **argv)
{
	std::cout << "Welcome to PlantCareApp.\n";
	Plants plants;
	std::string filePath{""};
	std::cout << "Enter address of database (/path/to/database.db): " << std::flush;
	getline(std::cin, filePath);
	// filePath = "testData/database.csv"; // temporary testing data
	plants.fetchData(filePath);
	while (true)
	{
		std::cout
			<< "1 - Show Plant Details\n"
			<< "2 - Add New Plant\n"
			<< "3 - Edit Plant\n"
			<< "4 - Remove Plant\n"
			<< "5 - Sarch by "
			<< "6 - Save & Exit\n"
			<< "7 - Exit without Saving\n"
			<< "Enter choice: "
			<< std::flush;
		char choice{'\0'};
		std::cin >> choice;
		std::cin.ignore();
		std::cout << "\n";
		switch (choice)
		{
		case '1':
		{
			plants.showDetails();
			break;
		}
		case '2':
		{
			plants.addPlant();
			break;
		}
		case '3':
		{
			plants.editPlant();
			break;
		}
		case '4':
		{
			int plantId;
			std::cout << "Enter the plant ID: " << std::flush;
			std::cin >> plantId;
			plants.removePlant(plantId);
			break;
		}
		case '5':
		{ // Add this as a new option
			std::cout << "\nSearch Options:\n"
					  << "1 - Search by name/species\n"
					  << "2 - Filter by health status\n"
					  << "3 - Filter by species\n"
					  << "Enter choice: ";
			char searchChoice;
			std::cin >> searchChoice;
			std::cin.ignore();

			switch (searchChoice)
			{
			case '1':
			{
				std::string query;
				std::cout << "Enter search query: ";
				std::getline(std::cin, query);
				plants.searchPlants(query);
				break;
			}
			case '2':
			{
				std::string healthStatus;
				std::cout << "Enter health status to filter (e.g., 'healthy', 'needs care'): ";
				std::getline(std::cin, healthStatus);
				plants.filterByHealth(healthStatus);
				break;
			}
			case '3':
			{
				std::string species;
				std::cout << "Enter species to filter: ";
				std::getline(std::cin, species);
				plants.filterBySpecies(species);
				break;
			}
			default:
				std::cerr << "Invalid search option\n";
			}
			break;
		}
		case '6':
		{
			plants.writeData(filePath);
			std::cout << "Changes have been Saved.\nThanks for using PlantCareApp." << std::endl;
			return 0;
		}
		case '7':
		{
			std::cout << "Exiting without Saving.\nThanks for using PlantCareApp." << std::endl;
			return 0;
		}
		default:
		{
			std::cerr << "Invalid Choice!\n";
			break;
		}
		}
	}
	return 0;
}
