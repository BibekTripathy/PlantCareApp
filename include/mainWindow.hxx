#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include "plant.hxx"
#include "secondWindow.hxx"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void loadCardsDynamically();
    void showEvent(QShowEvent *event) override;

private slots:

public slots:

private:
    Ui::MainWindow *ui;
	Plants plants;
    bool firstShow = true;
};

#endif // !MAINWINDOW_HXX
