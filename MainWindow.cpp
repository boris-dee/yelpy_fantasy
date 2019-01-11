#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize some useful stuff (models and storage vectors)
    initialization();

    // Display characters and enemies stat boxes
    displayStatBoxes();

    // Set model for all combo boxes
    setComboBoxModels();

    // Set model for attacker and target lists
    setListModels();

    // Connect signals (name is changed in combo box) to slots (stats are displayed in stat box)
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialization()
{
    // Minor alignments
    ui->charInfoLayout->setAlignment(ui->charAttackerButton, Qt::AlignHCenter);
    ui->enemyInfoLayout->setAlignment(ui->enemyAttackerButton, Qt::AlignHCenter);
    ui->charActionLayout->setAlignment(ui->charDmglabel, Qt::AlignHCenter);
    ui->enemyActionLayout->setAlignment(ui->enemyDmglabel, Qt::AlignHCenter);

    // Disable battle group box
    ui->battleGroupBox->setEnabled(false);

    // Create models for char/enemy/weapon/armor name combo boxes
    m_charComboBoxModel = new QStandardItemModel;
    m_enemyComboBoxModel = new QStandardItemModel;
    m_weaponComboBoxModel = new QStandardItemModel;
    m_armorComboBoxModel = new QStandardItemModel;
    m_accessoryComboBoxModel = new QStandardItemModel;
    m_allComboBoxModels = new QVector<QStandardItemModel*>;
    m_allComboBoxModels->push_back(m_charComboBoxModel);
    m_allComboBoxModels->push_back(m_enemyComboBoxModel);
    m_allComboBoxModels->push_back(m_weaponComboBoxModel);
    m_allComboBoxModels->push_back(m_armorComboBoxModel);
    m_allComboBoxModels->push_back(m_accessoryComboBoxModel);

    // Create models for attacker and target lists
    m_charListViewModel = new QStandardItemModel;
    m_enemyListViewModel = new QStandardItemModel;

    // Create storage vector for char/enemy and build the AllChar vector,
    // which stores all characters
    m_charVector = new QVector<Character*>;
    m_enemyVector = new QVector<Character*>;
    m_allCharVector = new QVector<QVector<Character*>*>;
    m_allCharVector->push_back(m_charVector);
    m_allCharVector->push_back(m_enemyVector);

    // Create storage vector for weapons and armors and build the Item vector,
    // which stores all the items
    m_weaponVector = new QVector<Item*>;
    m_armorVector = new QVector<Item*>;
    m_accessoryVector = new QVector<Item*>;

    // Create blank char/enemy/weapon/armor for combo box purpose
    m_newChar = new Character("Character");
    m_newWeapon = new Item();
    m_newArmor = new Item();
    m_newAccessory = new Item();
    m_enemyVector->push_back(m_newChar);
    m_charVector->push_back(m_newChar);
    m_weaponVector->push_back(m_newWeapon);
    m_armorVector->push_back(m_newArmor);
    m_accessoryVector->push_back(m_newAccessory);
    m_charComboBoxModel->appendRow(new QStandardItem(""));
    m_enemyComboBoxModel->appendRow(new QStandardItem(""));
    m_weaponComboBoxModel->appendRow(new QStandardItem(""));
    m_armorComboBoxModel->appendRow(new QStandardItem(""));
    m_accessoryComboBoxModel->appendRow(new QStandardItem(""));

    // Create storage vector for char/enemy/weapon/armor combo boxes
    m_charComboBoxVector = new QVector<QComboBox*>;
    m_enemyComboBoxVector = new QVector<QComboBox*>;
    m_weaponComboBoxVector = new QVector<QComboBox*>;
    m_armorComboBoxVector = new QVector<QComboBox*>;
    m_accessoryComboBoxVector = new QVector<QComboBox*>;

    // Create storage vector for char/enemy stat boxes and build the AllStatBox vector,
    // which contains all stat boxes
    m_charStatBoxVector = new QVector<CharStatBox*>;
    m_enemyStatBoxVector = new QVector<CharStatBox*>;
    m_allStatBoxVector = new QVector<QVector<CharStatBox*>*>;
    m_allStatBoxVector->push_back(m_charStatBoxVector);
    m_allStatBoxVector->push_back(m_enemyStatBoxVector);
}

