#include <QDebug>
#include <QFileDialog>
#include <QString>
#include "secondWindow.hxx"
#include "ui_secondWindow.h"

secondwindow::secondwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secondwindow)
{
    ui->setupUi(this);
}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::on_selectDB_clicked() {
	qDebug() << "selectDb Clicked";
	QString qFilePath = QFileDialog::getOpenFileName(
		this, "Select SQLite Database", "",
		"SQLite Database (*.db *.sqlite *.sqlite3);;All Files (*)");
	if (qFilePath.isEmpty()) {
		// User cancelled
		return;
	}
	filePath = qFilePath.toStdString();
}
