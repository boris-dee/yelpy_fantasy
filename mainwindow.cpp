#include "mainwindow.h"
#include "addcharacter.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Display all characters stat boxes
    for (int ichar(1); ichar < 5; ++ichar)
    {
        ui->characterLayout->addWidget(createCharStatBox(ichar), ichar, 0);
    }

    // Display Enemy stat box
    ui->enemyLayout->addWidget(createEnemyStatBox(), 0, 0);

    // Set all QLineEdits to readonly
    QList<QLineEdit*> allQLineEdit = findChildren<QLineEdit*>();
    for (int i(0); i < allQLineEdit.size(); ++i)
    {
        allQLineEdit.at(i)->setReadOnly(true);
    }
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
    charBoxLayout->addWidget(weaponComboBox, 4, 2, 1, 2);
    charBoxLayout->addWidget(armorLabel, 5, 1);
    charBoxLayout->addWidget(armorComboBox, 5, 2, 1, 2);
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
    charBoxLayout->addWidget(attackPercentLabel, 1, 8);
    charBoxLayout->addWidget(attackPercentEdit, 1, 9);
    charBoxLayout->addWidget(magAttackLabel, 2, 6);
    charBoxLayout->addWidget(magAttackEdit, 2, 7);
    charBoxLayout->addWidget(defenseLabel, 3, 6);
    charBoxLayout->addWidget(defenseEdit, 3, 7);
    charBoxLayout->addWidget(defensePercentLabel, 3, 8);
    charBoxLayout->addWidget(defensePercentEdit, 3, 9);
    charBoxLayout->addWidget(magDefenseLabel, 4, 6);
    charBoxLayout->addWidget(magDefenseEdit, 4, 7);
    charBoxLayout->addWidget(magDefPercentLabel, 4, 8);
    charBoxLayout->addWidget(magDefPercentEdit, 4, 9);
    charBoxLayout->addWidget(precisionLabel, 5, 6);
    charBoxLayout->addWidget(precisionEdit, 5, 7);
    charBoxLayout->addWidget(critHitPercentLabel, 5, 8);
    charBoxLayout->addWidget(critHitPercentEdit, 5, 9);

    charStatBox->setLayout(charBoxLayout);

    return charStatBox;
}

QGroupBox *MainWindow::createEnemyStatBox()
{
    QGroupBox *enemyStatBox = new QGroupBox;

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

    QListView *enemyList = new QListView;

    // Assemble the grid
    QGridLayout *enemyBoxLayout = new QGridLayout;
    enemyBoxLayout->addWidget(levelLabel, 0, 0);
    enemyBoxLayout->addWidget(levelEdit, 0, 1);
    enemyBoxLayout->addWidget(hpLabel, 1, 0);
    enemyBoxLayout->addWidget(hpEdit, 1, 1);
    enemyBoxLayout->addWidget(mpLabel, 2, 0);
    enemyBoxLayout->addWidget(mpEdit, 2, 1);
    enemyBoxLayout->addWidget(dextLabel, 0, 2);
    enemyBoxLayout->addWidget(dextEdit, 0, 3);
    enemyBoxLayout->addWidget(chanceLabel, 0, 4);
    enemyBoxLayout->addWidget(chanceEdit, 0, 5);
    enemyBoxLayout->addWidget(attackLabel, 1, 2);
    enemyBoxLayout->addWidget(attackEdit, 1, 3);
    enemyBoxLayout->addWidget(attackPercentLabel, 1, 4);
    enemyBoxLayout->addWidget(attackPercentEdit, 1, 5);
    enemyBoxLayout->addWidget(magAttackLabel, 2, 2);
    enemyBoxLayout->addWidget(magAttackEdit, 2, 3);
    enemyBoxLayout->addWidget(magAttPercentLabel, 2, 4);
    enemyBoxLayout->addWidget(magAttPercentEdit, 2, 5);
    enemyBoxLayout->addWidget(defenseLabel, 3, 2);
    enemyBoxLayout->addWidget(defenseEdit, 3, 3);
    enemyBoxLayout->addWidget(defensePercentLabel, 3, 4);
    enemyBoxLayout->addWidget(defensePercentEdit, 3, 5);
    enemyBoxLayout->addWidget(magDefenseLabel, 4, 2);
    enemyBoxLayout->addWidget(magDefenseEdit, 4, 3);
    enemyBoxLayout->addWidget(enemyList, 0, 6, 5, 1);
    enemyStatBox->setLayout(enemyBoxLayout);

    return enemyStatBox;
}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_addCharButton_clicked()
{
    AddCharacter *addCharWindow = new AddCharacter("Character", this);
    addCharWindow->exec();
}

void MainWindow::on_addEnemyButton_clicked()
{
    AddCharacter *addCharWindow = new AddCharacter("Enemy", this);
    addCharWindow->exec();
}
