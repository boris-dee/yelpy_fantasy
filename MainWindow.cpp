#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QString>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize some useful stuff (models and storage vectors)
    initialization();

    // Display characters and enemies stat boxes
    displayStatBoxes();

    // Set all QLineEdits to readonly and make them smaller
    formatLineEdits();

    // Set model for all combo boxes
    setComboBoxModels();

    // Connect signals (name is changed in combo box) to slots (stats are displayed in stat box)
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialization()
{
    // Create models for char/enemy/weapon/armor name combo boxes
    m_charComboBoxModel = new QStandardItemModel;
    m_enemyComboBoxModel = new QStandardItemModel;
    m_weaponComboBoxModel = new QStandardItemModel;
    m_armorComboBoxModel = new QStandardItemModel;
    m_accessoryComboBoxModel = new QStandardItemModel;

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
    for (int iplayer(0); iplayer < m_nPlayers; iplayer++)
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
    for (int ienemies(0); ienemies < m_nEnemies; ienemies++)
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

void MainWindow::formatLineEdits()
{
    QList<QLineEdit*> allQLineEdit = findChildren<QLineEdit*>();
    for (int i(0); i < allQLineEdit.size(); i++)
    {
        allQLineEdit.at(i)->setReadOnly(true);
        allQLineEdit.at(i)->setMaximumHeight(20);
        allQLineEdit.at(i)->setMaximumWidth(40);
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
}

void MainWindow::on_addCharButton_clicked(){createNew("Character");}
void MainWindow::on_addWeaponButton_clicked(){createNew("Weapon");}
void MainWindow::on_addArmorButton_clicked(){createNew("Armor");}
void MainWindow::on_addAccessoryButton_clicked(){createNew("Accessory");}
void MainWindow::on_newButton_clicked()
{
    bool ok;
    QString m_tableName = QInputDialog::getText(this, tr(""), tr("Table Name:"), QLineEdit::Normal, QString(), &ok);

    if (!m_tableName.isEmpty() && ok)
    {
        ui->addCharButton->setEnabled(true);
        ui->addWeaponButton->setEnabled(true);
        ui->addArmorButton->setEnabled(true);
        ui->saveButton->setEnabled(true);
        ui->addEnemyButton->setEnabled(true);
        ui->addAccessoryButton->setEnabled(true);

        m_windowTitle = "Yelpy Fantasy: " + m_tableName;
        setWindowTitle(m_windowTitle);
    }
}
void MainWindow::on_saveButton_clicked(){}
void MainWindow::on_loadButton_clicked()
{
    // Open the file browser which returns the file path
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "SAV Files (*.sav)");

    // If user has selected a file, do the following:
    if (!filePath.isEmpty())
    {
        // Enable all buttons
        ui->addCharButton->setEnabled(true);
        ui->addWeaponButton->setEnabled(true);
        ui->addArmorButton->setEnabled(true);
        ui->saveButton->setEnabled(true);
        ui->addEnemyButton->setEnabled(true);
        ui->addAccessoryButton->setEnabled(true);
    }
}
void MainWindow::on_exitButton_clicked(){MainWindow::close();}
void MainWindow::on_addEnemyButton_clicked(){createNew("Enemy");}

void MainWindow::createNew(QString newType)
{
    m_addCharDialog = new AddCharDialog(newType, this);
    QString windowTitle = "Add " + newType;
    m_addCharDialog->setWindowTitle(windowTitle);
    int dialogReturn = m_addCharDialog->exec();

    // Gather all character's stats
    QString name              = m_addCharDialog->getCharStatBox()->getStats()->value("Name")->displayText();
    QString level             = m_addCharDialog->getCharStatBox()->getStats()->value("Level")->displayText();
    QString hp                = m_addCharDialog->getCharStatBox()->getStats()->value("HP")->displayText();
    QString mp                = m_addCharDialog->getCharStatBox()->getStats()->value("MP")->displayText();
    QString strength          = m_addCharDialog->getCharStatBox()->getStats()->value("Strength")->displayText();
    QString vitality          = m_addCharDialog->getCharStatBox()->getStats()->value("Vitality")->displayText();
    QString magic             = m_addCharDialog->getCharStatBox()->getStats()->value("Magic")->displayText();
    QString spirit            = m_addCharDialog->getCharStatBox()->getStats()->value("Spirit")->displayText();
    QString dexterity         = m_addCharDialog->getCharStatBox()->getStats()->value("Dexterity")->displayText();
    QString chance            = m_addCharDialog->getCharStatBox()->getStats()->value("Chance")->displayText();
    QString attack            = m_addCharDialog->getCharStatBox()->getStats()->value("Attack")->displayText();
    QString attackPercent     = m_addCharDialog->getCharStatBox()->getStats()->value("AttackPercent")->displayText();
    QString magAttack         = m_addCharDialog->getCharStatBox()->getStats()->value("MagAttack")->displayText();
    QString magAttackPercent  = m_addCharDialog->getCharStatBox()->getStats()->value("MagAttackPercent")->displayText();
    QString critHitPercent    = m_addCharDialog->getCharStatBox()->getStats()->value("CritHitPercent")->displayText();
    QString defense           = m_addCharDialog->getCharStatBox()->getStats()->value("Defense")->displayText();
    QString magDefense        = m_addCharDialog->getCharStatBox()->getStats()->value("MagDefense")->displayText();
    QString defensePercent    = m_addCharDialog->getCharStatBox()->getStats()->value("DefensePercent")->displayText();
    QString magDefPercent     = m_addCharDialog->getCharStatBox()->getStats()->value("MagDefPercent")->displayText();

    if (dialogReturn == QDialog::Accepted && !name.isEmpty())
    {
        // Create the character/enemy/weapon/armor/accessory
        if (newType == "Character" || newType == "Enemy")
        {
            m_newChar = new Character(newType, name, level, hp, mp, strength, vitality, magic, spirit, dexterity, chance,
                                      attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                                      defense, defensePercent, magDefense, magDefPercent);

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
            m_newAccessory = new Item(name, magic, strength, hp, mp, vitality, dexterity, chance, spirit);

            // Store the armor
            m_accessoryVector->push_back(m_newAccessory);

            // Populate the model for armor combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_accessoryComboBoxModel->appendRow(item);
        }
    }
}

void MainWindow::fillCharStatBox1(QString charName){fillStatBox(0, "Character", charName);}
void MainWindow::fillCharStatBox2(QString charName){fillStatBox(1, "Character", charName);}
void MainWindow::fillCharStatBox3(QString charName){fillStatBox(2, "Character", charName);}
void MainWindow::fillCharStatBox4(QString charName){fillStatBox(3, "Character", charName);}

void MainWindow::fillEnemyStatBox1(QString enemyName){fillStatBox(0, "Enemy", enemyName);}
void MainWindow::fillEnemyStatBox2(QString enemyName){fillStatBox(1, "Enemy", enemyName);}

void MainWindow::updateStats1(){updateStats(0);}
void MainWindow::updateStats2(){updateStats(1);}
void MainWindow::updateStats3(){updateStats(2);}
void MainWindow::updateStats4(){updateStats(3);}

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
            QString chance          = m_allCharVector->at(itype)->at(it)->getStats()->value("Chance");
            QString attack          = m_allCharVector->at(itype)->at(it)->getStats()->value("Attack");
            QString attackPercent   = m_allCharVector->at(itype)->at(it)->getStats()->value("AttackPercent");
            QString magAttack       = m_allCharVector->at(itype)->at(it)->getStats()->value("MagAttack");
            QString magAttackPercent= m_allCharVector->at(itype)->at(it)->getStats()->value("MagAttackPercent");
            QString critHitPercent  = m_allCharVector->at(itype)->at(it)->getStats()->value("CritHitPercent");
            QString defense         = m_allCharVector->at(itype)->at(it)->getStats()->value("Defense");
            QString defensePercent  = m_allCharVector->at(itype)->at(it)->getStats()->value("DefensePercent");
            QString magDefense      = m_allCharVector->at(itype)->at(it)->getStats()->value("MagDefense");
            QString magDefPercent   = m_allCharVector->at(itype)->at(it)->getStats()->value("MagDefPercent");

            // Fill stat box
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
            m_allStatBoxVector->at(itype)->at(i)->getStats()->value("Chance")->setText(chance);
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
    }
}

