#ifndef ADDCHARDIALOG_H
#define ADDCHARDIALOG_H

#include "StatBox.h"

#include <QDialog>
#include <QString>
#include <QWidget>

class AddCharDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCharDialog(QString charType, QWidget *parent = nullptr);

    StatBox* getStatBox() const;

private:
    QDialog *m_dialogBox;
    StatBox *m_charStatBox;
};

#endif // ADDCHARDIALOG_H
