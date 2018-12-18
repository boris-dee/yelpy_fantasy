#include "CharStatBox.h"
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

CharStatBox::CharStatBox(QWidget *parent) : QWidget(parent)
{   
    QGroupBox *statBox = new QGroupBox("Character");
    QComboBox *comboBox = new QComboBox;
    QFrame *portrait = new QFrame;

    QLabel *levelLabel = new QLabel(tr("Level"));
    QLineEdit *levelEdit = new QLineEdit;
    levelEdit->setPlaceholderText(tr("Level"));

    QLabel *hpLabel = new QLabel(tr("HP"));
    QLineEdit *hpEdit = new QLineEdit;
    QLineEdit *hpMaxEdit = new QLineEdit;
    hpEdit->setPlaceholderText(tr("HP"));
    hpMaxEdit->setPlaceholderText(tr("HP Max"));

    QLabel *mpLabel = new QLabel(tr("MP"));
    QLineEdit *mpEdit = new QLineEdit;
    QLineEdit *mpMaxEdit = new QLineEdit;
    mpEdit->setPlaceholderText(tr("MP"));
    mpMaxEdit->setPlaceholderText(tr("MP Max"));

    QLabel *weaponLabel = new QLabel(tr("Weapon"));
    QComboBox *weaponComboBox = new QComboBox;

    QLabel *armorLabel = new QLabel(tr("Armor"));
    QComboBox *armorComboBox = new QComboBox;

    QLabel *strengthLabel = new QLabel(tr("Strength"));
    QLineEdit *strengthEdit = new QLineEdit;
    strengthEdit->setPlaceholderText(tr("Strength"));

    QLabel *vitalityLabel = new QLabel(tr("Vitality"));
    QLineEdit *vitalityEdit = new QLineEdit;
    vitalityEdit->setPlaceholderText(tr("Vitality"));

    QLabel *magicLabel = new QLabel(tr("Magic"));
    QLineEdit *magicEdit = new QLineEdit;
    magicEdit->setPlaceholderText(tr("Magic"));

    QLabel *dextLabel = new QLabel(tr("Dexterity"));
    QLineEdit *dextEdit = new QLineEdit;
    dextEdit->setPlaceholderText(tr("Dexterity"));

    QLabel *chanceLabel = new QLabel(tr("Chance"));
    QLineEdit *chanceEdit = new QLineEdit;
    chanceEdit->setPlaceholderText(tr("Chance"));

    QLabel *attackLabel = new QLabel(tr("Attack"));
    QLineEdit *attackEdit = new QLineEdit;
    attackEdit->setPlaceholderText(tr("Attack"));

    QLabel *attackPercentLabel = new QLabel(tr("Attack %"));
    QLineEdit *attackPercentEdit = new QLineEdit;
    attackPercentEdit->setPlaceholderText(tr("Attack %"));

    QLabel *defenseLabel = new QLabel(tr("Defense"));
    QLineEdit *defenseEdit = new QLineEdit;
    defenseEdit->setPlaceholderText(tr("Defense"));

    QLabel *defensePercentLabel = new QLabel(tr("Defense %"));
    QLineEdit *defensePercentEdit = new QLineEdit;
    defensePercentEdit->setPlaceholderText(tr("Defense %"));

    QLabel *magAttackLabel = new QLabel(tr("Magic Attack"));
    QLineEdit *magAttackEdit = new QLineEdit;
    magAttackEdit->setPlaceholderText(tr("Magic Attack"));

    QLabel *magDefenseLabel = new QLabel(tr("Magic Defense"));
    QLineEdit *magDefenseEdit = new QLineEdit;
    magDefenseEdit->setPlaceholderText(tr("Magic Defense"));

    QLabel *magDefPercentLabel = new QLabel(tr("Magic Defense %"));
    QLineEdit *magDefPercentEdit = new QLineEdit;
    magDefPercentEdit->setPlaceholderText(tr("Magic Defense %"));

    QLabel *precisionLabel = new QLabel(tr("Precision"));
    QLineEdit *precisionEdit = new QLineEdit;
    precisionEdit->setPlaceholderText(tr("Precision"));

    QLabel *critHitPercentLabel = new QLabel(tr("Critical Hit %"));
    QLineEdit *critHitPercentEdit = new QLineEdit;
    critHitPercentEdit->setPlaceholderText(tr("Critical Hit %"));

    // Create and assemble the lower level (group box) grid
    QGridLayout *lowerGrid = new QGridLayout;
    lowerGrid->addWidget(comboBox, 0, 0, 1, 3);
    lowerGrid->addWidget(portrait, 1, 0);
    lowerGrid->addWidget(levelLabel, 1, 1);
    lowerGrid->addWidget(levelEdit, 1, 2);
    lowerGrid->addWidget(hpLabel, 2, 1);
    lowerGrid->addWidget(hpEdit, 2, 2);
    lowerGrid->addWidget(hpMaxEdit, 2, 3);
    lowerGrid->addWidget(mpLabel, 3, 1);
    lowerGrid->addWidget(mpEdit, 3, 2);
    lowerGrid->addWidget(mpMaxEdit, 3, 3);
    lowerGrid->addWidget(weaponLabel, 4, 1);
    lowerGrid->addWidget(weaponComboBox, 4, 2, 1, 2);
    lowerGrid->addWidget(armorLabel, 5, 1);
    lowerGrid->addWidget(armorComboBox, 5, 2, 1, 2);
    lowerGrid->addWidget(strengthLabel, 1, 4);
    lowerGrid->addWidget(strengthEdit, 1, 5);
    lowerGrid->addWidget(vitalityLabel, 2, 4);
    lowerGrid->addWidget(vitalityEdit, 2, 5);
    lowerGrid->addWidget(magicLabel, 3, 4);
    lowerGrid->addWidget(magicEdit, 3, 5);
    lowerGrid->addWidget(dextLabel, 4, 4);
    lowerGrid->addWidget(dextEdit, 4, 5);
    lowerGrid->addWidget(chanceLabel, 5, 4);
    lowerGrid->addWidget(chanceEdit, 5, 5);
    lowerGrid->addWidget(attackLabel, 1, 6);
    lowerGrid->addWidget(attackEdit, 1, 7);
    lowerGrid->addWidget(attackPercentLabel, 1, 8);
    lowerGrid->addWidget(attackPercentEdit, 1, 9);
    lowerGrid->addWidget(magAttackLabel, 2, 6);
    lowerGrid->addWidget(magAttackEdit, 2, 7);
    lowerGrid->addWidget(defenseLabel, 3, 6);
    lowerGrid->addWidget(defenseEdit, 3, 7);
    lowerGrid->addWidget(defensePercentLabel, 3, 8);
    lowerGrid->addWidget(defensePercentEdit, 3, 9);
    lowerGrid->addWidget(magDefenseLabel, 4, 6);
    lowerGrid->addWidget(magDefenseEdit, 4, 7);
    lowerGrid->addWidget(magDefPercentLabel, 4, 8);
    lowerGrid->addWidget(magDefPercentEdit, 4, 9);
    lowerGrid->addWidget(precisionLabel, 5, 6);
    lowerGrid->addWidget(precisionEdit, 5, 7);
    lowerGrid->addWidget(critHitPercentLabel, 5, 8);
    lowerGrid->addWidget(critHitPercentEdit, 5, 9);
    statBox->setLayout(lowerGrid);

    // Create and assemble the upper (widget) grid
    QHBoxLayout *upperGrid = new QHBoxLayout(this);
    upperGrid->addWidget(statBox);
}
