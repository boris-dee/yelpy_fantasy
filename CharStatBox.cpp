#include "CharStatBox.h"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>

CharStatBox::CharStatBox(QString charType, bool dialog, QWidget *parent) : QWidget(parent)
{
    QGroupBox *statBox = new QGroupBox;
    m_statBundle = new QMap<QString, QLineEdit*>;

    QLabel *charLabel = new QLabel(tr("Character"));

    QLabel *nameLabel = new QLabel(tr("Name"));
    m_nameEdit = new QLineEdit;
    m_statBundle->insert("Name", m_nameEdit);
    m_nameComboBox = new QComboBox;
    m_nameComboBox->setMaximumHeight(20);

    QLabel *levelLabel = new QLabel(tr("Level"));
    m_levelEdit = new QLineEdit;
    m_statBundle->insert("Level", m_levelEdit);
    QProgressBar *expBar = new QProgressBar;
    expBar->setMaximumHeight(20);
    expBar->setMaximumWidth(100);

    QLabel *hpLabel = new QLabel(tr("HP"));
    m_hpEdit = new QLineEdit;
    m_statBundle->insert("HP", m_hpEdit);

    m_hpMaxEdit = new QLineEdit;
    m_statBundle->insert("HPMax", m_hpMaxEdit);

    QLabel *mpLabel = new QLabel(tr("MP"));
    m_mpEdit = new QLineEdit;
    m_statBundle->insert("MP", m_mpEdit);

    m_mpMaxEdit = new QLineEdit;
    m_statBundle->insert("MPMax", m_mpMaxEdit);

    QLabel *limitLabel = new QLabel(tr("Limit Break"));
    QProgressBar *limitBar = new QProgressBar;
    limitBar->setMaximumHeight(20);
    limitBar->setMaximumWidth(100);

    QLabel *weaponLabel = new QLabel(tr("Weapon"));
    m_weaponComboBox = new QComboBox;
    m_weaponComboBox->setMaximumHeight(20);

    QLabel *armorLabel = new QLabel(tr("Armor"));
    m_armorComboBox = new QComboBox;
    m_armorComboBox->setMaximumHeight(20);

    QLabel *accessoryLabel = new QLabel(tr("Accessory"));
    m_accessoryComboBox = new QComboBox;
    m_accessoryComboBox->setMaximumHeight(20);

    QLabel *strengthLabel = new QLabel(tr("Strength"));
    m_strengthEdit = new QLineEdit;
    m_statBundle->insert("Strength", m_strengthEdit);

    QLabel *vitalityLabel = new QLabel(tr("Vitality"));
    m_vitalityEdit = new QLineEdit;
    m_statBundle->insert("Vitality", m_vitalityEdit);

    QLabel *magicLabel = new QLabel(tr("Magic"));
    m_magicEdit = new QLineEdit;
    m_statBundle->insert("Magic", m_magicEdit);

    QLabel *spiritLabel = new QLabel(tr("Spirit"));
    m_spiritEdit = new QLineEdit;
    m_statBundle->insert("Spirit", m_spiritEdit);

    QLabel *dextLabel = new QLabel(tr("Dexterity"));
    m_dextEdit = new QLineEdit;
    m_statBundle->insert("Dexterity", m_dextEdit);

    QLabel *chanceLabel = new QLabel(tr("Chance"));
    m_chanceEdit = new QLineEdit;
    m_statBundle->insert("Chance", m_chanceEdit);

    QLabel *attackLabel = new QLabel(tr("Attack"));
    m_attackEdit = new QLineEdit;
    m_statBundle->insert("Attack", m_attackEdit);

    QLabel *attackPercentLabel = new QLabel(tr("Attack %"));
    m_attackPercentEdit = new QLineEdit;
    m_statBundle->insert("AttackPercent", m_attackPercentEdit);

    QLabel *defenseLabel = new QLabel(tr("Defense"));
    m_defenseEdit = new QLineEdit;
    m_statBundle->insert("Defense", m_defenseEdit);

    QLabel *defensePercentLabel = new QLabel(tr("Defense %"));
    m_defensePercentEdit = new QLineEdit;
    m_statBundle->insert("DefensePercent", m_defensePercentEdit);

    QLabel *magAttackLabel = new QLabel(tr("Magic Attack"));
    m_magAttackEdit = new QLineEdit;
    m_statBundle->insert("MagAttack", m_magAttackEdit);

    QLabel *magAttPercentLabel = new QLabel(tr("Magic Attack %"));
    m_magAttPercentEdit = new QLineEdit;
    m_statBundle->insert("MagAttackPercent", m_magAttPercentEdit);

    QLabel *magDefenseLabel = new QLabel(tr("Magic Defense"));
    m_magDefenseEdit = new QLineEdit;
    m_statBundle->insert("MagDefense", m_magDefenseEdit);

    QLabel *magDefPercentLabel = new QLabel(tr("Magic Defense %"));
    m_magDefPercentEdit = new QLineEdit;
    m_statBundle->insert("MagDefPercent", m_magDefPercentEdit);

    QLabel *precisionLabel = new QLabel(tr("Precision"));
    m_precisionEdit = new QLineEdit;
    m_statBundle->insert("Precision", m_precisionEdit);

    QLabel *critHitPercentLabel = new QLabel(tr("Critical Hit %"));
    m_critHitPercentEdit = new QLineEdit;
    m_statBundle->insert("CritHitPercent", m_critHitPercentEdit);

    // Assemble the grid differently depending on Char/Enemy/Dialog.
    QGridLayout *lowerGrid = new QGridLayout;

    if (!dialog)
    {
        if (charType == "Character")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameComboBox, 0, 1, 1, 2);
            lowerGrid->addWidget(levelLabel, 1, 0);
            lowerGrid->addWidget(m_levelEdit, 1, 1);
            lowerGrid->addWidget(expBar, 1, 2);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpEdit, 2, 1);
            lowerGrid->addWidget(m_hpMaxEdit, 2, 2);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(m_mpMaxEdit, 3, 2);
            lowerGrid->addWidget(limitLabel, 4, 0, 1, 2);
            lowerGrid->addWidget(limitBar, 5, 0, 1, 2);
            lowerGrid->addWidget(weaponLabel, 4, 3);
            lowerGrid->addWidget(m_weaponComboBox, 5, 3, 1, 2);
            lowerGrid->addWidget(armorLabel, 4, 5);
            lowerGrid->addWidget(m_armorComboBox, 5, 5, 1, 2);
            lowerGrid->addWidget(accessoryLabel, 4, 7);
            lowerGrid->addWidget(m_accessoryComboBox, 5, 7, 1, 2);
            lowerGrid->addWidget(strengthLabel, 0, 3);
            lowerGrid->addWidget(m_strengthEdit, 0, 4);
            lowerGrid->addWidget(vitalityLabel, 0, 5);
            lowerGrid->addWidget(m_vitalityEdit, 0, 6);
            lowerGrid->addWidget(magicLabel, 0, 7);
            lowerGrid->addWidget(m_magicEdit, 0, 8);
            lowerGrid->addWidget(spiritLabel, 0, 9);
            lowerGrid->addWidget(m_spiritEdit, 0, 10);
            lowerGrid->addWidget(dextLabel, 1, 3);
            lowerGrid->addWidget(m_dextEdit, 1, 4);
            lowerGrid->addWidget(chanceLabel, 1, 5);
            lowerGrid->addWidget(m_chanceEdit, 1, 6);
            lowerGrid->addWidget(precisionLabel, 1, 7);
            lowerGrid->addWidget(m_precisionEdit, 1, 8);
            lowerGrid->addWidget(critHitPercentLabel, 1, 9);
            lowerGrid->addWidget(m_critHitPercentEdit, 1, 10);
            lowerGrid->addWidget(attackLabel, 2, 3);
            lowerGrid->addWidget(m_attackEdit, 2, 4);
            lowerGrid->addWidget(attackPercentLabel, 2, 5);
            lowerGrid->addWidget(m_attackPercentEdit, 2, 6);
            lowerGrid->addWidget(magAttackLabel, 2, 7);
            lowerGrid->addWidget(m_magAttackEdit, 2, 8);
            lowerGrid->addWidget(magAttPercentLabel, 2, 9);
            lowerGrid->addWidget(m_magAttPercentEdit, 2, 10);
            lowerGrid->addWidget(defenseLabel, 3, 3);
            lowerGrid->addWidget(m_defenseEdit, 3, 4);
            lowerGrid->addWidget(defensePercentLabel, 3, 5);
            lowerGrid->addWidget(m_defensePercentEdit, 3, 6);
            lowerGrid->addWidget(magDefenseLabel, 3, 7);
            lowerGrid->addWidget(m_magDefenseEdit, 3, 8);
            lowerGrid->addWidget(magDefPercentLabel, 3, 9);
            lowerGrid->addWidget(m_magDefPercentEdit, 3, 10);
        }
        else
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameComboBox, 0, 1, 1, 2);
            lowerGrid->addWidget(levelLabel, 1, 0);
            lowerGrid->addWidget(m_levelEdit, 1, 1);
            lowerGrid->addWidget(expBar, 1, 2);
            expBar->setValue(100);
            expBar->setTextVisible(false);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpEdit, 2, 1);
            lowerGrid->addWidget(m_hpMaxEdit, 2, 2);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(m_mpMaxEdit, 3, 2);
            lowerGrid->addWidget(dextLabel, 1, 3);
            lowerGrid->addWidget(m_dextEdit, 1, 4);
            lowerGrid->addWidget(chanceLabel, 1, 5);
            lowerGrid->addWidget(m_chanceEdit, 1, 6);
            lowerGrid->addWidget(attackLabel, 2, 3);
            lowerGrid->addWidget(m_attackEdit, 2, 4);
            lowerGrid->addWidget(attackPercentLabel, 2, 5);
            lowerGrid->addWidget(m_attackPercentEdit, 2, 6);
            lowerGrid->addWidget(magAttackLabel, 2, 7);
            lowerGrid->addWidget(m_magAttackEdit, 2, 8);
            lowerGrid->addWidget(magAttPercentLabel, 2, 9);
            lowerGrid->addWidget(m_magAttPercentEdit, 2, 10);
            lowerGrid->addWidget(defenseLabel, 3, 3);
            lowerGrid->addWidget(m_defenseEdit, 3, 4);
            lowerGrid->addWidget(defensePercentLabel, 3, 5);
            lowerGrid->addWidget(m_defensePercentEdit, 3, 6);
            lowerGrid->addWidget(magDefenseLabel, 3, 7);
            lowerGrid->addWidget(m_magDefenseEdit, 3, 8);
            lowerGrid->addWidget(magDefPercentLabel, 3, 9);
            lowerGrid->addWidget(m_magDefPercentEdit, 3, 10);
        }

    }
    else
    {
        if (charType == "Character")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(levelLabel, 1, 0);
            lowerGrid->addWidget(m_levelEdit, 1, 1);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpEdit, 2, 1);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(strengthLabel, 4, 0);
            lowerGrid->addWidget(m_strengthEdit, 4, 1);
            lowerGrid->addWidget(vitalityLabel, 5, 0);
            lowerGrid->addWidget(m_vitalityEdit, 5, 1);
            lowerGrid->addWidget(magicLabel, 6, 0);
            lowerGrid->addWidget(m_magicEdit, 6, 1);
            lowerGrid->addWidget(spiritLabel, 7, 0);
            lowerGrid->addWidget(m_spiritEdit, 7, 1);
            lowerGrid->addWidget(dextLabel, 8, 0);
            lowerGrid->addWidget(m_dextEdit, 8, 1);
            lowerGrid->addWidget(chanceLabel, 9, 0);
            lowerGrid->addWidget(m_chanceEdit, 9, 1);
        }
        else if (charType == "Weapon")
        {
            lowerGrid->addWidget(charLabel, 0, 0);
            lowerGrid->addWidget(m_nameComboBox, 0, 1);
            lowerGrid->addWidget(nameLabel, 1, 0);
            lowerGrid->addWidget(m_nameEdit, 1, 1);
            lowerGrid->addWidget(attackLabel, 2, 0);
            lowerGrid->addWidget(m_attackEdit, 2, 1);
            lowerGrid->addWidget(attackPercentLabel, 3, 0);
            lowerGrid->addWidget(m_attackPercentEdit, 3, 1);
            lowerGrid->addWidget(magicLabel, 4, 0);
            lowerGrid->addWidget(m_magicEdit, 4, 1);
            lowerGrid->addWidget(critHitPercentLabel, 5, 0);
            lowerGrid->addWidget(m_critHitPercentEdit, 5, 1);
        }
        else if (charType == "Armor")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(defenseLabel, 1, 0);
            lowerGrid->addWidget(m_defenseEdit, 1, 1);
            lowerGrid->addWidget(defensePercentLabel, 2, 0);
            lowerGrid->addWidget(m_defensePercentEdit, 2, 1);
            lowerGrid->addWidget(magDefenseLabel, 3, 0);
            lowerGrid->addWidget(m_magDefenseEdit, 3, 1);
            lowerGrid->addWidget(magDefPercentLabel, 4, 0);
            lowerGrid->addWidget(m_magDefPercentEdit, 4, 1);
            lowerGrid->addWidget(magicLabel, 5, 0);
            lowerGrid->addWidget(m_magicEdit, 5, 1);
            lowerGrid->addWidget(strengthLabel, 6, 0);
            lowerGrid->addWidget(m_strengthEdit, 6, 1);
        }
        else if (charType == "Accessory")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(hpLabel, 1, 0);
            lowerGrid->addWidget(m_hpEdit, 1, 1);
            lowerGrid->addWidget(mpLabel, 2, 0);
            lowerGrid->addWidget(m_mpEdit, 2, 1);
            lowerGrid->addWidget(strengthLabel, 3, 0);
            lowerGrid->addWidget(m_strengthEdit, 3, 1);
            lowerGrid->addWidget(vitalityLabel, 4, 0);
            lowerGrid->addWidget(m_vitalityEdit, 4, 1);
            lowerGrid->addWidget(magicLabel, 5, 0);
            lowerGrid->addWidget(m_magicEdit, 5, 1);
            lowerGrid->addWidget(spiritLabel, 6, 0);
            lowerGrid->addWidget(m_spiritEdit, 6, 1);
            lowerGrid->addWidget(dextLabel, 7, 0);
            lowerGrid->addWidget(m_dextEdit, 7, 1);
            lowerGrid->addWidget(chanceLabel, 8, 0);
            lowerGrid->addWidget(m_chanceEdit, 8, 1);
        }
        else
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(levelLabel, 1, 0);
            lowerGrid->addWidget(m_levelEdit, 1, 1);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpEdit, 2, 1);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(dextLabel, 4, 0);
            lowerGrid->addWidget(m_dextEdit, 4, 1);
            lowerGrid->addWidget(chanceLabel, 5, 0);
            lowerGrid->addWidget(m_chanceEdit, 5, 1);
            lowerGrid->addWidget(attackLabel, 6, 0);
            lowerGrid->addWidget(m_attackEdit, 6, 1);
            lowerGrid->addWidget(attackPercentLabel, 7, 0);
            lowerGrid->addWidget(m_attackPercentEdit, 7, 1);
            lowerGrid->addWidget(magAttackLabel, 8, 0);
            lowerGrid->addWidget(m_magAttackEdit, 8, 1);
            lowerGrid->addWidget(magAttPercentLabel, 9, 0);
            lowerGrid->addWidget(m_magAttPercentEdit, 9, 1);
            lowerGrid->addWidget(defenseLabel, 10, 0);
            lowerGrid->addWidget(m_defenseEdit, 10, 1);
            lowerGrid->addWidget(defensePercentLabel, 11, 0);
            lowerGrid->addWidget(m_defensePercentEdit, 11, 1);
            lowerGrid->addWidget(magDefenseLabel, 12, 0);
            lowerGrid->addWidget(m_magDefenseEdit, 12, 1);
            lowerGrid->addWidget(magDefPercentLabel, 13, 0);
            lowerGrid->addWidget(m_magDefPercentEdit, 13, 1);
        }
    }

    statBox->setLayout(lowerGrid);

    // Create and assemble the upper (widget) grid
    QHBoxLayout *upperGrid = new QHBoxLayout(this);
    upperGrid->setMargin(0);
    upperGrid->addWidget(statBox);
}

QMap<QString, QLineEdit*>* CharStatBox::getStats() const {return m_statBundle;}

QComboBox* CharStatBox::getNameComboBox() const {return m_nameComboBox;}

QComboBox* CharStatBox::getWeaponComboBox() const {return m_weaponComboBox;}

QComboBox* CharStatBox::getArmorComboBox() const {return m_armorComboBox;}

QComboBox* CharStatBox::getAccessoryComboBox() const {return m_accessoryComboBox;}
