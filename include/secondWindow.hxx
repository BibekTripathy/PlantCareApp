#ifndef SECONDWINDOW_HXX
#define SECONDWINDOW_HXX

#include <QDialog>

namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr);
    ~secondwindow();

private:
    std::string filePath;
    Ui::secondwindow *ui;

private slots:
    void on_selectDB_clicked();
};

#endif // SECONDWINDOW_H
