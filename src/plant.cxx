#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "plant.hxx"

void Plants::fetchData(const std::string &filePath) {
    std::cout << "Fetching data from File: " << filePath << "\n";

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening the file!\n";
        std::exit(1); // Exits program if wrong filepath
    }

    std::string line{""};
    std::getline(file, line);
    while (std::getline(file, line)) {
        plantData row;
        std::stringstream ss(line);
        std::getline(ss, row.name, ',');
        std::getline(ss, row.species, ',');
        std::getline(ss, row.description, ',');
        std::getline(ss, row.healthStatus, ',');
        database.push_back(row);
    }

	file.close();

	std::cout << "Data has been fetched successfully!\n";
	Plants::showDetails();
}

void Plants::showDetails() {
    for (const plantData &plantData : database) {
        std::cout << "Name: " << plantData.name << "\n"
                  << "Species: " << plantData.species << "\n"
                  << "Description: " << plantData.description << "\n"
                  << "Health Status: " << plantData.healthStatus << "\n"
                  << "----------------------------------\n";
    }
}

void Plants::addPlant() {
    plantData newPlant;

	std::cout << "Please enter the following details for the new plant:" << std::endl;
    std::cout << "Name: " << std::flush;
    std::getline(std::cin, newPlant.name);
    std::cout << "Species: " << std::flush;
    std::getline(std::cin, newPlant.species);
    std::cout << "Description: " << std::flush;
    std::getline(std::cin, newPlant.description);
    std::cout << "Health Status: " << std::flush;
    std::getline(std::cin, newPlant.healthStatus);

    database.push_back(newPlant);

    std::cout << "Added plant: " << newPlant.name << std::endl;
    std::cout << "----------------------------------\n";
}

void Plants::editPlant() {
    int plantId{0};
    std::cout << "Enter plant ID to edit: ";
    std::cin >> plantId;

    if (plantId > database.size() || plantId < 1) {
        std::cerr << "Error: Plant with ID `" << plantId << "` not found.\n";
        return;
    }

    while (true) {
        std::cout
			<< "\n--- Editing Plant ID: " << plantId << " ---"
			<< "\n1. Name: " << database[plantId - 1].name
			<< "\n2. Species: " << database[plantId - 1].species
			<< "\n3. Description: " << database[plantId - 1].description
			<< "\n4. Health Status: " << database[plantId - 1].healthStatus
			<< "\n5. Exit\n"
			<< "Choose property to edit (1-5): "
			<< std::flush;

        char choice{'\0'};
        std::cin >> choice;
        std::cin.ignore();

        if (choice == '5') {
            std::cout << "Exiting edit mode.\n";
            std::cout << "----------------------------------\n";
            break;
        }

        if (choice < '1' || choice > '4') {
            std::cerr << "Invalid choice. Try again.\n";
            continue;
        }

        std::string newValue{""};
        switch (choice) {
			case '1': {
				std::cout << "New Name: " ;
				break;
			}
			case '2': {
				std::cout << "New Species: ";
				break;
			}
			case '3': {
				std::cout << "New Description: " ;
				break;
			}
			case '4': {
				std::cout << "New HealthStatus: " ;
				break;
			}
			default: {
				break;
			}
        }
        std::getline(std::cin, newValue);
    }
}

void Plants::removePlant(int plantId) {
    if (plantId > database.size()) {
        std::cerr << "Error: Plant with ID `" << plantId << "` not found.\n";
        return;
    }

    std::cout << "Removing plant ID " << plantId << std::endl;
    database.erase(database.begin() + (plantId - 1));
    std::cout << "Plant removed successfully.\n";
}

void Plants::writeData(const std::string &filePath) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening the file. Changes could not be saved.\n";
		return;
    }

	file << "name,species,description,healthStatus\n";

    for (const auto &plantData : database) {
        file
			<< plantData.name << ","
			<< plantData.species << ","
			<< plantData.description << ","
			<< plantData.healthStatus << "\n";
    }

    file.close();
}

void Plants::searchPlants(const std::string& query) {
    std::vector<plantData> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (const auto& plant : database) {
        std::string lowerName = plant.name;
        std::string lowerSpecies = plant.species;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        std::transform(lowerSpecies.begin(), lowerSpecies.end(), lowerSpecies.begin(), ::tolower);

        if (lowerName.find(lowerQuery) != std::string::npos ||
            lowerSpecies.find(lowerQuery) != std::string::npos) {
            results.push_back(plant);
        }
    }

    if (results.empty()) {
        std::cerr << "Error: No plants found matching: `" << query << "`\n";
    } else {
        showFiltered(results);
    }
}

void Plants::filterByHealth(const std::string& healthStatus) {
    std::vector<plantData> results;
    std::string lowerStatus = healthStatus;
    for (const auto& plant : database) {
        std::string lowerPlantStatus = plant.healthStatus;
        if (lowerPlantStatus == lowerStatus) {
            results.push_back(plant);
        }
    }

    if (results.empty()) {
        std::cerr << "Error: No plants found with matching Health-Status: `" << healthStatus << "`\n";
    } else {
        showFiltered(results);
    }
}

void Plants::filterBySpecies(const std::string& species) {
    std::vector<plantData> results;
    std::string lowerSpeciesQuery = species;
    std::transform(lowerSpeciesQuery.begin(), lowerSpeciesQuery.end(), lowerSpeciesQuery.begin(), ::tolower);

    for (const auto& plant : database) {
        std::string lowerPlantSpecies = plant.species;
        std::transform(lowerPlantSpecies.begin(), lowerPlantSpecies.end(), lowerPlantSpecies.begin(), ::tolower);

        if (lowerPlantSpecies.find(lowerSpeciesQuery) != std::string::npos) {
            results.push_back(plant);
        }
    }

    if (results.empty()) {
        std::cerr << "Error: No plants found with matching Species: `" << species << "`\n";
    } else {
        showFiltered(results);
    }
}

void Plants::showFiltered(const std::vector<plantData>& filteredPlants) {
    std::cout << "\n=== Filtered Results (" << filteredPlants.size() << " plants) ===\n";
    for (const auto& plant : filteredPlants) {
        std::cout
			<< "\nName: " << plant.name
			<< "\nSpecies: " << plant.species
			<< "\nDescription: " << plant.description
			<< "\nHealth: " << plant.healthStatus
			<< "\n-----------------------------\n";
    }
}
