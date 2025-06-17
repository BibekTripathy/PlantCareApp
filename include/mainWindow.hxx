#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>

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

private slots:
	void on_selectDbBtn_clicked();

private:
    Ui::MainWindow *ui;
	std::string filePath;
};

#endif // !MAINWINDOW_HXX
