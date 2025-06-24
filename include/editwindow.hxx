#ifndef EDITWINDOW_HXX
#define EDITWINDOW_HXX

#include <QDialog>
#include "plant.hxx"
namespace Ui {
class editwindow;
}

class editwindow : public QDialog
{
    Q_OBJECT

public:
    explicit editwindow(QWidget *parent = nullptr);
    explicit editwindow(const Plants::plantData& data, QWidget* parent = nullptr);
    ~editwindow();
    Plants::plantData getUpdatedData() const;

private slots:
    void on_cancelBtn_clicked();

    void on_SaveBtn_clicked();

private:
    Ui::editwindow *ui;
    Plants::plantData plantData;
};

#endif // EDITWINDOW_HXX
