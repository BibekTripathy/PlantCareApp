#ifndef EDITWINDOW_HXX
#define EDITWINDOW_HXX

#include <QDialog>

namespace Ui {
class editwindow;
}

class editwindow : public QDialog
{
    Q_OBJECT

public:
    explicit editwindow(QWidget *parent = nullptr);
    ~editwindow();

private:
    Ui::editwindow *ui;
};

#endif // EDITWINDOW_HXX
