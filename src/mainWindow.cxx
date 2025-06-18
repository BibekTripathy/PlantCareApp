#include <iostream>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include "mainWindow.hxx"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event){
	QMainWindow::showEvent(event);

    if (firstShow) {
        firstShow = false;
        secondwindow *dialog = new secondwindow(this);
        dialog->setModal(true);  
		dialog->exec();
    }
}

std::string MainWindow::getAddress() {
	return MainWindow::filePath;
}
