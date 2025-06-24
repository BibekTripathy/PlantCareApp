#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QSettings>
#include <QFileInfo>
#include "plant.hxx"
#include "secondWindow.hxx"
#include "ui_secondWindow.h"

secondwindow::secondwindow(QWidget *parent) : QDialog(parent), ui(new Ui::secondwindow) {
    ui->setupUi(this);
    ui->FP_Label->show();
    ui->FP_Box->show();
    this->resize(500, 220);
}

secondwindow::~secondwindow() {
    delete ui;
}

void secondwindow::on_BrowseBtn_clicked() {
    qDebug() << "selectDb Clicked";
    QString qFilePath = QFileDialog::getOpenFileName(
        this, "Select SQLite Database", "",
        "SQLite Database (*.db *.sqlite *.sqlite3);;All Files (*)"
	);

    if (qFilePath.isEmpty()) {
        return;
    }

    ui->FP_Box->setText(qFilePath);
}

void secondwindow::on_SubBtn_clicked() {
    QString pathText = ui->FP_Box->text();  // ✅ QLineEdit uses .text()

    if (pathText.isEmpty()) {
        QMessageBox::warning(this, "No File", "Please select a database file.");
        return;
    }
	filePath = pathText;
    accept();
}

QString secondwindow::getFilePath() const {
    return filePath;
}

void secondwindow::on_CreateDBbutton_clicked()
{
    QString newDbPath = QFileDialog::getSaveFileName(
        this,
        "Create New Plant Database",
        QDir::homePath() + "/plants.db",
        "SQLite Database (*.db *.sqlite *.sqlite3);;All Files (*)"
        );

    if (newDbPath.isEmpty()) return;

    // Create and open the database
    sqlite3* newDb;
    if (sqlite3_open(newDbPath.toStdString().c_str(), &newDb) != SQLITE_OK) {
        QMessageBox::critical(this, "Error", "Failed to create database.");
        return;
    }

    // SQL schema and inserts
    const char* schema = R"sql(
        BEGIN TRANSACTION;
        CREATE TABLE plants (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            species TEXT NOT NULL,
            description TEXT,
            healthstatus TEXT NOT NULL CHECK (healthstatus IN ('healthy', 'unhealthy'))
        );

        INSERT INTO plants (name, species, description, healthstatus) VALUES
        ('Snake Plant', 'Dracaena trifasciata', 'A hardy evergreen perennial with stiff, upright, sword-like leaves with green and yellow variegation. Excellent air purifier.',
        CASE WHEN abs(random() % 2) = 0 THEN 'healthy' ELSE 'unhealthy' END);
        COMMIT;
    )sql";

    char* errMsg = nullptr;
    if (sqlite3_exec(newDb, schema, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        QMessageBox::critical(this, "Error", QString("Failed to initialize database:\n%1").arg(errMsg));
        sqlite3_free(errMsg);
        sqlite3_close(newDb);
        return;
    }

    sqlite3_close(newDb);

    // ✅ Set created file path in FP_Box and store it internally
    ui->FP_Box->setText(newDbPath);
    filePath = newDbPath;
    QMessageBox::information(this, "Success", "Database created successfully!");
}

