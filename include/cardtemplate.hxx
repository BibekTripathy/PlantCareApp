#ifndef CARDTEMPLATE_H
#define CARDTEMPLATE_H

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

private:
    Ui::cardtemplate *ui;
};

#endif // CARDTEMPLATE_H