void MainWindow::displayStatBoxes()
{
    // Display character's stat boxes
    for (int iplayer(0); iplayer < m_nPlayerStatBox; iplayer++)
    {
        m_charStatBox = new CharStatBox("Character", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->characterLayout->addWidget(m_charStatBox);

        // Save combo boxes
        m_charComboBoxVector->push_back(m_charStatBox->getNameComboBox());
        m_weaponComboBoxVector->push_back(m_charStatBox->getWeaponComboBox());
        m_armorComboBoxVector->push_back(m_charStatBox->getArmorComboBox());
        m_accessoryComboBoxVector->push_back(m_charStatBox->getAccessoryComboBox());

        // Save the char stat box
        m_charStatBoxVector->push_back(m_charStatBox);
    }

    // Display enemy's stat boxes
    for (int ienemies(0); ienemies < m_nEnemyStatBox; ienemies++)
    {
        m_charStatBox = new CharStatBox("Enemy", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->enemyLayout->addWidget(m_charStatBox);

        // Save the name combo boxes
        m_enemyComboBoxVector->push_back(m_charStatBox->getNameComboBox());

        // Save the enemy stat box
        m_enemyStatBoxVector->push_back(m_charStatBox);
    }
}

void MainWindow::setComboBoxModels()
{
    // Characters
    for (int i(0); i < m_charComboBoxVector->size(); i++)
    {
        m_charComboBoxVector->at(i)->setModel(m_charComboBoxModel);
    }

    // Enemies
    for (int j(0); j < m_enemyComboBoxVector->size(); j++)
    {
        m_enemyComboBoxVector->at(j)->setModel(m_enemyComboBoxModel);
    }

    // Weapons
    for (int k(0); k < m_weaponComboBoxVector->size(); k++)
    {
        m_weaponComboBoxVector->at(k)->setModel(m_weaponComboBoxModel);
    }

    // Armors
    for (int l(0); l < m_armorComboBoxVector->size(); l++)
    {
        m_armorComboBoxVector->at(l)->setModel(m_armorComboBoxModel);
    }

    // Accessories
    for (int m(0); m < m_accessoryComboBoxVector->size(); m++)
    {
        m_accessoryComboBoxVector->at(m)->setModel(m_accessoryComboBoxModel);
    }
}

void MainWindow::setListModels()
{
    ui->charListView->setModel(m_charListViewModel);
    ui->enemyListView->setModel(m_enemyListViewModel);
}

void MainWindow::connectSignals()
{
    /* Note: I wanted to loop over combo boxes but the slot also needs the loop counter, and since I cannot pass any
     * additional argument in the signal, I could not find a more elegant way to NOT create different slots.
     * A better practice would be to customize the signal but I failed miserably. */
    QObject::connect(m_charComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillCharStatBox1(QString)));
    QObject::connect(m_charComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillCharStatBox2(QString)));
    QObject::connect(m_charComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillCharStatBox3(QString)));
    QObject::connect(m_charComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillCharStatBox4(QString)));

    QObject::connect(m_enemyComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillEnemyStatBox1(QString)));
    QObject::connect(m_enemyComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillEnemyStatBox2(QString)));
    QObject::connect(m_enemyComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillEnemyStatBox3(QString)));

    QObject::connect(m_weaponComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats1()));
    QObject::connect(m_weaponComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats2()));
    QObject::connect(m_weaponComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats3()));
    QObject::connect(m_weaponComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats4()));

    QObject::connect(m_armorComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats1()));
    QObject::connect(m_armorComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats2()));
    QObject::connect(m_armorComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats3()));
    QObject::connect(m_armorComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats4()));

    QObject::connect(m_accessoryComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats1()));
    QObject::connect(m_accessoryComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats2()));
    QObject::connect(m_accessoryComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats3()));
    QObject::connect(m_accessoryComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats4()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP4()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP4()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP4()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP4()));
}

void MainWindow::on_addCharButton_clicked(){newDialog("Character");}
void MainWindow::on_addWeaponButton_clicked(){newDialog("Weapon");}
void MainWindow::on_addArmorButton_clicked(){newDialog("Armor");}
void MainWindow::on_addAccessoryButton_clicked(){newDialog("Accessory");}
void MainWindow::on_addEnemyButton_clicked(){newDialog("Enemy");}

void MainWindow::on_newTableButton_clicked()
{
    bool ok;
    m_tableName = QInputDialog::getText(this, tr(""), tr("Table Name:"), QLineEdit::Normal, QString(), &ok);

    if (!m_tableName.isEmpty() && ok)
    {
        enableButtons();
        m_windowTitle = "Yelpy Fantasy: " + m_tableName;
        setWindowTitle(m_windowTitle);

        ui->newTableButton->setDisabled(true);
        ui->loadButton->setDisabled(true);
        ui->battleGroupBox->setEnabled(true);
    }
}
void MainWindow::on_saveButton_clicked()
{
    // First time the user is saving
    if (!m_alreadySaved)
    {
        //Open the save dialog that returns the complete filepath
        m_saveFilePath = QFileDialog::getSaveFileName(this, tr("Save file"), m_tableName + ".yf", tr("YF files (*.yf)"));

        // If user has selected a file, do the following:
        if (!m_saveFilePath.isEmpty())
        {
            // Create the save file
            m_saveFile = new QFile(m_saveFilePath);
            if (!m_saveFile->open(QIODevice::WriteOnly | QIODevice::Text)){return;}

            // Write everything needed
            writeToFile();

            // Close file
            m_saveFile->close();

            // Indicate that the first time save is done
            m_alreadySaved = true;
        }

    }
    else
    {
        if (!m_saveFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){return;}
        writeToFile();
        m_saveFile->close();
    }
}
void MainWindow::on_loadButton_clicked()
{
    // Open the file browser which returns the file path
    m_loadFilePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("YF Files (*.yf)"));

    // If user has selected a file, do the following:
    if (!m_loadFilePath.isEmpty())
    {
        // Create the load file
        m_loadFile = new QFile(m_loadFilePath);
        if (!m_loadFile->open(QIODevice::ReadOnly | QIODevice::Text)){return;}

        // Read everything needed
        readFromFile();

        // Close file
        m_loadFile->close();

        // Enable all buttons
        enableButtons();

        // Enable battle scene
        ui->battleGroupBox->setEnabled(true);

        // Disable the new table button
        ui->newTableButton->setEnabled(false);
    }
}
void MainWindow::on_exitButton_clicked(){MainWindow::close();}

