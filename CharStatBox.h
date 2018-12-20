#ifndef CHARSTATBOX_H
#define CHARSTATBOX_H

#include <QLineEdit>
#include <QWidget>

class CharStatBox : public QWidget
{
    Q_OBJECT
public:
    explicit CharStatBox(bool dialog, QWidget *parent = nullptr);

private:
    QLineEdit *nameEdit, *levelEdit, *hpEdit, *mpEdit;

friend class AddCharDialog;
};

#endif // CHARSTATBOX_H
