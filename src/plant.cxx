#include <algorithm>
#include <iostream>
#include <ostream>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <QDebug>
#include <QString>
#include "plant.hxx"

void Plants::setFilePath(const std::string &filePath){
    Plants::dbPath=filePath;
    qDebug()<<"File Path has been set.";
    qDebug()<<dbPath;
}

std::vector<Plants::plantData> Plants::getAllPlants() {
    std::vector<Plants::plantData> result;

    const char* sql = "SELECT id, name, species, description, healthStatus FROM plants;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        qDebug() << "Failed to prepare statement:" << sqlite3_errmsg(db);
        return result;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        plantData data;
        data.id = sqlite3_column_int(stmt, 0);
        data.name = QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        data.species = QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        data.description = QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        data.healthStatus = QString::fromUtf8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        result.push_back(data);
    }

    sqlite3_finalize(stmt);
    return result;
}

bool Plants::updatePlantData(const Plants::plantData& data) {
    const char* sql = "UPDATE plants SET name = ?, species = ?, description = ?, healthStatus = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        qDebug() << "Failed to prepare update:" << sqlite3_errmsg(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, data.name.toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, data.species.toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, data.description.toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, data.healthStatus.toUtf8().constData(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, data.id);

    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool Plants::deletePlantById(int id) {
    if (!db) return false;

    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM plants WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}



void Plants::closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

void Plants::fetchData(const std::string& filePath) {
    std::cout << "Fetching data from File." << std::endl;
    if (sqlite3_open(filePath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
    /*Creates a table if it doesn't exist*/
    const char* sql =
        "CREATE TABLE IF NOT EXISTS plants ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "species TEXT NOT NULL,"
        "description TEXT,"
        "healthStatus TEXT);";
    /*Error Handling*/
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Checkfor data in the database
    // const char *sql = "SELECT COUNT(*) FROM plants;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    /*Counts total number of plants in database*/
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        std::cout << "Found " << count << " plants in database." << std::endl;
    }

    sqlite3_finalize(stmt);
    showDetails();
}

void Plants::showDetails() {
    const char* sql = "SELECT id, name, species, description, healthStatus FROM plants;";
    sqlite3_stmt* stmt;
    /*Error Handling*/
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "\n=== Plant Database ===\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout
            << "ID: " << sqlite3_column_int(stmt, 0)
            << "\nName: " << sqlite3_column_text(stmt, 1)
            << "\nSpecies: " << sqlite3_column_text(stmt, 2)
            << "\nDescription: " << sqlite3_column_text(stmt, 3)
            << "\nHealth Status: " << sqlite3_column_text(stmt, 4)
            << "\n----------------------------------\n";
    }

    sqlite3_finalize(stmt);
}
/*
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
    //Inserting Plants
    const char* sql =
        "INSERT INTO plants (name, species, description, healthStatus) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    //Error Handling
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    //Appending plants into database
    sqlite3_bind_text(stmt, 1, newPlant.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, newPlant.species.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, newPlant.description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, newPlant.healthStatus.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error inserting plant: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Added plant: " << newPlant.name << " (ID: " << sqlite3_last_insert_rowid(db) << ")" << std::endl;
    }

    sqlite3_finalize(stmt);

    std::cout << "Added plant: " << newPlant.name << std::endl;
    std::cout << "----------------------------------\n";
}

void Plants::editPlant() {
    int plantId{ 0 };
    std::cout << "Enter plant ID to edit: ";
    std::cin >> plantId;
    std::cin.ignore();

    const char* checkSql = "SELECT COUNT(*) FROM plants WHERE id = ?;";
    sqlite3_stmt* checkStmt;
    //Error Handling
    if (sqlite3_prepare_v2(db, checkSql, -1, &checkStmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(checkStmt, 1, plantId);

    //Error Handling
    if (sqlite3_step(checkStmt) != SQLITE_ROW ||
        sqlite3_column_int(checkStmt, 0) == 0) {
        std::cerr << "Error:Plant with ID: " << plantId << " not found." << std::endl;
        sqlite3_finalize(checkStmt);
        return;
    }

    while (true) {
        const char* getSql = "SELECT name, species,description, healthstatus FROM plants WHERE id = ?;";
        sqlite3_stmt* getStmt;

        if (sqlite3_prepare_v2(db, getSql, -1, &getStmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        sqlite3_bind_int(getStmt, 1, plantId);
        sqlite3_step(getStmt);

        std::cout
            << "\n--- Editing Plant ID: " << plantId << " ---"
            << "\n1. Name: " << sqlite3_column_text(getStmt, 0)
            << "\n2. Species: " << sqlite3_column_text(getStmt, 1)
            << "\n3. Description: " << sqlite3_column_text(getStmt, 2)
            << "\n4. Health Status: " << sqlite3_column_text(getStmt, 3)
            << "\n5. Exit\n"
            << "Choose property to edit (1-5): "
            << std::flush;

        sqlite3_finalize(getStmt);
        char choice{ '\0' };
        std::cin >> choice;
        std::cin.ignore();

        if (choice == '5') {
            std::cout << "Exiting edit mode." << std::endl;
            break;
        }
        if (choice < '1' || choice > '4') {
            std::cerr << "Invalid choice. Try again.\n";
            continue;
        }
        std::string newValue{ "" };
        std::string columnName;
        //Option to edit plant properties
        switch (choice) {
        case '1': {
            std::cout << "New Name: ";
            columnName = "name";
            break;
        }
        case '2': {
            std::cout << "New Species: ";
            columnName = "species";
            break;
        }
        case '3': {
            std::cout << "New Description: ";
            columnName = "description";
            break;
        }
        case '4': {
            std::cout << "New HealthStatus: ";
            columnName = "healthStatus";
            break;
        }
        }
        std::getline(std::cin, newValue);
        //Update SQL
        std::string updateSql = "UPDATE plants SET " + columnName + " = ? WHERE id =?;";
        sqlite3_stmt* updateStmt;
        if (sqlite3_prepare_v2(db, updateSql.c_str(), -1, &updateStmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            continue;
        }

        sqlite3_bind_text(updateStmt, 1, newValue.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(updateStmt, 2, plantId);

        //Error Handling
        if (sqlite3_step(updateStmt) != SQLITE_DONE) {
            std::cerr << "Error updating plant: " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cout << "Plant updated successfully.\n";
        }

        sqlite3_finalize(updateStmt);
    }
}

void Plants::removePlant(int plantId) {
    const char* checkSql = "SELECT COUNT(*) FROM plants WHERE id = ?;";
    sqlite3_stmt* checkStmt;

    //Error Handling
    if (sqlite3_prepare_v2(db, checkSql, -1, &checkStmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(checkStmt, 1, plantId);

    if (sqlite3_step(checkStmt) != SQLITE_ROW || sqlite3_column_int(checkStmt, 0) == 0) {
        std::cerr << "Error: Plant with ID `" << plantId << "` not found.\n";
        sqlite3_finalize(checkStmt);
        return;
    }
    sqlite3_finalize(checkStmt);

    // Delete the plant
    const char* deleteSql = "DELETE FROM plants WHERE id = ?;";
    sqlite3_stmt* deleteStmt;

    if (sqlite3_prepare_v2(db, deleteSql, -1, &deleteStmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(deleteStmt, 1, plantId);

    //Error Handling while deleting plants
    if (sqlite3_step(deleteStmt) != SQLITE_DONE) {
        std::cerr << "Error deleting plant: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Plant ID " << plantId << " removed successfully.\n";
    }

    sqlite3_finalize(deleteStmt);
}

void Plants::searchPlants(const std::string& query) {
    std::vector<plantData> results;
    const char* sql = "SELECT id, name, species, description, healthStatus FROM plants WHERE LOWER(name) LIKE ? OR LOWER(species) LIKE ?;";
    sqlite3_stmt* stmt;

    //Error Handling
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string likeQuery = "%" + query + "%";
    std::transform(likeQuery.begin(), likeQuery.end(), likeQuery.begin(), ::tolower);

    sqlite3_bind_text(stmt, 1, likeQuery.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, likeQuery.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        plantData plant;
        plant.id = sqlite3_column_int(stmt, 0);
        plant.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        plant.species = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        plant.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        plant.healthStatus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        results.push_back(plant);
    }

    sqlite3_finalize(stmt);

    if (results.empty()) {
        std::cerr << "Error: No plants found matching: `" << query << "`\n";
    } else {
        showFiltered(results);
    }
}

void Plants::filterByHealth(const std::string& healthStatus) {
    std::vector<plantData> results;
    const char* sql = "SELECT id, name, species, description, healthStatus FROM plants WHERE healthStatus = ?;";
    sqlite3_stmt* stmt;

    //Error Handling
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, healthStatus.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        plantData plant;
        plant.id = sqlite3_column_int(stmt, 0);
        plant.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        plant.species = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        plant.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        plant.healthStatus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        results.push_back(plant);
    }

    sqlite3_finalize(stmt);

    if (results.empty()) {
        std::cerr << "Error: No plants found with matching Health-Status: `" << healthStatus << "`\n";
    } else {
        showFiltered(results);
    }
}

void Plants::filterBySpecies(const std::string& species) {
    std::vector<plantData> results;
    const char* sql = "SELECT id, name, species, description, healthStatus FROM plants WHERE LOWER(species) LIKE ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string likeQuery = "%" + species + "%";
    std::transform(likeQuery.begin(), likeQuery.end(), likeQuery.begin(), ::tolower);

    sqlite3_bind_text(stmt, 1, likeQuery.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        plantData plant;
        plant.id = sqlite3_column_int(stmt, 0);
        plant.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        plant.species = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        plant.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        plant.healthStatus = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        results.push_back(plant);
    }

    sqlite3_finalize(stmt);

    if (results.empty()) {
        std::cerr << "Error: No plants found with matching Species: `" << species << "`\n";
    }
    else {
        showFiltered(results);
    }
}

void Plants::showFiltered(const std::vector<plantData>& filteredPlants) {
    std::cout << "\n=== Filtered Results (" << filteredPlants.size() << " plants) ===\n";
    for (const auto& plant : filteredPlants) {
        std::cout
            << "\nID: " << plant.id
            << "\nName: " << plant.name
            << "\nSpecies: " << plant.species
            << "\nDescription: " << plant.description
            << "\nHealth: " << plant.healthStatus
            << "\n-----------------------------\n";
    }
}*/
