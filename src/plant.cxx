#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "plant.hxx"
void Plants::fetchData(const std::string &filePath)
{
    /* code */
}

void Plants::showDetails() {
    /* code */
}
int nextId = 1;
void Plants::addPlant(std::string name, std::string species, std::string description, std::string healthStatus)
{
    plantData newPlant;
    newPlant.id = nextId++;
    newPlant.name = name;
    newPlant.species = species;
    newPlant.description = description;
    newPlant.healthStatus = healthStatus;

    database.push_back(newPlant);
    std::cout << "Added plant: " << name << " (ID: " << newPlant.id << ")\n";
}

void Plants::editPlant()
{
    int plantId;
    std::cout << "Enter plant ID to edit: ";
    std::cin >> plantId;

    auto it = std::find_if(database.begin(), database.end(), [plantId](const plantData &p)
                           { return p.id == plantId; });
    if (it == database.end())
    {
        std::cout << "Error: Plant with ID " << plantId << " not found.\n";
        return;
    }

    while (true)
    {
        std::cout << "\n--- Editing Plant ID " << plantId << " ---\n"
                  << "1. Name: " << it->name << "\n"
                  << "2. Species: " << it->species << "\n"
                  << "3. Description: " << it->description << "\n"
                  << "4. Health Status: " << it->healthStatus << "\n"
                  << "5. Exit\n"
                  << "Choose property to edit (1-5): ";

        char choice{'\0'};
        std::cin >> choice;
        std::cin.ignore();
        if (choice == '5')
        {
            std::cout << "Exiting edit mode.\n";
            break;
        }

        if (choice < '1' || choice > '4')
        {
            std::cerr << "Invalid choice. Try again.\n";
            continue;
        }
        std::string newValue;
        std::cout << "Enter new value: ";
        std::getline(std::cin, newValue);

        editPlant();
    }
}
void Plants::removePlant(int plantId)
{
    auto it = std::find_if(database.begin(), database.end(), [plantId](const plantData &p)
                           { return p.id == plantId; });
    if (it == database.end())
    {
        std::cerr << "Error: Plant with ID " << plantId << " not found.\n";
        return;
    }

    std::cout << "Removing plant ID " << plantId << " (" << it->name << ")\n";
    database.erase(it);
    std::cout << "Plant removed successfully.\n";
}

void writeData(const std::string &filePath)
{
    /* code */
}
