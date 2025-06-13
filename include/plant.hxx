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

  sqlite3 *db;       
  std::string dbPath; // Store database path

  // Private helper methods for SQLite
  void openDatabase();
  void closeDatabase();
  void createTable();
  void executeSQL(const std::string &sql);

public:
  void fetchData(const std::string &filePath);
  void showDetails();
  void addPlant();
  void editPlant();
  void removePlant(int plantId);
  void writeData(const std::string &filePath);
  void searchPlants(const std::string &query);
  void filterByHealth(const std::string &healthStatus);
  void filterBySpecies(const std::string &species);
  void showFiltered(const std::vector<plantData> &filteredPlants);
};

#endif // !PLANT_HXX
