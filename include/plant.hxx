#ifndef PLANT_HXX
#define PLANT_HXX

#include <string>
#include<vector>
#include<ctime> /* Migrate to <chrono> later */

class plant {
private:
	struct plantData {
		std::string name, species, description, healthStatus;
	};
	std::vector<plantData> database;
public:
	void fetchData(const std::string& filePath) {}
	void addPlant(std::string name, std::string species, std::string description, std::string healthStatus) {}
	void editPlant(int plantId) {}
	void removePlant(int plantId) {}
	void writeData(const std::string& filePath) {}
};

#endif