void MainWindow::enableButtons()
{
    ui->addCharButton->setEnabled(true);
    ui->addWeaponButton->setEnabled(true);
    ui->addArmorButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->addEnemyButton->setEnabled(true);
    ui->addAccessoryButton->setEnabled(true);
    ui->fullRegenButton->setEnabled(true);
    ui->addAttackButton->setEnabled(true);
    ui->addMagicButton->setEnabled(true);
    ui->addSummonButton->setEnabled(true);
    ui->addItemButton->setEnabled(true);
}

void MainWindow::newDialog(QString newType)
{
    m_addCharDialog = new AddCharDialog(newType, this);
    QString windowTitle = "Add " + newType;
    m_addCharDialog->setWindowTitle(windowTitle);
    int dialogReturn = m_addCharDialog->exec();

    QString name = m_addCharDialog->getCharStatBox()->getStats()->value("Name")->displayText();

    if (dialogReturn == QDialog::Accepted && !name.isEmpty())
    {
        // Gather all character's stats
        QString level             = m_addCharDialog->getCharStatBox()->getStats()->value("Level")->displayText();
        QString hp                = m_addCharDialog->getCharStatBox()->getStats()->value("HPMax")->displayText();
        QString mp                = m_addCharDialog->getCharStatBox()->getStats()->value("MPMax")->displayText();
        QString hpMax             = m_addCharDialog->getCharStatBox()->getStats()->value("HPMax")->displayText();
        QString mpMax             = m_addCharDialog->getCharStatBox()->getStats()->value("MPMax")->displayText();
        QString strength          = m_addCharDialog->getCharStatBox()->getStats()->value("Strength")->displayText();
        QString vitality          = m_addCharDialog->getCharStatBox()->getStats()->value("Vitality")->displayText();
        QString magic             = m_addCharDialog->getCharStatBox()->getStats()->value("Magic")->displayText();
        QString spirit            = m_addCharDialog->getCharStatBox()->getStats()->value("Spirit")->displayText();
        QString dexterity         = m_addCharDialog->getCharStatBox()->getStats()->value("Dexterity")->displayText();
        QString luck            = m_addCharDialog->getCharStatBox()->getStats()->value("Luck")->displayText();
        QString attack            = m_addCharDialog->getCharStatBox()->getStats()->value("Attack")->displayText();
        QString attackPercent     = m_addCharDialog->getCharStatBox()->getStats()->value("AttackPercent")->displayText();
        QString magAttack         = m_addCharDialog->getCharStatBox()->getStats()->value("MagAttack")->displayText();
        QString magAttackPercent  = m_addCharDialog->getCharStatBox()->getStats()->value("MagAttackPercent")->displayText();
        QString critHitPercent    = m_addCharDialog->getCharStatBox()->getStats()->value("CritHitPercent")->displayText();
        QString defense           = m_addCharDialog->getCharStatBox()->getStats()->value("Defense")->displayText();
        QString magDefense        = m_addCharDialog->getCharStatBox()->getStats()->value("MagDefense")->displayText();
        QString defensePercent    = m_addCharDialog->getCharStatBox()->getStats()->value("DefensePercent")->displayText();
        QString magDefPercent     = m_addCharDialog->getCharStatBox()->getStats()->value("MagDefPercent")->displayText();
        QString weapon            = "None";
        QString armor             = "None";
        QString accessory         = "None";

        createNew(newType, name, level, hp, mp, hpMax, mpMax, strength, vitality, magic, spirit, dexterity, luck,
                  attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                  defense, defensePercent, magDefense, magDefPercent, weapon, armor, accessory);
    }
}

