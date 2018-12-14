#ifndef ADDCHARACTER_H
#define ADDCHARACTER_H

#include <QDialog>
#include <QGroupBox>

namespace Ui {
class AddCharacter;
}

class AddCharacter : public QDialog
{
    Q_OBJECT

public:
    explicit AddCharacter(QString charType, QWidget *parent = 0);
    ~AddCharacter();

private:
    Ui::AddCharacter *ui;
};

#endif // ADDCHARACTER_H
