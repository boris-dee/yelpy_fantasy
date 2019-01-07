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

    QLabel *weaponLabel = new QLabel(tr("Weapon"));
    QComboBox *weaponComboBox = new QComboBox;
    weaponComboBox->setMaximumHeight(20);

    QLabel *armorLabel = new QLabel(tr("Armor"));
    QComboBox *armorComboBox = new QComboBox;
    armorComboBox->setMaximumHeight(20);

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
    m_statBundle->insert("CriticalHit", m_critHitPercentEdit);

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
            lowerGrid->addWidget(weaponLabel, 4, 0);
            lowerGrid->addWidget(weaponComboBox, 4, 1, 1, 2);
            lowerGrid->addWidget(armorLabel, 5, 0);
            lowerGrid->addWidget(armorComboBox, 5, 1, 1, 2);
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
            lowerGrid->addWidget(strengthLabel, 1, 3);
            lowerGrid->addWidget(m_strengthEdit, 1, 4);
            lowerGrid->addWidget(vitalityLabel, 2, 3);
            lowerGrid->addWidget(m_vitalityEdit, 2, 4);
            lowerGrid->addWidget(magicLabel, 3, 3);
            lowerGrid->addWidget(m_magicEdit, 3, 4);
            lowerGrid->addWidget(spiritLabel, 1, 5);
            lowerGrid->addWidget(m_spiritEdit, 1, 6);
            lowerGrid->addWidget(dextLabel, 2, 5);
            lowerGrid->addWidget(m_dextEdit, 2, 6);
            lowerGrid->addWidget(chanceLabel, 3, 5);
            lowerGrid->addWidget(m_chanceEdit, 3, 6);
        }
        else if (charType == "Weapon")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(magicLabel, 3, 3);
            lowerGrid->addWidget(m_magicEdit, 3, 4);
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
            lowerGrid->addWidget(dextLabel, 0, 2);
            lowerGrid->addWidget(m_dextEdit, 0, 3);
            lowerGrid->addWidget(chanceLabel, 0, 4);
            lowerGrid->addWidget(m_chanceEdit, 0, 5);
            lowerGrid->addWidget(attackLabel, 1, 2);
            lowerGrid->addWidget(m_attackEdit, 1, 3);
            lowerGrid->addWidget(attackPercentLabel, 1, 4);
            lowerGrid->addWidget(m_attackPercentEdit, 1, 5);
            lowerGrid->addWidget(magAttackLabel, 2, 2);
            lowerGrid->addWidget(m_magAttackEdit, 2, 3);
            lowerGrid->addWidget(magAttPercentLabel, 2, 4);
            lowerGrid->addWidget(m_magAttPercentEdit, 2, 5);
            lowerGrid->addWidget(defenseLabel, 3, 2);
            lowerGrid->addWidget(m_defenseEdit, 3, 3);
            lowerGrid->addWidget(defensePercentLabel, 3, 4);
            lowerGrid->addWidget(m_defensePercentEdit, 3, 5);
            lowerGrid->addWidget(magDefenseLabel, 4, 2);
            lowerGrid->addWidget(m_magDefenseEdit, 4, 3);
            lowerGrid->addWidget(magDefPercentLabel, 4, 4);
            lowerGrid->addWidget(m_magDefPercentEdit, 4, 5);
        }
    }

    statBox->setLayout(lowerGrid);

    // Create and assemble the upper (widget) grid
    QHBoxLayout *upperGrid = new QHBoxLayout(this);
    upperGrid->setMargin(0);
    upperGrid->addWidget(statBox);
}

QMap<QString, QLineEdit*>* CharStatBox::getStats() const {return m_statBundle;}

QComboBox* CharStatBox::getComboBox() const {return m_nameComboBox;}