void MainWindow::createNew(QString newType, QString name, QString level, QString hp, QString mp, QString hpMax, QString mpMax, QString strength, QString vitality, QString magic,
                           QString spirit, QString dexterity, QString luck, QString attack, QString attackPercent, QString magAttack,
                           QString magAttackPercent, QString critHitPercent, QString defense, QString defensePercent, QString magDefense, QString magDefPercent,
                           QString weapon, QString armor, QString accessory)
{
    if (newType == "Character" || newType == "Enemy")
    {
        m_newChar = new Character(newType, name, level, hp, mp, hpMax, mpMax, strength, vitality, magic, spirit, dexterity, luck,
                                  attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                                  defense, defensePercent, magDefense, magDefPercent, weapon, armor, accessory);

        if (newType == "Character")
        {
            // Store the character
            m_charVector->push_back(m_newChar);

            // Populate the model for char combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_charComboBoxModel->appendRow(item);
        }
        else
        {
            // Store the enemy
            m_enemyVector->push_back(m_newChar);

            // Populate the model for enemy combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_enemyComboBoxModel->appendRow(item);
            m_enemyComboBoxModel->sort(0,Qt::AscendingOrder);
        }
    }
    else if (newType == "Weapon")
    {
        m_newWeapon = new Item(name, attack, attackPercent, magic, critHitPercent);

        // Store the weapon
        m_weaponVector->push_back(m_newWeapon);

        // Populate the model for weapon combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_weaponComboBoxModel->appendRow(item);
    }
    else if (newType == "Armor")
    {
        m_newArmor = new Item(name, magic, defense, magDefense, defensePercent, magDefPercent, strength);

        // Store the armor
        m_armorVector->push_back(m_newArmor);

        // Populate the model for armor combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_armorComboBoxModel->appendRow(item);
    }
    else
    {
        m_newAccessory = new Item(name, magic, strength, hpMax, mpMax, vitality, dexterity, luck, spirit);

        // Store the armor
        m_accessoryVector->push_back(m_newAccessory);

        // Populate the model for armor combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_accessoryComboBoxModel->appendRow(item);
    }

    // Sort all Combo Box Models
    for (int iModel(0); iModel < m_allComboBoxModels->size(); iModel++){m_allComboBoxModels->at(iModel)->sort(0, Qt::AscendingOrder);}
}

void MainWindow::fillCharStatBox1(QString charName){fillStatBox(0, "Character", charName);}
void MainWindow::fillCharStatBox2(QString charName){fillStatBox(1, "Character", charName);}
void MainWindow::fillCharStatBox3(QString charName){fillStatBox(2, "Character", charName);}
void MainWindow::fillCharStatBox4(QString charName){fillStatBox(3, "Character", charName);}

void MainWindow::fillEnemyStatBox1(QString enemyName){fillStatBox(0, "Enemy", enemyName);}
void MainWindow::fillEnemyStatBox2(QString enemyName){fillStatBox(1, "Enemy", enemyName);}
void MainWindow::fillEnemyStatBox3(QString enemyName){fillStatBox(2, "Enemy", enemyName);}

void MainWindow::updateStats1(){updateStats(0);}
void MainWindow::updateStats2(){updateStats(1);}
void MainWindow::updateStats3(){updateStats(2);}
void MainWindow::updateStats4(){updateStats(3);}

void MainWindow::checkHPMP1(){checkHPMP(0);}
void MainWindow::checkHPMP2(){checkHPMP(1);}
void MainWindow::checkHPMP3(){checkHPMP(2);}
void MainWindow::checkHPMP4(){checkHPMP(3);}

void MainWindow::setCurrentHPMP1(){setCurrentHPMP(0);}
void MainWindow::setCurrentHPMP2(){setCurrentHPMP(1);}
void MainWindow::setCurrentHPMP3(){setCurrentHPMP(2);}
void MainWindow::setCurrentHPMP4(){setCurrentHPMP(3);}

void MainWindow::checkHPMP(int i)
{
    QString hpDisplay = m_charStatBoxVector->at(i)->getStats()->value("HP")->displayText();
    QString hpMaxDisplay = m_charStatBoxVector->at(i)->getStats()->value("HPMax")->displayText();
    QString mpDisplay = m_charStatBoxVector->at(i)->getStats()->value("MP")->displayText();
    QString mpMaxDisplay = m_charStatBoxVector->at(i)->getStats()->value("MPMax")->displayText();

    if (hpDisplay.toInt() > hpMaxDisplay.toInt())
    {
        m_charStatBoxVector->at(i)->getStats()->value("HP")->setText(hpMaxDisplay);
    }
    if (mpDisplay.toInt() > mpMaxDisplay.toInt())
    {
        m_charStatBoxVector->at(i)->getStats()->value("MP")->setText(mpMaxDisplay);
    }
}

void MainWindow::setCurrentHPMP(int i)
{
    //Get character's name and new values of HP and MP
    QString name = m_charComboBoxVector->at(i)->currentText();
    QString hpDisplay = m_charStatBoxVector->at(i)->getStats()->value("HP")->displayText();
    QString mpDisplay = m_charStatBoxVector->at(i)->getStats()->value("MP")->displayText();

    //Loop on characters, find character and update new values of HP and MP
    for (int iChar(0); iChar < m_charVector->size(); iChar++)
    {
        if (m_charVector->at(iChar)->getStats()->value("Name") == name)
        {
            m_charVector->at(iChar)->setStat("HP", hpDisplay);
            m_charVector->at(iChar)->setStat("MP", mpDisplay);
        }
    }
}

