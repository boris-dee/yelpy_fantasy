#ifndef CHARSTATBOX_H
#define CHARSTATBOX_H

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVector>
#include <QWidget>

class CharStatBox : public QWidget
{
    Q_OBJECT
public:
    explicit CharStatBox(QString charType, bool dialog, QWidget *parent = nullptr);

    QVector<QLineEdit*> getStats() const;
    QPushButton* getRemoveButton() const;
    void setStats(QVector<QString> statBundle);


private:
    QVector<QLineEdit*> *m_statBundle;
    QLineEdit *m_nameEdit, *m_levelEdit, *m_hpEdit, *m_mpEdit;
    QComboBox *m_charComboBox;
};

#endif // CHARSTATBOX_H
