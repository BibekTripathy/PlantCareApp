#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include "plant.hxx"
#include "secondWindow.hxx"
#include "ui_secondWindow.h"

secondwindow::secondwindow(QWidget *parent) : QDialog(parent), ui(new Ui::secondwindow) {
    ui->setupUi(this);
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
