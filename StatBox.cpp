#include "StatBox.h"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QProgressBar>

StatBox::StatBox(QString charType, bool dialog, QWidget *parent) : QWidget(parent)
{
    QGroupBox *statBox = new QGroupBox;
    m_statBundle = new QMap<QString, QLineEdit*>;

    QLabel *charLabel = new QLabel(tr("Character"));

    QLabel *nameLabel = new QLabel(tr("Name"));
    m_nameEdit = new QLineEdit;
    m_statBundle->insert("Name", m_nameEdit);
    m_nameComboBox = new QComboBox();
    m_nameComboBox->setMaximumHeight(20);

    QLabel *levelLabel = new QLabel(tr("Level"));
    m_levelEdit = new QLineEdit;
    m_statBundle->insert("Level", m_levelEdit);

    m_expBar = new QProgressBar;
    m_expBar->setMaximumHeight(20);
    m_expBar->setMaximumWidth(100);
    m_expBar->setTextVisible(false);

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
    m_limitBar = new QProgressBar;
    m_limitBar->setMaximumHeight(20);
    m_limitBar->setTextVisible(false);

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

    QLabel *luckLabel = new QLabel(tr("Luck"));
    m_luckEdit = new QLineEdit;
    m_statBundle->insert("Luck", m_luckEdit);

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

    QLabel *magAttackLabel = new QLabel(tr("Mag. Attack"));
    m_magAttackEdit = new QLineEdit;
    m_statBundle->insert("MagAttack", m_magAttackEdit);

    QLabel *magAttPercentLabel = new QLabel(tr("Mag. Attack %"));
    m_magAttPercentEdit = new QLineEdit;
    m_statBundle->insert("MagAttackPercent", m_magAttPercentEdit);

    QLabel *magDefenseLabel = new QLabel(tr("Mag. Defense"));
    m_magDefenseEdit = new QLineEdit;
    m_statBundle->insert("MagDefense", m_magDefenseEdit);

    QLabel *magDefPercentLabel = new QLabel(tr("Mag. Defense %"));
    m_magDefPercentEdit = new QLineEdit;
    m_statBundle->insert("MagDefPercent", m_magDefPercentEdit);

    QLabel *precisionLabel = new QLabel(tr("Precision"));
    m_precisionEdit = new QLineEdit;
    m_statBundle->insert("Precision", m_precisionEdit);

    QLabel *critHitPercentLabel = new QLabel(tr("Critical Hit %"));
    m_critHitPercentEdit = new QLineEdit;
    m_statBundle->insert("CritHitPercent", m_critHitPercentEdit);

    // Case of attack, magic, summons.
    QLabel *factorLabel = new QLabel(tr("Factor"));
    m_factorEdit = new QLineEdit;
    m_statBundle->insert("Factor", m_factorEdit);

    QLabel *mpCostLabel = new QLabel(tr("MP Cost"));
    m_mpCostEdit = new QLineEdit;
    m_statBundle->insert("MPCost", m_mpCostEdit);

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
            lowerGrid->addWidget(m_expBar, 1, 2);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpEdit, 2, 1);
            lowerGrid->addWidget(m_hpMaxEdit, 2, 2);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(m_mpMaxEdit, 3, 2);

            lowerGrid->addWidget(limitLabel, 0, 3);
            lowerGrid->addWidget(m_limitBar, 0, 4, 1, 2);
            lowerGrid->addWidget(weaponLabel, 1, 3);
            lowerGrid->addWidget(m_weaponComboBox, 1, 4, 1, 2);
            lowerGrid->addWidget(armorLabel, 2, 3);
            lowerGrid->addWidget(m_armorComboBox, 2, 4, 1, 2);
            lowerGrid->addWidget(accessoryLabel, 3, 3);
            lowerGrid->addWidget(m_accessoryComboBox, 3, 4, 1, 2);

            lowerGrid->addWidget(strengthLabel, 0, 6);
            lowerGrid->addWidget(m_strengthEdit, 0, 7);
            lowerGrid->addWidget(vitalityLabel, 0, 8);
            lowerGrid->addWidget(m_vitalityEdit, 0, 9);
            lowerGrid->addWidget(magicLabel, 0, 10);
            lowerGrid->addWidget(m_magicEdit, 0, 11);
            lowerGrid->addWidget(spiritLabel, 0, 12);
            lowerGrid->addWidget(m_spiritEdit, 0, 13);

            lowerGrid->addWidget(dextLabel, 1, 6);
            lowerGrid->addWidget(m_dextEdit, 1, 7);
            lowerGrid->addWidget(luckLabel, 1, 8);
            lowerGrid->addWidget(m_luckEdit, 1, 9);

            lowerGrid->addWidget(attackLabel, 2, 6);
            lowerGrid->addWidget(m_attackEdit, 2, 7);
            lowerGrid->addWidget(magAttackLabel, 2, 8);
            lowerGrid->addWidget(m_magAttackEdit, 2, 9);
            lowerGrid->addWidget(defenseLabel, 2, 10);
            lowerGrid->addWidget(m_defenseEdit, 2, 11);
            lowerGrid->addWidget(magDefenseLabel, 2, 12);
            lowerGrid->addWidget(m_magDefenseEdit, 2, 13);

            lowerGrid->addWidget(attackPercentLabel, 3, 6);
            lowerGrid->addWidget(m_attackPercentEdit, 3, 7);
            lowerGrid->addWidget(magAttPercentLabel, 3, 8);
            lowerGrid->addWidget(m_magAttPercentEdit, 3, 9);
            lowerGrid->addWidget(defensePercentLabel, 3, 10);
            lowerGrid->addWidget(m_defensePercentEdit, 3, 11);
            lowerGrid->addWidget(magDefPercentLabel, 3, 12);
            lowerGrid->addWidget(m_magDefPercentEdit, 3, 13);
        }
        else
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameComboBox, 0, 1, 1, 2);
            lowerGrid->addWidget(levelLabel, 1, 0);
            lowerGrid->addWidget(m_levelEdit, 1, 1);
            lowerGrid->addWidget(m_expBar, 1, 2);
            m_expBar->setValue(100);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpEdit, 2, 1);
            lowerGrid->addWidget(m_hpMaxEdit, 2, 2);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpEdit, 3, 1);
            lowerGrid->addWidget(m_mpMaxEdit, 3, 2);

            lowerGrid->addWidget(attackLabel, 0, 6);
            lowerGrid->addWidget(m_attackEdit, 0, 7);
            lowerGrid->addWidget(magAttackLabel, 0, 8);
            lowerGrid->addWidget(m_magAttackEdit, 0, 9);
            lowerGrid->addWidget(defenseLabel, 0, 10);
            lowerGrid->addWidget(m_defenseEdit, 0, 11);
            lowerGrid->addWidget(magDefenseLabel, 0, 12);
            lowerGrid->addWidget(m_magDefenseEdit, 0, 13);

            lowerGrid->addWidget(attackPercentLabel, 1, 6);
            lowerGrid->addWidget(m_attackPercentEdit, 1, 7);
            lowerGrid->addWidget(magAttPercentLabel, 1, 8);
            lowerGrid->addWidget(m_magAttPercentEdit, 1, 9);
            lowerGrid->addWidget(defensePercentLabel, 1, 10);
            lowerGrid->addWidget(m_defensePercentEdit, 1, 11);
            lowerGrid->addWidget(magDefPercentLabel, 1, 12);
            lowerGrid->addWidget(m_magDefPercentEdit, 1, 13);

            lowerGrid->addWidget(dextLabel, 2, 6);
            lowerGrid->addWidget(m_dextEdit, 2, 7);
            lowerGrid->addWidget(luckLabel, 2, 8);
            lowerGrid->addWidget(m_luckEdit, 2, 9);
        }

        // Formal all line edits
        QMap<QString, QLineEdit*>::const_iterator it = m_statBundle->constBegin();
        while (it != m_statBundle->constEnd())
        {
            it.value()->setReadOnly(true);
            it.value()->setMaximumHeight(20);
            it.value()->setMaximumWidth(40);
            it++;
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
            lowerGrid->addWidget(m_hpMaxEdit, 2, 1);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpMaxEdit, 3, 1);
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
            lowerGrid->addWidget(luckLabel, 9, 0);
            lowerGrid->addWidget(m_luckEdit, 9, 1);
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
            lowerGrid->addWidget(m_hpMaxEdit, 1, 1);
            lowerGrid->addWidget(mpLabel, 2, 0);
            lowerGrid->addWidget(m_mpMaxEdit, 2, 1);
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
            lowerGrid->addWidget(luckLabel, 8, 0);
            lowerGrid->addWidget(m_luckEdit, 8, 1);
        }
        else if (charType == "Attack")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(factorLabel, 1, 0);
            lowerGrid->addWidget(m_factorEdit, 1, 1);
        }
        else if (charType == "Magic" || charType == "Summon")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(factorLabel, 1, 0);
            lowerGrid->addWidget(m_factorEdit, 1, 1);
            lowerGrid->addWidget(magAttPercentLabel, 2, 0);
            lowerGrid->addWidget(m_magAttPercentEdit, 2, 1);
            lowerGrid->addWidget(mpCostLabel, 3, 0);
            lowerGrid->addWidget(m_mpCostEdit, 3, 1);

        }
        else if (charType == "Item")
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
        }
        else
        {
            lowerGrid->addWidget(nameLabel, 0, 0);
            lowerGrid->addWidget(m_nameEdit, 0, 1);
            lowerGrid->addWidget(levelLabel, 1, 0);
            lowerGrid->addWidget(m_levelEdit, 1, 1);
            lowerGrid->addWidget(hpLabel, 2, 0);
            lowerGrid->addWidget(m_hpMaxEdit, 2, 1);
            lowerGrid->addWidget(mpLabel, 3, 0);
            lowerGrid->addWidget(m_mpMaxEdit, 3, 1);
            lowerGrid->addWidget(dextLabel, 4, 0);
            lowerGrid->addWidget(m_dextEdit, 4, 1);
            lowerGrid->addWidget(luckLabel, 5, 0);
            lowerGrid->addWidget(m_luckEdit, 5, 1);
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

QMap<QString, QLineEdit*>* StatBox::getStats() const {return m_statBundle;}

QComboBox* StatBox::getNameComboBox() const {return m_nameComboBox;}

QComboBox* StatBox::getWeaponComboBox() const {return m_weaponComboBox;}

QComboBox* StatBox::getArmorComboBox() const {return m_armorComboBox;}

QComboBox* StatBox::getAccessoryComboBox() const {return m_accessoryComboBox;}

QProgressBar* StatBox::getLimitBar() const {return m_limitBar;}

QProgressBar* StatBox::getExpBar() const {return m_expBar;}
