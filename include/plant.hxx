#ifndef PLANT_HXX
#define PLANT_HXX

#include <sqlite3.h>
#include <string>
#include <vector>
class Plants {
private:
	struct plantData {
		int id; // Primary key in db
		std::string name, species, description, healthStatus;
	};

	std::string dbPath;
	sqlite3 *db;


public:
	void fetchData(const std::string &filePath);
	void openDatabase();
	void createTable();
	void executeSQL(const std::string &sql);
	void showDetails();
	void addPlant();
	void editPlant();
	void removePlant(int plantId);
	void writeData(const std::string &filePath);
	void searchPlants(const std::string &query);
	void filterByHealth(const std::string &healthStatus);
	void filterBySpecies(const std::string &species);
	void showFiltered(const std::vector<plantData> &filteredPlants);
	void closeDatabase();
};

#endif // !PLANT_HXX
