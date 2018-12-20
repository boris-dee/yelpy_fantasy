#include "EnemyStatBox.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>

EnemyStatBox::EnemyStatBox(QWidget *parent) : QWidget(parent)
{
    QGroupBox *statBox = new QGroupBox;

    QLabel *nameLabel = new QLabel(tr("Name"));
    QLineEdit *nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText(tr("Enemy's Name"));

    QLabel *levelLabel = new QLabel(tr("Level"));
    QLineEdit *levelEdit = new QLineEdit;
    levelEdit->setPlaceholderText(tr("Level"));

    QLabel *hpLabel = new QLabel(tr("HP"));
    QLineEdit *hpEdit = new QLineEdit;
    hpEdit->setPlaceholderText(tr("HP"));

    QLabel *mpLabel = new QLabel(tr("MP"));
    QLineEdit *mpEdit = new QLineEdit;
    mpEdit->setPlaceholderText(tr("MP"));

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

    QLabel *magAttPercentLabel = new QLabel(tr("Magic Attack %"));
    QLineEdit *magAttPercentEdit = new QLineEdit;
    magAttPercentEdit->setPlaceholderText(tr("Magic Attack %"));

    QLabel *magDefenseLabel = new QLabel(tr("Magic Defense"));
    QLineEdit *magDefenseEdit = new QLineEdit;
    magDefenseEdit->setPlaceholderText(tr("Magic Defense"));

    // Create and assemble the lower level (group box) grid
    QGridLayout *lowerGrid = new QGridLayout;
    lowerGrid->addWidget(nameLabel, 0, 0);
    lowerGrid->addWidget(nameEdit, 0, 1, 1, 2);
    lowerGrid->addWidget(levelLabel, 1,  0);
    lowerGrid->addWidget(levelEdit, 1, 1);
    lowerGrid->addWidget(hpLabel, 2, 0);
    lowerGrid->addWidget(hpEdit, 2, 1);
    lowerGrid->addWidget(mpLabel, 3, 0);
    lowerGrid->addWidget(mpEdit, 3, 1);
    lowerGrid->addWidget(dextLabel, 1, 2);
    lowerGrid->addWidget(dextEdit, 1, 3);
    lowerGrid->addWidget(chanceLabel, 1, 4);
    lowerGrid->addWidget(chanceEdit, 1, 5);
    lowerGrid->addWidget(attackLabel, 2, 2);
    lowerGrid->addWidget(attackEdit, 2, 3);
    lowerGrid->addWidget(attackPercentLabel, 2, 4);
    lowerGrid->addWidget(attackPercentEdit, 2, 5);
    lowerGrid->addWidget(magAttackLabel, 3, 2);
    lowerGrid->addWidget(magAttackEdit, 3, 3);
    lowerGrid->addWidget(magAttPercentLabel, 3, 4);
    lowerGrid->addWidget(magAttPercentEdit, 3, 5);
    lowerGrid->addWidget(defenseLabel, 4, 2);
    lowerGrid->addWidget(defenseEdit, 4, 3);
    lowerGrid->addWidget(defensePercentLabel, 4, 4);
    lowerGrid->addWidget(defensePercentEdit, 4, 5);
    lowerGrid->addWidget(magDefenseLabel, 5, 2);
    lowerGrid->addWidget(magDefenseEdit, 5, 3);
    statBox->setLayout(lowerGrid);

    // Create and assemble the upper (widget) grid
    QHBoxLayout *upperGrid = new QHBoxLayout(this);
    upperGrid->addWidget(statBox);
}
