#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QGridLayout>
#include "plant.hxx"
#include "cardtemplate.hxx"
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
    void loadCardsDynamically(int columns);
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void handleCardDeletion(cardtemplate* card);
    void on_actionNew_Plant_triggered();


    void on_actionExit_triggered();

    void on_actionUnhealthy_triggered();

    void on_actionHealthy_triggered();

    void on_actionFilter_by_Species_triggered();

    void on_actionReset_Filters_triggered();

public slots:

private:
    Ui::MainWindow *ui;
	Plants plants;
    bool firstShow = true;
    QGridLayout* gridLayout = nullptr;
};

#endif // !MAINWINDOW_HXX