void MainWindow::fillStatBox(int i, QString charType, QString charName)
{
    int itype(0);
    if (charType == "Enemy"){itype = 1;}

    // Find the character in the storage vector
    for (int it(0); it < m_allCharVector->at(itype)->size(); it++)
    {
        if(m_allCharVector->at(itype)->at(it)->getStats()->value("Name") == charName)
        {
            //Get relevant stats
            QString level           = m_allCharVector->at(itype)->at(it)->getStats()->value("Level");
            QString hp              = m_allCharVector->at(itype)->at(it)->getStats()->value("HP");
            QString hpMax           = m_allCharVector->at(itype)->at(it)->getStats()->value("HPMax");
            QString mp              = m_allCharVector->at(itype)->at(it)->getStats()->value("MP");
            QString mpMax           = m_allCharVector->at(itype)->at(it)->getStats()->value("MPMax");
            QString strength        = m_allCharVector->at(itype)->at(it)->getStats()->value("Strength");
            QString vitality        = m_allCharVector->at(itype)->at(it)->getStats()->value("Vitality");
            QString magic           = m_allCharVector->at(itype)->at(it)->getStats()->value("Magic");
            QString spirit          = m_allCharVector->at(itype)->at(it)->getStats()->value("Spirit");
            QString dexterity       = m_allCharVector->at(itype)->at(it)->getStats()->value("Dexterity");
            QString luck            = m_allCharVector->at(itype)->at(it)->getStats()->value("Luck");
            QString attack          = m_allCharVector->at(itype)->at(it)->getStats()->value("Attack");
            QString attackPercent   = m_allCharVector->at(itype)->at(it)->getStats()->value("AttackPercent");
            QString magAttack       = m_allCharVector->at(itype)->at(it)->getStats()->value("MagAttack");
            QString magAttackPercent= m_allCharVector->at(itype)->at(it)->getStats()->value("MagAttackPercent");
            QString critHitPercent  = m_allCharVector->at(itype)->at(it)->getStats()->value("CritHitPercent");
            QString defense         = m_allCharVector->at(itype)->at(it)->getStats()->value("Defense");
            QString defensePercent  = m_allCharVector->at(itype)->at(it)->getStats()->value("DefensePercent");
            QString magDefense      = m_allCharVector->at(itype)->at(it)->getStats()->value("MagDefense");
            QString magDefPercent   = m_allCharVector->at(itype)->at(it)->getStats()->value("MagDefPercent");
            QString weapon          = m_allCharVector->at(itype)->at(it)->getStats()->value("Weapon");
            QString armor           = m_allCharVector->at(itype)->at(it)->getStats()->value("Armor");
            QString accessory       = m_allCharVector->at(itype)->at(it)->getStats()->value("Accessory");

            // If character does not have any items (e.g. it is an enemy or a character who has just been created)
            if (weapon == "None" && armor == "None" && accessory == "None")
            {
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Level")->setText(level);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("HP")->setText(hp);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("HPMax")->setText(hpMax);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MP")->setText(mp);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MPMax")->setText(mpMax);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Strength")->setText(strength);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Vitality")->setText(vitality);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Magic")->setText(magic);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Spirit")->setText(spirit);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Dexterity")->setText(dexterity);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Luck")->setText(luck);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Attack")->setText(attack);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("AttackPercent")->setText(attackPercent);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MagAttack")->setText(magAttack);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MagAttackPercent")->setText(magAttackPercent);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("CritHitPercent")->setText(critHitPercent);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Defense")->setText(defense);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("DefensePercent")->setText(defensePercent);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MagDefense")->setText(magDefense);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MagDefPercent")->setText(magDefPercent);
            }
            else
            {
                // Use items to update most stats.
                m_accessoryComboBoxVector->at(i)->setCurrentText(accessory);
                m_weaponComboBoxVector->at(i)->setCurrentText(weapon);
                m_armorComboBoxVector->at(i)->setCurrentText(armor);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Level")->setText(level);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("HP")->setText(hp);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MP")->setText(mp);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MagAttack")->setText(magAttack);
                m_allStatBoxVector->at(itype)->at(i)->getStats()->value("MagAttackPercent")->setText(magAttackPercent);
            }

            // Populate the model for character's battle list

            QStandardItem *item = new QStandardItem(charName);
            if (itype == 0){m_charListViewModel->setItem(i, item);}
            else{m_enemyListViewModel->setItem(i, item);}
        }
    }
}

