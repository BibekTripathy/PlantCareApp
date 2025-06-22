#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

#include "plant.hxx"
#include <QWidget>

namespace Ui {
class cardtemplate;
}

class cardtemplate : public QWidget
{
    Q_OBJECT

public:
    explicit cardtemplate(QWidget *parent = nullptr);
    ~cardtemplate();
    void setPlantData(const Plants::plantData& data);

private slots:
    void on_EditBtn_clicked();

private:
    Ui::cardtemplate *ui;
};

#endif // CARDTEMPLATE_H
