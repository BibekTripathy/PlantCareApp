#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
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
	std::string getAddress();


protected:
    void loadCardsDynamically();
    void showEvent(QShowEvent *event) override;

private slots:

private:
    Ui::MainWindow *ui;
	std::string filePath;
    bool firstShow = true;
};

#endif // !MAINWINDOW_HXX
