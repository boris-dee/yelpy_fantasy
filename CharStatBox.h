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
    QComboBox* getNameComboBox() const;
    QComboBox* getArmorComboBox() const;
    QComboBox* getWeaponComboBox() const;
    QComboBox* getAccessoryComboBox() const;

private:
    QMap<QString, QLineEdit*> *m_statBundle;
    QLineEdit *m_nameEdit, *m_levelEdit, *m_hpEdit, *m_hpMaxEdit, *m_mpEdit, *m_mpMaxEdit;
    QLineEdit *m_strengthEdit, *m_vitalityEdit, *m_magicEdit, *m_spiritEdit, *m_dextEdit, *m_chanceEdit;
    QLineEdit *m_attackEdit, *m_attackPercentEdit, *m_defenseEdit, *m_defensePercentEdit;
    QLineEdit *m_magAttackEdit, *m_magAttPercentEdit, *m_magDefenseEdit, *m_magDefPercentEdit;
    QLineEdit *m_precisionEdit, *m_critHitPercentEdit;
    QComboBox *m_nameComboBox, *m_weaponComboBox, *m_armorComboBox, *m_accessoryComboBox;
};

#endif // CHARSTATBOX_H
