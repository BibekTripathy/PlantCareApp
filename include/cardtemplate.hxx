#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

#include "plant.hxx"
#include <QString>
#include <QWidget>

namespace Ui {
class cardtemplate;
}

class cardtemplate : public QWidget
{
    Q_OBJECT

public:
    explicit cardtemplate(QWidget *parent = nullptr);
    cardtemplate(QWidget* parent = nullptr, Plants* plantManager = nullptr);
    ~cardtemplate();
    void setPlantData(const Plants::plantData& data);
    int getPlantId();

private slots:
    void on_EditBtn_clicked();

    void on_DeleteBtn_clicked();

private:
    Ui::cardtemplate *ui;
    int plantId;
    Plants* plantManager = nullptr;
    QString species;

signals:
    void requestDeletion(cardtemplate* card);

};

#endif // CARDTEMPLATE_H
