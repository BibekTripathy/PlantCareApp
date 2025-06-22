#ifndef PLANT_HXX
#define PLANT_HXX

#include<QString>
#include <sqlite3.h>
#include <string>
#include <vector>
class Plants {
private:
	struct plantData {
    int id;
    QString name;
    QString species;
    QString description;
    QString healthStatus;
	};


	std::string dbPath;
	sqlite3 *db;


public:
	void setFilePath(const std::string &filePath);
	std::vector<plantData> getAllPlants();
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
	friend class MainWindow;
	friend class cardtemplate;
};

#endif // !PLANT_HXX
