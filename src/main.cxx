#include <iostream>
#include <QApplication>
#include <QFileDialog>
#include <QString>
#include <QStyleHints>
#include <sqlite3.h>
#include <string>
#include "plant.hxx"
#include "mainWindow.hxx"
#include "secondWindow.hxx"
#include "stylemanager.hxx"

#define APP_VERSION "2.0.0"

int main(int argc, char *argv[]) {

	if (argc > 1 && std::string(argv[1]) == std::string("--version")) {
		std::cout
			<< "QtPlantly " << APP_VERSION << "\n"
			<< "License GPLv3: GNU GPL Version 3 or <https://raw.githubusercontent.com/BibekTripathy/QtPlantly/refs/heads/main/LICENSE>\n"
			<< "This is free software: you are free to change and redistribute it.\n"
			<< "This software does not come with any Warranty.\n"
			<< "\n"
			<< "Contributors:\n"
			<< "Ajitesh Borah <https://github.com/felixity1917/>\n"
			<< "Bibek Tripathy <https://github.com/BibekTripathy/>\n"
			<< "Sarvansh Mishra <https://github.com/Astral-Error/>\n"
			<< std::endl;
		exit(0);
	}

	QApplication app(argc, argv);
    bool isDark = app.styleHints()->colorScheme() == Qt::ColorScheme::Dark;

    StyleManager::applyStyle(isDark ? StyleManager::Dark : StyleManager::Light);
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
}