void MainWindow::updateStats(int i)
{
    // Initialize some stuff
    QString charName;
    QString charAttack, charAttackPercent, charMagic, charCritHitPercent, charStrength;
    QString charDefense, charDefensePercent, charMagDefense, charMagDefPercent;
    QString charHP, charMP, charHPMax, charMPMax, charVitality, charSpirit, charDexterity, charLuck;
    QString weaponAttack, weaponAttackPercent, weaponMagic, weaponCritHitPercent;
    QString armorDefense, armorDefensePercent, armorMagDefense, armorMagDefPercent, armorMagic, armorStrength;
    QString accessoryMagic, accessoryStrength, accessoryHP, accessoryMP, accessoryVitality;
    QString accessoryDexterity, accessoryLuck, accessorySpirit;

    // Get weapon, armor, and accessory names in the current i-th stat box.
    QString weaponName = m_weaponComboBoxVector->at(i)->currentText();
    QString armorName = m_armorComboBoxVector->at(i)->currentText();
    QString accessoryName = m_accessoryComboBoxVector->at(i)->currentText();

    // Get whose stat box this is
    charName = m_charComboBoxVector->at(i)->currentText();

    // Loop over character and set weapon, armor, and accessory to this character
    for (int iChar(0); iChar < m_charVector->size(); iChar++)
    {
        if (m_charVector->at(iChar)->getStats()->value("Name") == charName)
        {
            m_charVector->at(iChar)->setItems(weaponName, armorName, accessoryName);
        }
    }

    // Find the weapon in the weapons list
    for (int iWeapon(0); iWeapon < m_weaponVector->size(); iWeapon++)
    {
        if (m_weaponVector->at(iWeapon)->getStats()->value("Name") == weaponName)
        {
            // Get relevant stats
            weaponAttack = m_weaponVector->at(iWeapon)->getStats()->value("Attack");
            weaponAttackPercent = m_weaponVector->at(iWeapon)->getStats()->value("AttackPercent");
            weaponMagic = m_weaponVector->at(iWeapon)->getStats()->value("Magic");
            weaponCritHitPercent = m_weaponVector->at(iWeapon)->getStats()->value("CritHitPercent");
        }
    }

    // Find the armor in the armors list
    for (int iArmor(0); iArmor < m_armorVector->size(); iArmor++)
    {
        if (m_armorVector->at(iArmor)->getStats()->value("Name") == armorName)
        {
            // Get relevant stats
            armorDefense = m_armorVector->at(iArmor)->getStats()->value("Defense");
            armorDefensePercent = m_armorVector->at(iArmor)->getStats()->value("DefensePercent");
            armorMagDefense = m_armorVector->at(iArmor)->getStats()->value("MagDefense");
            armorMagDefPercent = m_armorVector->at(iArmor)->getStats()->value("MagDefPercent");
            armorMagic = m_armorVector->at(iArmor)->getStats()->value("Magic");
            armorStrength = m_armorVector->at(iArmor)->getStats()->value("Strength");
        }
    }

    // Find the accessory in the accessories list
    for (int iAccessory(0); iAccessory < m_accessoryVector->size(); iAccessory++)
    {
        if (m_accessoryVector->at(iAccessory)->getStats()->value("Name") == accessoryName)
        {
            // Get relevant stats
            accessoryMagic = m_accessoryVector->at(iAccessory)->getStats()->value("Magic");
            accessoryStrength = m_accessoryVector->at(iAccessory)->getStats()->value("Strength");
            accessoryHP = m_accessoryVector->at(iAccessory)->getStats()->value("HPMax");
            accessoryMP = m_accessoryVector->at(iAccessory)->getStats()->value("MPMax");
            accessoryVitality = m_accessoryVector->at(iAccessory)->getStats()->value("Vitality");
            accessorySpirit = m_accessoryVector->at(iAccessory)->getStats()->value("Spirit");
            accessoryDexterity = m_accessoryVector->at(iAccessory)->getStats()->value("Dexterity");
            accessoryLuck = m_accessoryVector->at(iAccessory)->getStats()->value("Luck");
        }
    }

    //Loop on characters and get the base stats values
    for (int iChar(0); iChar < m_charVector->size(); iChar++)
    {
        if(m_charVector->at(iChar)->getStats()->value("Name") == charName)
        {
            charAttack = m_charVector->at(iChar)->getStats()->value("Attack");
            charAttackPercent = m_charVector->at(iChar)->getStats()->value("AttackPercent");
            charMagic = m_charVector->at(iChar)->getStats()->value("Magic");
            charStrength = m_charVector->at(iChar)->getStats()->value("Strength");
            charCritHitPercent = m_charVector->at(iChar)->getStats()->value("CritHitPercent");
            charDefense = m_charVector->at(iChar)->getStats()->value("Defense");
            charDefensePercent = m_charVector->at(iChar)->getStats()->value("DefensePercent");
            charMagDefense = m_charVector->at(iChar)->getStats()->value("MagDefense");
            charMagDefPercent = m_charVector->at(iChar)->getStats()->value("MagDefPercent");
            charHP = m_charVector->at(iChar)->getStats()->value("HP");
            charMP = m_charVector->at(iChar)->getStats()->value("MP");
            charHPMax = m_charVector->at(iChar)->getStats()->value("HPMax");
            charMPMax = m_charVector->at(iChar)->getStats()->value("MPMax");
            charVitality = m_charVector->at(iChar)->getStats()->value("Vitality");
            charSpirit = m_charVector->at(iChar)->getStats()->value("Spirit");
            charDexterity = m_charVector->at(iChar)->getStats()->value("Dexterity");
            charLuck = m_charVector->at(iChar)->getStats()->value("Luck");
        }
    }

    // Compute new values
    charMagic = QString::number(charMagic.toInt() + weaponMagic.toInt() + armorMagic.toInt() + accessoryMagic.toInt());
    charStrength = QString::number(charStrength.toInt() + armorStrength.toInt() + accessoryStrength.toInt());
    charVitality = QString::number(charVitality.toInt() + accessoryVitality.toInt());
    charSpirit = QString::number(charSpirit.toInt() + accessorySpirit.toInt());
    charDexterity = QString::number(charDexterity.toInt() + accessoryDexterity.toInt());
    charLuck = QString::number(charLuck.toInt() + accessoryLuck.toInt());
    charHPMax = QString::number(charHPMax.toInt() + accessoryHP.toInt());
    charMPMax = QString::number(charMPMax.toInt() + accessoryMP.toInt());
    charAttack = QString::number(charAttack.toInt() + weaponAttack.toInt());
    charAttackPercent = QString::number(charAttackPercent.toInt() + weaponAttackPercent.toInt());
    charCritHitPercent = QString::number(charCritHitPercent.toInt() + weaponCritHitPercent.toInt());
    charDefense = QString::number(charDefense.toInt() + armorDefense.toInt());
    charDefensePercent = QString::number(charDefensePercent.toInt() + armorDefensePercent.toInt());
    charMagDefense = QString::number(charMagDefense.toInt() + armorMagDefense.toInt());
    charMagDefPercent = QString::number(charMagDefPercent.toInt() + armorMagDefPercent.toInt());


    // Fill stat box with new values
    m_charStatBoxVector->at(i)->getStats()->value("Magic")->setText(charMagic);
    m_charStatBoxVector->at(i)->getStats()->value("Strength")->setText(charStrength);
    m_charStatBoxVector->at(i)->getStats()->value("Vitality")->setText(charVitality);
    m_charStatBoxVector->at(i)->getStats()->value("Spirit")->setText(charSpirit);
    m_charStatBoxVector->at(i)->getStats()->value("Dexterity")->setText(charDexterity);
    m_charStatBoxVector->at(i)->getStats()->value("Luck")->setText(charLuck);
    m_charStatBoxVector->at(i)->getStats()->value("HPMax")->setText(charHPMax);
    m_charStatBoxVector->at(i)->getStats()->value("MPMax")->setText(charMPMax);
    m_charStatBoxVector->at(i)->getStats()->value("Attack")->setText(charAttack);
    m_charStatBoxVector->at(i)->getStats()->value("AttackPercent")->setText(charAttackPercent);
    m_charStatBoxVector->at(i)->getStats()->value("CritHitPercent")->setText(charCritHitPercent);
    m_charStatBoxVector->at(i)->getStats()->value("Defense")->setText(charDefense);
    m_charStatBoxVector->at(i)->getStats()->value("DefensePercent")->setText(charDefensePercent);
    m_charStatBoxVector->at(i)->getStats()->value("MagDefense")->setText(charMagDefense);
    m_charStatBoxVector->at(i)->getStats()->value("MagDefPercent")->setText(charMagDefPercent);
}

