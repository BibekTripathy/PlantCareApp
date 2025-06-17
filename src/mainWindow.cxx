#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include "mainWindow.hxx"
#include "./ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

std::string MainWindow::getAddress() {
	return MainWindow::filePath;
}

void MainWindow::on_selectDbBtn_clicked() {
	qDebug() << "selectDbBtn Clicked";
	QString qFilePath = QFileDialog::getOpenFileName(
		this, "Select SQLite Database", "",
		"SQLite Database (*.db *.sqlite *.sqlite3);;All Files (*)");
	if (qFilePath.isEmpty()) {
		// User cancelled
		return;
	}
	filePath = qFilePath.toStdString();
}
