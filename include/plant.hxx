#ifndef PLANT_HXX
#define PLANT_HXX

#include <ctime> /* Migrate to <chrono> later */
#include <string>
#include <vector>

class Plants {
private:
	struct plantData {
		int id;
		std::string name, species, description, healthStatus;
	};

	std::vector<plantData> database;
public:
	void fetchData(const std::string& filePath);
	void showDetails();
	void addPlant();
	void editPlant();
	void removePlant(int plantId);
	void writeData(const std::string& filePath);
	void searchPlants(const std::string& query);
    void filterByHealth(const std::string& healthStatus);
    void filterBySpecies(const std::string& species);
    void showFiltered(const std::vector<plantData>& filteredPlants);
};

#endif // !PLANT_HXX
