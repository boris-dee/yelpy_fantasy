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

    QLineEdit *hpMaxEdit = new QLineEdit;

    QLabel *mpLabel = new QLabel(tr("MP"));
    m_mpEdit = new QLineEdit;
    m_statBundle->insert("MP", m_mpEdit);

    QLineEdit *mpMaxEdit = new QLineEdit;

    QLabel *weaponLabel = new QLabel(tr("Weapon"));
    QComboBox *weaponComboBox = new QComboBox;
    weaponComboBox->setMaximumHeight(20);

    QLabel *armorLabel = new QLabel(tr("Armor"));
    QComboBox *armorComboBox = new QComboBox;
    armorComboBox->setMaximumHeight(20);

    QLabel *strengthLabel = new QLabel(tr("Strength"));
    QLineEdit *strengthEdit = new QLineEdit;

    QLabel *vitalityLabel = new QLabel(tr("Vitality"));
    QLineEdit *vitalityEdit = new QLineEdit;

    QLabel *magicLabel = new QLabel(tr("Magic"));
    QLineEdit *magicEdit = new QLineEdit;

    QLabel *spiritLabel = new QLabel(tr("Spirit"));
    QLineEdit *spiritEdit = new QLineEdit;

    QLabel *dextLabel = new QLabel(tr("Dexterity"));
    QLineEdit *dextEdit = new QLineEdit;

    QLabel *chanceLabel = new QLabel(tr("Chance"));
    QLineEdit *chanceEdit = new QLineEdit;

    QLabel *attackLabel = new QLabel(tr("Attack"));
    QLineEdit *attackEdit = new QLineEdit;

    QLabel *attackPercentLabel = new QLabel(tr("Attack %"));
    QLineEdit *attackPercentEdit = new QLineEdit;

    QLabel *defenseLabel = new QLabel(tr("Defense"));
    QLineEdit *defenseEdit = new QLineEdit;

    QLabel *defensePercentLabel = new QLabel(tr("Defense %"));
    QLineEdit *defensePercentEdit = new QLineEdit;

    QLabel *magAttPercentLabel = new QLabel(tr("Magic Attack %"));
    QLineEdit *magAttPercentEdit = new QLineEdit;

    QLabel *magAttackLabel = new QLabel(tr("Magic Attack"));
    QLineEdit *magAttackEdit = new QLineEdit;

    QLabel *magDefenseLabel = new QLabel(tr("Magic Defense"));
    QLineEdit *magDefenseEdit = new QLineEdit;

    QLabel *magDefPercentLabel = new QLabel(tr("Magic Defense %"));
    QLineEdit *magDefPercentEdit = new QLineEdit;

    QLabel *precisionLabel = new QLabel(tr("Precision"));
    QLineEdit *precisionEdit = new QLineEdit;

    QLabel *critHitPercentLabel = new QLabel(tr("Critical Hit %"));
    QLineEdit *critHitPercentEdit = new QLineEdit;

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
            lowerGrid->addWidget(hpMaxEdit, 2, 2);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(mpMaxEdit, 3, 2);
            lowerGrid->addWidget(weaponLabel, 4, 0);
            lowerGrid->addWidget(weaponComboBox, 4, 1, 1, 2);
            lowerGrid->addWidget(armorLabel, 5, 0);
            lowerGrid->addWidget(armorComboBox, 5, 1, 1, 2);
            lowerGrid->addWidget(strengthLabel, 0, 3);
            lowerGrid->addWidget(strengthEdit, 0, 4);
            lowerGrid->addWidget(vitalityLabel, 0, 5);
            lowerGrid->addWidget(vitalityEdit, 0, 6);
            lowerGrid->addWidget(magicLabel, 0, 7);
            lowerGrid->addWidget(magicEdit, 0, 8);
            lowerGrid->addWidget(spiritLabel, 0, 9);
            lowerGrid->addWidget(spiritEdit, 0, 10);
            lowerGrid->addWidget(dextLabel, 1, 3);
            lowerGrid->addWidget(dextEdit, 1, 4);
            lowerGrid->addWidget(chanceLabel, 1, 5);
            lowerGrid->addWidget(chanceEdit, 1, 6);
            lowerGrid->addWidget(precisionLabel, 1, 7);
            lowerGrid->addWidget(precisionEdit, 1, 8);
            lowerGrid->addWidget(critHitPercentLabel, 1, 9);
            lowerGrid->addWidget(critHitPercentEdit, 1, 10);
            lowerGrid->addWidget(attackLabel, 2, 3);
            lowerGrid->addWidget(attackEdit, 2, 4);
            lowerGrid->addWidget(attackPercentLabel, 2, 5);
            lowerGrid->addWidget(attackPercentEdit, 2, 6);
            lowerGrid->addWidget(magAttackLabel, 2, 7);
            lowerGrid->addWidget(magAttackEdit, 2, 8);
            lowerGrid->addWidget(magAttPercentLabel, 2, 9);
            lowerGrid->addWidget(magAttPercentEdit, 2, 10);
            lowerGrid->addWidget(defenseLabel, 3, 3);
            lowerGrid->addWidget(defenseEdit, 3, 4);
            lowerGrid->addWidget(defensePercentLabel, 3, 5);
            lowerGrid->addWidget(defensePercentEdit, 3, 6);
            lowerGrid->addWidget(magDefenseLabel, 3, 7);
            lowerGrid->addWidget(magDefenseEdit, 3, 8);
            lowerGrid->addWidget(magDefPercentLabel, 3, 9);
            lowerGrid->addWidget(magDefPercentEdit, 3, 10);
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
            lowerGrid->addWidget(hpMaxEdit, 2, 2);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(mpMaxEdit, 3, 2);
            lowerGrid->addWidget(dextLabel, 1, 3);
            lowerGrid->addWidget(dextEdit, 1, 4);
            lowerGrid->addWidget(chanceLabel, 1, 5);
            lowerGrid->addWidget(chanceEdit, 1, 6);
            lowerGrid->addWidget(attackLabel, 2, 3);
            lowerGrid->addWidget(attackEdit, 2, 4);
            lowerGrid->addWidget(attackPercentLabel, 2, 5);
            lowerGrid->addWidget(attackPercentEdit, 2, 6);
            lowerGrid->addWidget(magAttackLabel, 2, 7);
            lowerGrid->addWidget(magAttackEdit, 2, 8);
            lowerGrid->addWidget(magAttPercentLabel, 2, 9);
            lowerGrid->addWidget(magAttPercentEdit, 2, 10);
            lowerGrid->addWidget(defenseLabel, 3, 3);
            lowerGrid->addWidget(defenseEdit, 3, 4);
            lowerGrid->addWidget(defensePercentLabel, 3, 5);
            lowerGrid->addWidget(defensePercentEdit, 3, 6);
            lowerGrid->addWidget(magDefenseLabel, 3, 7);
            lowerGrid->addWidget(magDefenseEdit, 3, 8);
            lowerGrid->addWidget(magDefPercentLabel, 3, 9);
            lowerGrid->addWidget(magDefPercentEdit, 3, 10);
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
            lowerGrid->addWidget(weaponLabel, 4, 0);
            lowerGrid->addWidget(weaponComboBox, 4, 1, 1, 3);
            lowerGrid->addWidget(armorLabel, 5, 0);
            lowerGrid->addWidget(armorComboBox, 5, 1, 1, 3);
            lowerGrid->addWidget(strengthLabel, 1, 3);
            lowerGrid->addWidget(strengthEdit, 1, 4);
            lowerGrid->addWidget(vitalityLabel, 2, 3);
            lowerGrid->addWidget(vitalityEdit, 2, 4);
            lowerGrid->addWidget(magicLabel, 3, 3);
            lowerGrid->addWidget(magicEdit, 3, 4);
            lowerGrid->addWidget(spiritLabel, 1, 5);
            lowerGrid->addWidget(spiritEdit, 1, 6);
            lowerGrid->addWidget(dextLabel, 2, 5);
            lowerGrid->addWidget(dextEdit, 2, 6);
            lowerGrid->addWidget(chanceLabel, 3, 5);
            lowerGrid->addWidget(chanceEdit, 3, 6);
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
            lowerGrid->addWidget(dextEdit, 0, 3);
            lowerGrid->addWidget(chanceLabel, 0, 4);
            lowerGrid->addWidget(chanceEdit, 0, 5);
            lowerGrid->addWidget(attackLabel, 1, 2);
            lowerGrid->addWidget(attackEdit, 1, 3);
            lowerGrid->addWidget(attackPercentLabel, 1, 4);
            lowerGrid->addWidget(attackPercentEdit, 1, 5);
            lowerGrid->addWidget(magAttackLabel, 2, 2);
            lowerGrid->addWidget(magAttackEdit, 2, 3);
            lowerGrid->addWidget(magAttPercentLabel, 2, 4);
            lowerGrid->addWidget(magAttPercentEdit, 2, 5);
            lowerGrid->addWidget(defenseLabel, 3, 2);
            lowerGrid->addWidget(defenseEdit, 3, 3);
            lowerGrid->addWidget(defensePercentLabel, 3, 4);
            lowerGrid->addWidget(defensePercentEdit, 3, 5);
            lowerGrid->addWidget(magDefenseLabel, 4, 2);
            lowerGrid->addWidget(magDefenseEdit, 4, 3);
            lowerGrid->addWidget(magDefPercentLabel, 4, 4);
            lowerGrid->addWidget(magDefPercentEdit, 4, 5);
        }
    }

    statBox->setLayout(lowerGrid);

    // Create and assemble the upper (widget) grid
    QHBoxLayout *upperGrid = new QHBoxLayout(this);
    upperGrid->setMargin(0);
    upperGrid->addWidget(statBox);
}

QMap<QString, QLineEdit*>* CharStatBox::getStats() const {return m_statBundle;}
