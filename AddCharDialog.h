#ifndef ADDCHARDIALOG_H
#define ADDCHARDIALOG_H

#include "CharStatBox.h"

#include <QDialog>
#include <QString>
#include <QWidget>

class AddCharDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCharDialog(QString charType, QWidget *parent = nullptr);

    CharStatBox* getCharStatBox() const;

private:
    QDialog *m_dialogBox;
    CharStatBox *m_charStatBox;
};

#endif // ADDCHARDIALOG_H
