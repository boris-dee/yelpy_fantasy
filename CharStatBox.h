#ifndef CHARSTATBOX_H
#define CHARSTATBOX_H

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QWidget>

class CharStatBox : public QWidget
{
    Q_OBJECT
public:
    explicit CharStatBox(QString charType, bool dialog, QWidget *parent = nullptr);

    QMap<QString, QLineEdit*>* getStats() const;

private:
    QMap<QString, QLineEdit*> *m_statBundle;
    QLineEdit *m_nameEdit, *m_levelEdit, *m_hpEdit, *m_mpEdit;
    QComboBox *m_nameComboBox;
};

#endif // CHARSTATBOX_H