void MainWindow::updateStats(int i)
{
    // Initialize some stuff
    QString charName;
    QString charAttack, charAttackPercent, charMagic, charCritHitPercent, charStrength;
    QString charDefense, charDefensePercent, charMagDefense, charMagDefPercent;
    QString charHP, charMP, charVitality, charSpirit, charDexterity, charChance;
    QString weaponAttack, weaponAttackPercent, weaponMagic, weaponCritHitPercent;
    QString armorDefense, armorDefensePercent, armorMagDefense, armorMagDefPercent, armorMagic, armorStrength;
    QString accessoryMagic, accessoryStrength, accessoryHP, accessoryMP, accessoryVitality;
    QString accessoryDexterity, accessoryChance, accessorySpirit;

    // Get weapon, armor, and accessory names in the current i-th stat box.
    QString weaponName = m_weaponComboBoxVector->at(i)->currentText();
    QString armorName = m_armorComboBoxVector->at(i)->currentText();
    QString accessoryName = m_accessoryComboBoxVector->at(i)->currentText();

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
            accessoryHP = m_accessoryVector->at(iAccessory)->getStats()->value("HP");
            accessoryMP = m_accessoryVector->at(iAccessory)->getStats()->value("MP");
            accessoryVitality = m_accessoryVector->at(iAccessory)->getStats()->value("Vitality");
            accessorySpirit = m_accessoryVector->at(iAccessory)->getStats()->value("Spirit");
            accessoryDexterity = m_accessoryVector->at(iAccessory)->getStats()->value("Dexterity");
            accessoryChance = m_accessoryVector->at(iAccessory)->getStats()->value("Chance");
        }
    }

    // Get the character's base values.
    //   1. Find the corresponding character
    charName = m_charComboBoxVector->at(i)->currentText();

    //   2. Loop on characters and get the base stats values
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
            charVitality = m_charVector->at(iChar)->getStats()->value("Vitality");
            charSpirit = m_charVector->at(iChar)->getStats()->value("Spirit");
            charDexterity = m_charVector->at(iChar)->getStats()->value("Dexterity");
            charChance = m_charVector->at(iChar)->getStats()->value("Chance");
        }
    }

    // Compute new values
    charMagic = QString::number(charMagic.toInt() + weaponMagic.toInt() + armorMagic.toInt() + accessoryMagic.toInt());
    charStrength = QString::number(charStrength.toInt() + armorStrength.toInt() + accessoryStrength.toInt());
    charVitality = QString::number(charVitality.toInt() + accessoryVitality.toInt());
    charSpirit = QString::number(charSpirit.toInt() + accessorySpirit.toInt());
    charDexterity = QString::number(charDexterity.toInt() + accessoryDexterity.toInt());
    charChance = QString::number(charChance.toInt() + accessoryChance.toInt());
    charHP = QString::number(charHP.toInt() + accessoryHP.toInt());
    charMP = QString::number(charMP.toInt() + accessoryMP.toInt());
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
    m_charStatBoxVector->at(i)->getStats()->value("Chance")->setText(charChance);
    m_charStatBoxVector->at(i)->getStats()->value("HPMax")->setText(charHP);
    m_charStatBoxVector->at(i)->getStats()->value("MPMax")->setText(charMP);
    m_charStatBoxVector->at(i)->getStats()->value("Attack")->setText(charAttack);
    m_charStatBoxVector->at(i)->getStats()->value("AttackPercent")->setText(charAttackPercent);
    m_charStatBoxVector->at(i)->getStats()->value("CritHitPercent")->setText(charCritHitPercent);
    m_charStatBoxVector->at(i)->getStats()->value("Defense")->setText(charDefense);
    m_charStatBoxVector->at(i)->getStats()->value("DefensePercent")->setText(charDefensePercent);
    m_charStatBoxVector->at(i)->getStats()->value("MagDefense")->setText(charMagDefense);
    m_charStatBoxVector->at(i)->getStats()->value("MagDefPercent")->setText(charMagDefPercent);
}