void MainWindow::writeToFile()
{
    // Create output text stream
    QTextStream write(m_saveFile);

    // Write Table name
    write << "Table Name: " << m_tableName << "\n";

    // Write number of characters, enemies, weapons, armors and accessories.
    // Note the -1 because there's always a dummy class for combo box purposes.
    m_nChar = QString::number(m_allCharVector->at(0)->size()-1);
    m_nEnemies = QString::number(m_allCharVector->at(1)->size()-1);
    m_nWeapons = QString::number(m_weaponVector->size()-1);
    m_nArmors = QString::number(m_armorVector->size()-1);
    m_nAccessories = QString::number(m_accessoryVector->size()-1);

    write << "Characters: " << m_nChar << " | Enemies: " << m_nEnemies <<
             " | Weapons: " << m_nWeapons << " | Armors: " << m_nArmors <<
             " | Accessories: " << m_nAccessories << "\n";

    /* Big fat loop to write all stats from characters, enemies, and items.
     * Type 1: characters
     * Type 2: enemies
     * Type 3: weapons
     * Type 4: armors
     * Type 5: accessories */
    for (int iType(0); iType < 5; iType++)
    {
        int nMax(0);
        QMap<QString, QString> *charStat = new QMap<QString, QString>;
        QVector<Character*> *charVector = new QVector<Character*>;
        QVector<Item*> *itemVector = new QVector<Item*>;

        if (iType == 0){write << "========= CHARACTERS =========\n"; nMax = m_charVector->size(); charVector = m_charVector;}
        else if (iType == 1){write << "========= BESTIARY =========\n"; nMax = m_enemyVector->size(); charVector = m_enemyVector;}
        else if (iType == 2){write << "========= WEAPONS =========\n"; nMax = m_weaponVector->size(); itemVector = m_weaponVector;}
        else if (iType == 3){write << "========= ARMORS =========\n"; nMax = m_armorVector->size(); itemVector = m_armorVector;}
        else {write << "========= ACCESSORIES =========\n"; nMax = m_accessoryVector->size(); itemVector = m_accessoryVector;}

        for (int i(0); i < nMax; i++)
        {
            // Get the name of the thing we are looping over
            QString name;
            if (iType == 0 || iType == 1){name = charVector->at(i)->getStats()->value("Name");}
            else {name = itemVector->at(i)->getStats()->value("Name");}

            if (!name.isEmpty())
            {
                if (iType == 0){write << "Character " << i << ":\n";}
                else if (iType == 1){write << "Enemy " << i << ":\n";}
                else if (iType == 2){write << "Weapon " << i << ":\n";}
                else if (iType == 3){write << "Armor " << i << ":\n";}
                else {write << "Accessory " << i << ":\n";}

                // Navigate through the stat QMap
                if (iType == 0 || iType == 1){charStat = charVector->at(i)->getStats();}
                else {charStat = itemVector->at(i)->getStats();}

                QMap<QString, QString>::const_iterator it = charStat->constBegin();
                while (it != charStat->constEnd())
                {
                    write << it.key() << ": " << it.value() << " | ";
                    it++;
                }
                write << "\n";
            }
        }
    }
}

