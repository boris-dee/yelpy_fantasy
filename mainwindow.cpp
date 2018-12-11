#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    for (int ichar = 1; ichar < 5; ++ichar)
    {
        mainLayout->addWidget(createCharStatBox(ichar));
    }

    QWidget *screenLayout = new QWidget;
    screenLayout->setLayout(mainLayout);
    setCentralWidget(screenLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGroupBox *MainWindow::createCharStatBox(const int ichar)
{
    // Box Title
    QString boxTitle = "Character ";
    boxTitle.append(QString::number(ichar));

    QGroupBox *charStatBox = new QGroupBox(boxTitle);
    QComboBox *charComboBox = new QComboBox;
    QFrame *charPortrait = new QFrame;

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

    QLabel *attackPercentLabel = new QLabel(tr("% Attack"));
    QLineEdit *attackPercentEdit = new QLineEdit;
    attackPercentEdit->setPlaceholderText(tr("% Attack"));

    QLabel *defenseLabel = new QLabel(tr("Defense"));
    QLineEdit *defenseEdit = new QLineEdit;
    defenseEdit->setPlaceholderText(tr("Defense"));

    QLabel *defensePercentLabel = new QLabel(tr("% Defense"));
    QLineEdit *defensePercentEdit = new QLineEdit;
    defensePercentEdit->setPlaceholderText(tr("% Defense"));

    QLabel *magAttackLabel = new QLabel(tr("Magic Attack"));
    QLineEdit *magAttackEdit = new QLineEdit;
    magAttackEdit->setPlaceholderText(tr("Magic Attack"));

    QLabel *magDefenseLabel = new QLabel(tr("Magic Defense"));
    QLineEdit *magDefenseEdit = new QLineEdit;
    magDefenseEdit->setPlaceholderText(tr("Magic Defense"));

    QLabel *magDefPercentLabel = new QLabel(tr("% Magic Defense"));
    QLineEdit *magDefPercentEdit = new QLineEdit;
    magDefPercentEdit->setPlaceholderText(tr("% Magic Defense"));

    // Assemble the grid
    QGridLayout *charBoxLayout = new QGridLayout;
    charBoxLayout->addWidget(charComboBox, 0, 0, 1, 3);
    charBoxLayout->addWidget(charPortrait, 1, 0);
    charBoxLayout->addWidget(levelLabel, 1, 1);
    charBoxLayout->addWidget(levelEdit, 1, 2);
    charBoxLayout->addWidget(hpLabel, 2, 1);
    charBoxLayout->addWidget(hpEdit, 2, 2);
    charBoxLayout->addWidget(hpMaxEdit, 2, 3);
    charBoxLayout->addWidget(mpLabel, 3, 1);
    charBoxLayout->addWidget(mpEdit, 3, 2);
    charBoxLayout->addWidget(mpMaxEdit, 3, 3);
    charBoxLayout->addWidget(weaponLabel, 4, 1);
    charBoxLayout->addWidget(weaponComboBox, 5, 1, 1, 2);
    charBoxLayout->addWidget(armorLabel, 6, 1);
    charBoxLayout->addWidget(armorComboBox, 7, 1, 1, 2);
    charBoxLayout->addWidget(strengthLabel, 1, 4);
    charBoxLayout->addWidget(strengthEdit, 1, 5);
    charBoxLayout->addWidget(vitalityLabel, 2, 4);
    charBoxLayout->addWidget(vitalityEdit, 2, 5);
    charBoxLayout->addWidget(magicLabel, 3, 4);
    charBoxLayout->addWidget(magicEdit, 3, 5);
    charBoxLayout->addWidget(dextLabel, 4, 4);
    charBoxLayout->addWidget(dextEdit, 4, 5);
    charBoxLayout->addWidget(chanceLabel, 5, 4);
    charBoxLayout->addWidget(chanceEdit, 5, 5);
    charBoxLayout->addWidget(attackLabel, 1, 6);
    charBoxLayout->addWidget(attackEdit, 1, 7);
    charBoxLayout->addWidget(attackPercentLabel, 2, 6);
    charBoxLayout->addWidget(attackPercentEdit, 2, 7);
    charBoxLayout->addWidget(defenseLabel, 3, 6);
    charBoxLayout->addWidget(defenseEdit, 3, 7);
    charBoxLayout->addWidget(defensePercentLabel, 4, 6);
    charBoxLayout->addWidget(defensePercentEdit, 4, 7);
    charBoxLayout->addWidget(magAttackLabel, 5, 6);
    charBoxLayout->addWidget(magAttackEdit, 5, 7);
    charBoxLayout->addWidget(magDefenseLabel, 6, 6);
    charBoxLayout->addWidget(magDefenseEdit, 6, 7);
    charBoxLayout->addWidget(magDefPercentLabel, 7, 6);
    charBoxLayout->addWidget(magDefPercentEdit, 7, 7);
    charStatBox->setLayout(charBoxLayout);

    return charStatBox;
}
