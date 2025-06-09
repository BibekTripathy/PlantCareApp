#ifndef PLANT_HXX
#define PLANT_HXX

#include <string>
#include <vector>
#include <ctime> /* Migrate to <chrono> later */

class Plants {
private:
	struct plantData {
    int id;
    std::string name;
    std::string species;
    std::string description;
    std::string healthStatus;
};

	std::vector<plantData> database;
public:
	void fetchData(const std::string& filePath) {}
	void showDetails();
	void addPlant(std::string name, std::string species, std::string description, std::string healthStatus) {}
	void editPlant() {}
	void removePlant(int plantId) {}
	void writeData(const std::string& filePath) {}
};

#endif // !PLANT_HXX