void MainWindow::readFromFile()
{
    // Create input text stream
    QTextStream read(m_loadFile);

    // Get table Name
    m_tableName = read.readLine().split(": ")[1];
    m_windowTitle = "Yelpy Fantasy: " + m_tableName;
    setWindowTitle(m_windowTitle);

    // Get number of characters, enemies, weapons and accessories
    QStringList lineList = read.readLine().split(" | ");
    m_nChar = lineList[0].split(": ")[1];
    m_nEnemies = lineList[1].split(": ")[1];
    m_nWeapons = lineList[2].split(": ")[1];
    m_nArmors = lineList[3].split(": ")[1];
    m_nAccessories = lineList[4].split(": ")[1];    

    /* Big fat loop to get all stats from characters, enemies, and items.
     * Type 1: characters
     * Type 2: enemies
     * Type 3: weapons
     * Type 4: armors
     * Type 5: accessories */
    for (int iType(0); iType < 5; iType++)
    {
        int nMax(0);
        QString type;

        read.readLine();
        if (iType == 0){nMax = m_nChar.toInt(); type = "Character";}
        else if (iType == 1){nMax = m_nEnemies.toInt(); type = "Enemy";}
        else if (iType == 2){nMax = m_nWeapons.toInt(); type = "Weapon";}
        else if (iType == 3){nMax = m_nArmors.toInt(); type = "Armor";}
        else {nMax = m_nAccessories.toInt(); type = "Accessory";}

        for (int i(0); i < nMax; i++)
        {
            read.readLine();
            QStringList innerList = read.readLine().split(" | ", QString::SkipEmptyParts);

            // Create the stat bundle
            QMap<QString, QString> *statBundle = new QMap<QString, QString>;

            // Navigate through the stat list and populate the bundle
            for (int iElement(0); iElement < innerList.size(); iElement++)
            {
                QStringList statPair = innerList.at(iElement).split(": ");
                statBundle->insert(statPair[0],statPair[1]);
            }

            // Gather all character's stats
            QString name              = statBundle->value("Name");
            QString level             = statBundle->value("Level");
            QString hp                = statBundle->value("HP");
            QString hpMax             = statBundle->value("HPMax");
            QString mp                = statBundle->value("MP");
            QString mpMax             = statBundle->value("MPMax");
            QString strength          = statBundle->value("Strength");
            QString vitality          = statBundle->value("Vitality");
            QString magic             = statBundle->value("Magic");
            QString spirit            = statBundle->value("Spirit");
            QString dexterity         = statBundle->value("Dexterity");
            QString luck            = statBundle->value("Luck");
            QString attack            = statBundle->value("Attack");
            QString attackPercent     = statBundle->value("AttackPercent");
            QString magAttack         = statBundle->value("MagAttack");
            QString magAttackPercent  = statBundle->value("MagAttackPercent");
            QString critHitPercent    = statBundle->value("CritHitPercent");
            QString defense           = statBundle->value("Defense");
            QString magDefense        = statBundle->value("MagDefense");
            QString defensePercent    = statBundle->value("DefensePercent");
            QString magDefPercent     = statBundle->value("MagDefPercent");
            QString weapon            = statBundle->value("Weapon");
            QString armor             = statBundle->value("Armor");
            QString accessory         = statBundle->value("Accessory");

            // Create character/enemy
            createNew(type, name, level, hp, mp, hpMax, mpMax, strength, vitality, magic, spirit, dexterity, luck,
                      attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                      defense, defensePercent, magDefense, magDefPercent, weapon, armor, accessory);
        }
    }
}

void MainWindow::on_fullRegenButton_clicked()
{
    for (int iBox(0); iBox < m_nPlayerStatBox; iBox++)
    {
        //Get character's name
        QString name = m_charComboBoxVector->at(iBox)->currentText();

        //Loop on characters, find character and update HP and MP
        for (int iChar(0); iChar < m_charVector->size(); iChar++)
        {
            if (m_charVector->at(iChar)->getStats()->value("Name") == name)
            {
                // We use the displayed value of HPMax and MPMax rather than the base value,
                // which does not account for accessories bonus.
                QString hpMaxDisplay = m_charStatBoxVector->at(iBox)->getStats()->value("HPMax")->displayText();
                QString mpMaxDisplay = m_charStatBoxVector->at(iBox)->getStats()->value("MPMax")->displayText();
                m_charStatBoxVector->at(iBox)->getStats()->value("HP")->setText(hpMaxDisplay);
                m_charStatBoxVector->at(iBox)->getStats()->value("MP")->setText(mpMaxDisplay);
            }
        }
    }
}
