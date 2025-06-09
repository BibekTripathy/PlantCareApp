#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "plant.hxx"
void Plants::fetchData(const std::string &filePath) {
    std::ifstream file(filePath);
    
}

void Plants::showDetails() {
    /* code */
}
//int nextId = 1;
void Plants::addPlant()
{
    plantData newPlant;
    std::getline(std::cin,newPlant.name);
    std::getline(std::cin,newPlant.species);
    std::getline(std::cin,newPlant.description);
    std::getline(std::cin,newPlant.healthStatus);
   // newPlant.id = nextId++;

    database.push_back(newPlant);
    std::cout << "Added plant: " << newPlant.name <<std::endl;
}

void Plants::editPlant()
{
    int plantId;
    std::cout << "Enter plant ID to edit: ";
    std::cin >> plantId;

    // auto it = std::find_if(database.begin(), database.end(), [plantId](const plantData &p)
    //                        { return p.id == plantId; });
    if (plantId > database.size()|| plantId<1)
    {
        std::cout << "Error: Plant with ID " << plantId << " not found.\n";
        return;
    }

    while (true)
    {
        std::cout << "\n--- Editing Plant ID " << plantId << " ---\n"
                  << "1. Name: " << database[plantId-1].name << "\n"
                  << "2. Species: " << database[plantId-1].species << "\n"
                  << "3. Description: " << database[plantId-1].description << "\n"
                  << "4. Health Status: " << database[plantId-1].healthStatus << "\n"
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

        
    }
}
void Plants::removePlant(int plantId)
{
    // auto it = std::find_if(database.begin(), database.end(), [plantId](const plantData &p)
    //                        { return p.id == plantId; });
    if (plantId > database.size())
    {
        std::cerr << "Error: Plant with ID " << plantId << " not found.\n";
        return;
    }

    std::cout << "Removing plant ID " << plantId  << std::endl;
    database.erase(database.begin()+(plantId-1));
    std::cout << "Plant removed successfully.\n";
}

void Plants::writeData(const std::string &filePath) {
    std::ofstream file(filePath);
    for (const auto& plantData : database){
        file<<plantData.id<<","<<plantData.name<<","<<plantData.species<<","<<plantData.description<<","<<plantData.healthStatus;
    }
    file.close();
}
