#ifndef PLANT_HXX
#define PLANT_HXX

#include <string>
#include <vector>
#include <ctime> /* Migrate to <chrono> later */

class Plants {
private:
	struct plantData {
		std::string name, species, description, healthStatus;
	};
	std::vector<plantData> database;
public:
	void fetchData(const std::string& filePath) {}
	void showDetails();
	void startAddPlant();
	void addPlant(std::string name, std::string species, std::string description, std::string healthStatus) {}
	void startEditPlant();
	void editPlant(int plantId, int propertyId, std::string newData) {}
	void startRemovePlant();
	void removePlant(int plantId) {}
	void writeData(const std::string& filePath) {}
};

#endif // !PLANT_HXX
