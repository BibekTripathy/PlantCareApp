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
	QString getFilePath() const;

private:
    QString filePath;
    Ui::secondwindow *ui;

private slots:
    void on_BrowseBtn_clicked();
    void on_SubBtn_clicked();
};

#endif // !SECONDWINDOW_HXX
