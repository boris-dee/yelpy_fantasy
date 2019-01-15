#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QtMath>

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
    ui->charInfoLayout->setAlignment(ui->charListView, Qt::AlignHCenter);
    ui->enemyInfoLayout->setAlignment(ui->enemyListView, Qt::AlignHCenter);
    ui->charActionLayout->setAlignment(ui->charAttDmgEdit, Qt::AlignRight);
    ui->charActionLayout->setAlignment(ui->charMagDmgEdit, Qt::AlignRight);
    ui->charActionLayout->setAlignment(ui->charSumDmgEdit, Qt::AlignRight);
    ui->enemyActionLayout->setAlignment(ui->enemyAttDmgEdit, Qt::AlignLeft);
    ui->enemyActionLayout->setAlignment(ui->enemyMagDmgEdit, Qt::AlignLeft);

    // Disable battle group box
    ui->battleGroupBox->setEnabled(false);

    // Create models for name combo boxes
    m_charComboBoxModel = new QStandardItemModel;
    m_enemyComboBoxModel = new QStandardItemModel;
    m_weaponComboBoxModel = new QStandardItemModel;
    m_armorComboBoxModel = new QStandardItemModel;
    m_accessoryComboBoxModel = new QStandardItemModel;
    m_attackComboBoxModel = new QStandardItemModel;
    m_magicComboBoxModel = new QStandardItemModel;
    m_summonComboBoxModel = new QStandardItemModel;
    m_itemComboBoxModel = new QStandardItemModel;
    m_allComboBoxModels = new QVector<QStandardItemModel*>;
    m_allComboBoxModels->push_back(m_charComboBoxModel);
    m_allComboBoxModels->push_back(m_enemyComboBoxModel);
    m_allComboBoxModels->push_back(m_weaponComboBoxModel);
    m_allComboBoxModels->push_back(m_armorComboBoxModel);
    m_allComboBoxModels->push_back(m_accessoryComboBoxModel);
    m_allComboBoxModels->push_back(m_attackComboBoxModel);
    m_allComboBoxModels->push_back(m_magicComboBoxModel);
    m_allComboBoxModels->push_back(m_summonComboBoxModel);
    m_allComboBoxModels->push_back(m_itemComboBoxModel);

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

    // Create storage vector for attacks, magic, summons and items
    m_attackVector = new QVector<Item*>;
    m_magicVector = new QVector<Item*>;
    m_summonVector = new QVector<Item*>;
    m_itemVector = new QVector<Item*>;

    // Create blank char/enemy/weapon/armor/etc. for combo box purpose
    m_newChar = new Character("Character");
    m_newWeapon = new Item();
    m_newArmor = new Item();
    m_newAccessory = new Item();
    m_newAttack = new Item();
    m_newMagic = new Item();
    m_newSummon = new Item();
    m_newItem = new Item();

    m_enemyVector->push_back(m_newChar);
    m_charVector->push_back(m_newChar);
    m_weaponVector->push_back(m_newWeapon);
    m_armorVector->push_back(m_newArmor);
    m_accessoryVector->push_back(m_newAccessory);
    m_attackVector->push_back(m_newAttack);
    m_magicVector->push_back(m_newMagic);
    m_summonVector->push_back(m_newSummon);
    m_itemVector->push_back(m_newItem);

    m_charComboBoxModel->appendRow(new QStandardItem(""));
    m_enemyComboBoxModel->appendRow(new QStandardItem(""));
    m_weaponComboBoxModel->appendRow(new QStandardItem(""));
    m_armorComboBoxModel->appendRow(new QStandardItem(""));
    m_accessoryComboBoxModel->appendRow(new QStandardItem(""));
    m_attackComboBoxModel->appendRow(new QStandardItem(""));
    m_magicComboBoxModel->appendRow(new QStandardItem(""));
    m_summonComboBoxModel->appendRow(new QStandardItem(""));
    m_itemComboBoxModel->appendRow(new QStandardItem(""));

    // Create storage vector for all combo boxes
    m_charComboBoxVector = new QVector<QComboBox*>;
    m_enemyComboBoxVector = new QVector<QComboBox*>;
    m_weaponComboBoxVector = new QVector<QComboBox*>;
    m_armorComboBoxVector = new QVector<QComboBox*>;
    m_accessoryComboBoxVector = new QVector<QComboBox*>;
    m_attackComboBoxVector = new QVector<QComboBox*>;
    m_magicComboBoxVector = new QVector<QComboBox*>;
    m_summonComboBoxVector = new QVector<QComboBox*>;
    m_itemComboBoxVector = new QVector<QComboBox*>;

    // For attacks, magic, summons and items, populate here combox box vectors
    m_attackComboBoxVector->push_back(ui->charAttackComboBox);
    m_attackComboBoxVector->push_back(ui->enemyAttackComboBox);

    m_magicComboBoxVector->push_back(ui->charMagicComboBox);
    m_magicComboBoxVector->push_back(ui->enemyMagicComboBox);

    m_summonComboBoxVector->push_back(ui->charSummonComboBox);

    m_itemComboBoxVector->push_back(ui->charItemComboBox);
    m_itemComboBoxVector->push_back(ui->enemyItemComboBox);

    // Create storage vector for char/enemy stat boxes and build the AllStatBox vector,
    // which contains all stat boxes
    m_charStatBoxVector = new QVector<StatBox*>;
    m_enemyStatBoxVector = new QVector<StatBox*>;
    m_allStatBoxVector = new QVector<QVector<StatBox*>*>;
    m_allStatBoxVector->push_back(m_charStatBoxVector);
    m_allStatBoxVector->push_back(m_enemyStatBoxVector);

    // Create the QMap of ailments QPushButton and store them in a vector
    m_charAilmentMap = new QMap<QString, QPushButton*>;
    m_charAilmentMap->insert("Sleep", ui->charSleepButton);
    m_charAilmentMap->insert("Poison", ui->charPoisonButton);
    m_charAilmentMap->insert("Confusion", ui->charConfusionButton);
    m_charAilmentMap->insert("Sadness", ui->charSadnessButton);
    m_charAilmentMap->insert("Fury", ui->charFuryButton);
    m_charAilmentMap->insert("Silence", ui->charSilenceButton);
    m_charAilmentMap->insert("Darkness", ui->charDarknessButton);
    m_charAilmentMap->insert("Frog", ui->charFrogButton);
    m_charAilmentMap->insert("Regen", ui->charRegenButton);
    m_charAilmentMap->insert("Haste", ui->charHasteButton);
    m_charAilmentMap->insert("Slow", ui->charSlowButton);
    m_charAilmentMap->insert("Stop", ui->charStopButton);
    m_charAilmentMap->insert("Barrier", ui->charBarrierButton);
    m_charAilmentMap->insert("MBarrier", ui->charMbarrierButton);
    m_charAilmentMap->insert("Reflect", ui->charReflectButton);

    m_enemyAilmentMap = new QMap<QString, QPushButton*>;
    m_enemyAilmentMap->insert("Sleep", ui->enemySleepButton);
    m_enemyAilmentMap->insert("Poison", ui->enemyPoisonButton);
    m_enemyAilmentMap->insert("Confusion", ui->enemyConfusionButton);
    m_enemyAilmentMap->insert("Sadness", ui->enemySadnessButton);
    m_enemyAilmentMap->insert("Fury", ui->enemyFuryButton);
    m_enemyAilmentMap->insert("Silence", ui->enemySilenceButton);
    m_enemyAilmentMap->insert("Darkness", ui->enemyDarknessButton);
    m_enemyAilmentMap->insert("Frog", ui->enemyFrogButton);
    m_enemyAilmentMap->insert("Regen", ui->enemyRegenButton);
    m_enemyAilmentMap->insert("Haste", ui->enemyHasteButton);
    m_enemyAilmentMap->insert("Slow", ui->enemySlowButton);
    m_enemyAilmentMap->insert("Stop", ui->enemyStopButton);
    m_enemyAilmentMap->insert("Barrier", ui->enemyBarrierButton);
    m_enemyAilmentMap->insert("MBarrier", ui->enemyMbarrierButton);
    m_enemyAilmentMap->insert("Reflect", ui->enemyReflectButton);

    m_ailmentMapVector = new QVector<QMap<QString, QPushButton*>*>;
    m_ailmentMapVector->push_back(m_charAilmentMap);
    m_ailmentMapVector->push_back(m_enemyAilmentMap);

}

void MainWindow::displayStatBoxes()
{
    // Display character's stat boxes
    for (int iplayer(0); iplayer < m_nPlayerStatBox; iplayer++)
    {
        m_charStatBox = new StatBox("Character", false);
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
        m_charStatBox = new StatBox("Enemy", false);
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
    for (int i(0); i < m_charComboBoxVector->size(); i++){m_charComboBoxVector->at(i)->setModel(m_charComboBoxModel);}

    // Enemies
    for (int i(0); i < m_enemyComboBoxVector->size(); i++){m_enemyComboBoxVector->at(i)->setModel(m_enemyComboBoxModel);}

    // Weapons
    for (int i(0); i < m_weaponComboBoxVector->size(); i++){m_weaponComboBoxVector->at(i)->setModel(m_weaponComboBoxModel);}

    // Armors
    for (int i(0); i < m_armorComboBoxVector->size(); i++){m_armorComboBoxVector->at(i)->setModel(m_armorComboBoxModel);}

    // Accessories
    for (int i(0); i < m_accessoryComboBoxVector->size(); i++){m_accessoryComboBoxVector->at(i)->setModel(m_accessoryComboBoxModel);}

    // Attacks
    for (int i(0); i < m_attackComboBoxVector->size(); i++){m_attackComboBoxVector->at(i)->setModel(m_attackComboBoxModel);}

    // Magic
    for (int i(0); i < m_magicComboBoxVector->size(); i++){m_magicComboBoxVector->at(i)->setModel(m_magicComboBoxModel);}

    // Summons
    for (int i(0); i < m_summonComboBoxVector->size(); i++){m_summonComboBoxVector->at(i)->setModel(m_summonComboBoxModel);}

    // Items
    for (int i(0); i < m_itemComboBoxVector->size(); i++){m_itemComboBoxVector->at(i)->setModel(m_itemComboBoxModel);}
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
    QObject::connect(m_charComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillStatBox1(QString)));
    QObject::connect(m_charComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillStatBox2(QString)));
    QObject::connect(m_charComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillStatBox3(QString)));
    QObject::connect(m_charComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillStatBox4(QString)));
    QObject::connect(m_charComboBoxVector->at(4), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillStatBox5(QString)));

    QObject::connect(m_enemyComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillEnemyStatBox1(QString)));
    QObject::connect(m_enemyComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillEnemyStatBox2(QString)));
    QObject::connect(m_enemyComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(fillEnemyStatBox3(QString)));

    QObject::connect(m_weaponComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats1()));
    QObject::connect(m_weaponComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats2()));
    QObject::connect(m_weaponComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats3()));
    QObject::connect(m_weaponComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats4()));
    QObject::connect(m_weaponComboBoxVector->at(4), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats5()));

    QObject::connect(m_armorComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats1()));
    QObject::connect(m_armorComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats2()));
    QObject::connect(m_armorComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats3()));
    QObject::connect(m_armorComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats4()));
    QObject::connect(m_armorComboBoxVector->at(4), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats5()));

    QObject::connect(m_accessoryComboBoxVector->at(0), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats1()));
    QObject::connect(m_accessoryComboBoxVector->at(1), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats2()));
    QObject::connect(m_accessoryComboBoxVector->at(2), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats3()));
    QObject::connect(m_accessoryComboBoxVector->at(3), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats4()));
    QObject::connect(m_accessoryComboBoxVector->at(4), SIGNAL(currentIndexChanged(QString)), this, SLOT(updateStats5()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP4()));
    QObject::connect(m_charStatBoxVector->at(4)->getStats()->value("HPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP5()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP4()));
    QObject::connect(m_charStatBoxVector->at(4)->getStats()->value("MPMax"), SIGNAL(textChanged(QString)), this, SLOT(checkHPMP5()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP4()));
    QObject::connect(m_charStatBoxVector->at(4)->getStats()->value("HP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP5()));

    QObject::connect(m_charStatBoxVector->at(0)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP1()));
    QObject::connect(m_charStatBoxVector->at(1)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP2()));
    QObject::connect(m_charStatBoxVector->at(2)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP3()));
    QObject::connect(m_charStatBoxVector->at(3)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP4()));
    QObject::connect(m_charStatBoxVector->at(4)->getStats()->value("MP"), SIGNAL(textChanged(QString)), this, SLOT(setCurrentHPMP5()));

    QMap<QString, QPushButton*>::const_iterator it = m_charAilmentMap->constBegin();
    while (it != m_charAilmentMap->constEnd())
    {
        QObject::connect(it.value(), SIGNAL(clicked()), this, SLOT(toggleCharAilment()));
        it++;
    }

    QMap<QString, QPushButton*>::const_iterator it2 = m_enemyAilmentMap->constBegin();
    while (it2 != m_enemyAilmentMap->constEnd())
    {
        QObject::connect(it2.value(), SIGNAL(clicked()), this, SLOT(toggleEnemyAilment()));
        it2++;
    }

}

void MainWindow::on_addCharButton_clicked(){newDialog("Character");}
void MainWindow::on_addWeaponButton_clicked(){newDialog("Weapon");}
void MainWindow::on_addArmorButton_clicked(){newDialog("Armor");}
void MainWindow::on_addAccessoryButton_clicked(){newDialog("Accessory");}
void MainWindow::on_addEnemyButton_clicked(){newDialog("Enemy");}
void MainWindow::on_addAttackButton_clicked(){newDialog("Attack");}
void MainWindow::on_addMagicButton_clicked(){newDialog("Magic");}
void MainWindow::on_addSummonButton_clicked(){newDialog("Summon");}
void MainWindow::on_addItemButton_clicked(){newDialog("Item");}

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

void MainWindow::on_charAttackComboBox_currentIndexChanged(QString attackName){computeDamage("Character", "Attack", attackName);}
void MainWindow::on_charMagicComboBox_currentIndexChanged(QString attackName){computeDamage("Character", "Magic", attackName);}
void MainWindow::on_charSummonComboBox_currentIndexChanged(QString attackName){computeDamage("Character", "Summon", attackName);}
void MainWindow::on_enemyAttackComboBox_currentIndexChanged(QString attackName){computeDamage("Enemy", "Attack", attackName);}
void MainWindow::on_enemyMagicComboBox_currentIndexChanged(QString attackName){computeDamage("Enemy", "Magic", attackName);}
void MainWindow::on_charListView_clicked(QModelIndex index){updateInfo("Character", index);}
void MainWindow::on_enemyListView_clicked(QModelIndex index){updateInfo("Enemy", index);}

void MainWindow::on_charAttackButton_clicked()
{
    // Get enemy index
    QModelIndex index = ui->enemyListView->currentIndex();
    int enemyIndex = index.row();

    // Get char damage
    int charDamage = ui->charAttDmgEdit->displayText().toInt();

    // Apply damage
    int enemyHP = m_enemyStatBoxVector->at(enemyIndex)->getStats()->value("HP")->displayText().toInt();
    enemyHP = enemyHP - charDamage;
    m_enemyStatBoxVector->at(enemyIndex)->getStats()->value("HP")->setText(QString::number(enemyHP));

    // Update enemy HP
    QString enemyName = index.data(Qt::DisplayRole).toString();
    for (int iEnemy(0); iEnemy < m_enemyVector->size(); iEnemy++)
    {
        if (m_enemyVector->at(iEnemy)->getStats()->value("Name") == enemyName)
        {
            m_enemyVector->at(iEnemy)->setStat("HP", QString::number(enemyHP));
        }
    }
}
void MainWindow::on_magicButton_clicked()
{
    // Get enemy index
    QModelIndex index = ui->enemyListView->currentIndex();
    int enemyIndex = index.row();

    // Get char damage
    int charDamage = ui->charMagDmgEdit->displayText().toInt();

    // Apply damage
    int enemyHP = m_enemyStatBoxVector->at(enemyIndex)->getStats()->value("HP")->displayText().toInt();
    enemyHP = enemyHP - charDamage;
    m_enemyStatBoxVector->at(enemyIndex)->getStats()->value("HP")->setText(QString::number(enemyHP));

    // Update enemy HP
    QString enemyName = index.data(Qt::DisplayRole).toString();
    for (int iEnemy(0); iEnemy < m_enemyVector->size(); iEnemy++)
    {
        if (m_enemyVector->at(iEnemy)->getStats()->value("Name") == enemyName)
        {
            m_enemyVector->at(iEnemy)->setStat("HP", QString::number(enemyHP));
        }
    }
}
void MainWindow::on_summonButton_clicked()
{
    // Get enemy index
    QModelIndex index = ui->enemyListView->currentIndex();
    int enemyIndex = index.row();

    // Get char damage
    int charDamage = ui->charSumDmgEdit->displayText().toInt();

    // Apply damage
    int enemyHP = m_enemyStatBoxVector->at(enemyIndex)->getStats()->value("HP")->displayText().toInt();
    enemyHP = enemyHP - charDamage;
    m_enemyStatBoxVector->at(enemyIndex)->getStats()->value("HP")->setText(QString::number(enemyHP));

    // Update enemy HP
    QString enemyName = index.data(Qt::DisplayRole).toString();
    for (int iEnemy(0); iEnemy < m_enemyVector->size(); iEnemy++)
    {
        if (m_enemyVector->at(iEnemy)->getStats()->value("Name") == enemyName)
        {
            m_enemyVector->at(iEnemy)->setStat("HP", QString::number(enemyHP));
        }
    }
}
void MainWindow::on_enemyAttackButton_clicked()
{
    // Get char index
    QModelIndex index = ui->charListView->currentIndex();
    int charIndex = index.row();

    // Get enemy damage
    int enemyDamage = ui->enemyAttDmgEdit->displayText().toInt();

    // Apply damage and update enemy HP
    int charHP = m_charStatBoxVector->at(charIndex)->getStats()->value("HP")->displayText().toInt();
    charHP = charHP - enemyDamage;

    QString charName = index.data(Qt::DisplayRole).toString();
    for (int iChar(0); iChar< m_charVector->size(); iChar++)
    {
        if (m_charVector->at(iChar)->getStats()->value("Name") == charName)
        {
            m_charVector->at(iChar)->setStat("HP", QString::number(charHP));
        }
    }

    // Display new HP
    m_charStatBoxVector->at(charIndex)->getStats()->value("HP")->setText(QString::number(charHP));

}
void MainWindow::on_enemyMagicButton_clicked()
{
    // Get char index
    QModelIndex index = ui->charListView->currentIndex();
    int charIndex = index.row();

    // Get enemy damage
    int enemyDamage = ui->enemyMagDmgEdit->displayText().toInt();

    // Apply damage
    int charHP = m_charStatBoxVector->at(charIndex)->getStats()->value("HP")->displayText().toInt();
    charHP = charHP - enemyDamage;
    m_charStatBoxVector->at(charIndex)->getStats()->value("HP")->setText(QString::number(charHP));

    // Update enemy HP
    QString charName = index.data(Qt::DisplayRole).toString();
    for (int iChar(0); iChar< m_charVector->size(); iChar++)
    {
        if (m_charVector->at(iChar)->getStats()->value("Name") == charName)
        {
            m_charVector->at(iChar)->setStat("HP", QString::number(charHP));
        }
    }
}

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

    QString name = m_addCharDialog->getStatBox()->getStats()->value("Name")->displayText();

    if (dialogReturn == QDialog::Accepted && !name.isEmpty())
    {
        // Gather all character's stats
        QString level             = m_addCharDialog->getStatBox()->getStats()->value("Level")->displayText();
        QString hp                = m_addCharDialog->getStatBox()->getStats()->value("HPMax")->displayText();
        QString mp                = m_addCharDialog->getStatBox()->getStats()->value("MPMax")->displayText();
        QString hpMax             = m_addCharDialog->getStatBox()->getStats()->value("HPMax")->displayText();
        QString mpMax             = m_addCharDialog->getStatBox()->getStats()->value("MPMax")->displayText();
        QString strength          = m_addCharDialog->getStatBox()->getStats()->value("Strength")->displayText();
        QString vitality          = m_addCharDialog->getStatBox()->getStats()->value("Vitality")->displayText();
        QString magic             = m_addCharDialog->getStatBox()->getStats()->value("Magic")->displayText();
        QString spirit            = m_addCharDialog->getStatBox()->getStats()->value("Spirit")->displayText();
        QString dexterity         = m_addCharDialog->getStatBox()->getStats()->value("Dexterity")->displayText();
        QString luck              = m_addCharDialog->getStatBox()->getStats()->value("Luck")->displayText();
        QString attack            = m_addCharDialog->getStatBox()->getStats()->value("Attack")->displayText();
        QString attackPercent     = m_addCharDialog->getStatBox()->getStats()->value("AttackPercent")->displayText();
        QString magAttack         = m_addCharDialog->getStatBox()->getStats()->value("MagAttack")->displayText();
        QString magAttackPercent  = m_addCharDialog->getStatBox()->getStats()->value("MagAttackPercent")->displayText();
        QString critHitPercent    = m_addCharDialog->getStatBox()->getStats()->value("CritHitPercent")->displayText();
        QString defense           = m_addCharDialog->getStatBox()->getStats()->value("Defense")->displayText();
        QString magDefense        = m_addCharDialog->getStatBox()->getStats()->value("MagDefense")->displayText();
        QString defensePercent    = m_addCharDialog->getStatBox()->getStats()->value("DefensePercent")->displayText();
        QString magDefPercent     = m_addCharDialog->getStatBox()->getStats()->value("MagDefPercent")->displayText();
        QString weapon            = "None";
        QString armor             = "None";
        QString accessory         = "None";

        // For attacks, magic, summons and items
        QString factor            = m_addCharDialog->getStatBox()->getStats()->value("Factor")->displayText();
        QString mpCost            = m_addCharDialog->getStatBox()->getStats()->value("MPCost")->displayText();

        // Status ailments for characters
        bool poison(false), sadness(false), fury(false), silence(false), darkness(false), frog(false);

        createNew(newType, name, level, hp, mp, hpMax, mpMax, strength, vitality, magic, spirit, dexterity, luck,
                  attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                  defense, defensePercent, magDefense, magDefPercent, weapon, armor, accessory,
                  factor, mpCost, poison, sadness, fury, silence, darkness, frog);
    }
}

void MainWindow::createNew(QString newType, QString name, QString level, QString hp, QString mp, QString hpMax, QString mpMax, QString strength, QString vitality, QString magic,
                           QString spirit, QString dexterity, QString luck, QString attack, QString attackPercent, QString magAttack,
                           QString magAttackPercent, QString critHitPercent, QString defense, QString defensePercent, QString magDefense, QString magDefPercent,
                           QString weapon, QString armor, QString accessory, QString factor, QString mpCost, bool poison, bool sadness, bool fury,
                           bool silence, bool darkness, bool frog)
{
    if (newType == "Character" || newType == "Enemy")
    {
        m_newChar = new Character(newType, name, level, hp, mp, hpMax, mpMax, strength, vitality, magic, spirit, dexterity, luck,
                                  attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                                  defense, defensePercent, magDefense, magDefPercent, weapon, armor, accessory,
                                  poison, sadness, fury, silence, darkness, frog);

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
    else if (newType == "Accessory")
    {
        m_newAccessory = new Item(name, magic, strength, hpMax, mpMax, vitality, dexterity, luck, spirit);

        // Store the armor
        m_accessoryVector->push_back(m_newAccessory);

        // Populate the model for armor combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_accessoryComboBoxModel->appendRow(item);
    }
    else if(newType == "Attack")
    {
        m_newAttack = new Item(name, factor);

        // Store the attack
        m_attackVector->push_back(m_newAttack);

        // Populate the model for attack combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_attackComboBoxModel->appendRow(item);
    }
    else if (newType == "Magic" || newType == "Summon")
    {
        m_newMagic = new Item(name, magAttackPercent, factor, mpCost);

        if (newType == "Magic")
        {
            // Store the magic
            m_magicVector->push_back(m_newMagic);

            // Populate the model for magic combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_magicComboBoxModel->appendRow(item);
        }
        else
        {
            // Store the summon
            m_summonVector->push_back(m_newMagic);

            // Populate the model for summon combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_summonComboBoxModel->appendRow(item);
        }
    }
    else if (newType == "Item")
    {
        m_newItem = new Item(name);

        // Store the item
        m_itemVector->push_back(m_newItem);

        // Populate the model for magic combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_itemComboBoxModel->appendRow(item);
    }

    // Sort all Combo Box Models
    for (int iModel(0); iModel < m_allComboBoxModels->size(); iModel++){m_allComboBoxModels->at(iModel)->sort(0, Qt::AscendingOrder);}
}

void MainWindow::fillStatBox1(QString charName){fillStatBox(0, "Character", charName);}
void MainWindow::fillStatBox2(QString charName){fillStatBox(1, "Character", charName);}
void MainWindow::fillStatBox3(QString charName){fillStatBox(2, "Character", charName);}
void MainWindow::fillStatBox4(QString charName){fillStatBox(3, "Character", charName);}
void MainWindow::fillStatBox5(QString charName){fillStatBox(4, "Character", charName);}

void MainWindow::fillEnemyStatBox1(QString enemyName){fillStatBox(0, "Enemy", enemyName);}
void MainWindow::fillEnemyStatBox2(QString enemyName){fillStatBox(1, "Enemy", enemyName);}
void MainWindow::fillEnemyStatBox3(QString enemyName){fillStatBox(2, "Enemy", enemyName);}

void MainWindow::updateStats1(){updateStats(0);}
void MainWindow::updateStats2(){updateStats(1);}
void MainWindow::updateStats3(){updateStats(2);}
void MainWindow::updateStats4(){updateStats(3);}
void MainWindow::updateStats5(){updateStats(4);}

void MainWindow::checkHPMP1(){checkHPMP(0);}
void MainWindow::checkHPMP2(){checkHPMP(1);}
void MainWindow::checkHPMP3(){checkHPMP(2);}
void MainWindow::checkHPMP4(){checkHPMP(3);}
void MainWindow::checkHPMP5(){checkHPMP(4);}

void MainWindow::setCurrentHPMP1(){setCurrentHPMP(0);}
void MainWindow::setCurrentHPMP2(){setCurrentHPMP(1);}
void MainWindow::setCurrentHPMP3(){setCurrentHPMP(2);}
void MainWindow::setCurrentHPMP4(){setCurrentHPMP(3);}
void MainWindow::setCurrentHPMP5(){setCurrentHPMP(4);}

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
    if (hpDisplay.toInt() < 1)
    {
        m_charStatBoxVector->at(i)->getStats()->value("HP")->setText("0");
    }

    if (mpDisplay.toInt() > mpMaxDisplay.toInt())
    {
        m_charStatBoxVector->at(i)->getStats()->value("MP")->setText(mpMaxDisplay);
    }
    if (mpDisplay.toInt() < 1)
    {
        m_charStatBoxVector->at(i)->getStats()->value("MP")->setText("0");
    }
}

void MainWindow::setCurrentHPMP(int i)
{
    // Check new value of HP and/or MP
    checkHPMP(i);

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
    QString charAttack, charAttackPercent, charMagAttack, charMagAttackPercent, charMagic, charCritHitPercent, charStrength;
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
            charMagAttack = m_charVector->at(iChar)->getStats()->value("MagAttack");
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

    charAttack = QString::number(charStrength.toInt() + weaponAttack.toInt());
    charAttackPercent = QString::number(charAttackPercent.toInt() + weaponAttackPercent.toInt());
    charCritHitPercent = QString::number(charCritHitPercent.toInt() + weaponCritHitPercent.toInt());

    charMagAttack = QString::number(charMagic.toInt()) ;
    //charMagAttackPercent = QString::number();

    charDefense = QString::number(charVitality.toInt() + armorDefense.toInt());
    charDefensePercent = QString::number(charDexterity.toInt()/4 + armorDefensePercent.toInt());

    charMagDefense = QString::number(charSpirit.toInt() + armorMagDefense.toInt());
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
    m_charStatBoxVector->at(i)->getStats()->value("MagAttack")->setText(charMagAttack);
    m_charStatBoxVector->at(i)->getStats()->value("MagDefense")->setText(charMagDefense);
    m_charStatBoxVector->at(i)->getStats()->value("MagDefPercent")->setText(charMagDefPercent);
}

void MainWindow::writeToFile()
{
    // Create output text stream
    QTextStream write(m_saveFile);

    // Write Table name
    write << "Table Name: " << m_tableName << "\n";

    // Write number of characters, enemies, weapons, armors and accessories, etc.
    // Note the -1 because there's always a dummy item for combo box purpose
    m_nChar = QString::number(m_allCharVector->at(0)->size()-1);
    m_nEnemies = QString::number(m_allCharVector->at(1)->size()-1);
    m_nWeapons = QString::number(m_weaponVector->size()-1);
    m_nArmors = QString::number(m_armorVector->size()-1);
    m_nAccessories = QString::number(m_accessoryVector->size()-1);
    m_nAttacks = QString::number(m_attackVector->size()-1);
    m_nMagic = QString::number(m_magicVector->size()-1);
    m_nSummons = QString::number(m_summonVector->size()-1);
    m_nItems = QString::number(m_itemVector->size()-1);

    write << "Characters: " << m_nChar << " | Enemies: " << m_nEnemies <<
             " | Weapons: " << m_nWeapons << " | Armors: " << m_nArmors <<
             " | Accessories: " << m_nAccessories << " | Attacks: " << m_nAttacks <<
             " | Magic: " << m_nMagic << " | Summons: " << m_nSummons <<
             " | Items: " << m_nItems << "\n";

    /* Big fat loop to write all stats from characters, enemies, items, etc.
     * Type 1: characters
     * Type 2: enemies
     * Type 3: weapons
     * Type 4: armors
     * Type 5: accessories
     * Type 6: attacks
     * Type 7: magic
     * Type 8: summons
     * Type 9: items */
    for (int iType(0); iType < 9; iType++)
    {
        int nMax(0);
        QMap<QString, QString> *charStat = new QMap<QString, QString>;
        QVector<Character*> *charVector = new QVector<Character*>;
        QVector<Item*> *itemVector = new QVector<Item*>;

        if (iType == 0){write << "========= CHARACTERS =========\n"; nMax = m_charVector->size(); charVector = m_charVector;}
        else if (iType == 1){write << "========= BESTIARY =========\n"; nMax = m_enemyVector->size(); charVector = m_enemyVector;}
        else if (iType == 2){write << "========= WEAPONS =========\n"; nMax = m_weaponVector->size(); itemVector = m_weaponVector;}
        else if (iType == 3){write << "========= ARMORS =========\n"; nMax = m_armorVector->size(); itemVector = m_armorVector;}
        else if (iType == 4){write << "========= ACCESSORIES =========\n"; nMax = m_accessoryVector->size(); itemVector = m_accessoryVector;}
        else if (iType == 5){write << "========= ATTACKS =========\n"; nMax = m_attackVector->size(); itemVector = m_attackVector;}
        else if (iType == 6){write << "========= MAGIC =========\n"; nMax = m_magicVector->size(); itemVector = m_magicVector;}
        else if (iType == 7){write << "========= SUMMONS =========\n"; nMax = m_summonVector->size(); itemVector = m_summonVector;}
        else if (iType == 8){write << "========= ITEMS =========\n"; nMax = m_itemVector->size(); itemVector = m_itemVector;}

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
                else if (iType == 4){write << "Accessory " << i << ":\n";}
                else if (iType == 5){write << "Attack " << i << ":\n";}
                else if (iType == 6){write << "Magic " << i << ":\n";}
                else if (iType == 7){write << "Summon " << i << ":\n";}
                else if (iType == 8){write << "Item " << i << ":\n";}

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

                // If char, also navigate through the ailment QMap
                if (iType == 0 || iType == 1)
                {
                    QMap<QString, bool>::const_iterator it = charVector->at(i)->getAilments()->constBegin();
                    while (it != charVector->at(i)->getAilments()->constEnd())
                    {
                        write << it.key() << ": " << it.value() << " | ";
                        it++;
                    }
                    write << "\n";
                }
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

    // Get number of characters, enemies, weapons, accessories, etc.
    QStringList lineList = read.readLine().split(" | ");
    m_nChar = lineList[0].split(": ")[1];
    m_nEnemies = lineList[1].split(": ")[1];
    m_nWeapons = lineList[2].split(": ")[1];
    m_nArmors = lineList[3].split(": ")[1];
    m_nAccessories = lineList[4].split(": ")[1];
    m_nAttacks = lineList[5].split(": ")[1];
    m_nMagic = lineList[6].split(": ")[1];
    m_nSummons = lineList[7].split(": ")[1];
    m_nItems = lineList[8].split(": ")[1];

    /* Big fat loop to get all stats from characters, enemies, and items.
     * Type 1: characters
     * Type 2: enemies
     * Type 3: weapons
     * Type 4: armors
     * Type 5: accessories
     * Type 6: attacks
     * Type 7: magic
     * Type 8: summons
     * Type 9: items */
    for (int iType(0); iType < 9; iType++)
    {
        int nMax(0);
        QString type;

        read.readLine();
        if (iType == 0){nMax = m_nChar.toInt(); type = "Character";}
        else if (iType == 1){nMax = m_nEnemies.toInt(); type = "Enemy";}
        else if (iType == 2){nMax = m_nWeapons.toInt(); type = "Weapon";}
        else if (iType == 3){nMax = m_nArmors.toInt(); type = "Armor";}
        else if (iType == 4){nMax = m_nAccessories.toInt(); type = "Accessory";}
        else if (iType == 5){nMax = m_nAttacks.toInt(); type = "Attack";}
        else if (iType == 6){nMax = m_nMagic.toInt(); type = "Magic";}
        else if (iType == 7){nMax = m_nSummons.toInt(); type = "Summon";}
        else if (iType == 8){nMax = m_nItems.toInt(); type = "Item";}

        for (int i(0); i < nMax; i++)
        {
            read.readLine();
            QStringList statList = read.readLine().split(" | ", QString::SkipEmptyParts);

            // Create the stat bundle
            QMap<QString, QString> *statBundle = new QMap<QString, QString>;

            // Navigate through the stat list and populate the bundle
            for (int iElement(0); iElement < statList.size(); iElement++)
            {
                QStringList statPair = statList.at(iElement).split(": ");
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
            QString luck              = statBundle->value("Luck");
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
            QString factor            = statBundle->value("Factor");
            QString mpCost            = statBundle->value("MPCost");

            // for characters only
            bool poison(false), sadness(false), fury(false), silence(false), darkness(false), frog(false);

            if (iType == 0 || iType == 1)
            {
                QStringList ailmentList = read.readLine().split(" | ", QString::SkipEmptyParts);

                // Create the stat bundle
                QMap<QString, QString> *ailmentBundle = new QMap<QString, QString>;

                // Navigate through the ailment list and populate the bundle
                for (int iElement(0); iElement < ailmentList.size(); iElement++)
                {
                    QStringList ailmentPair = ailmentList.at(iElement).split(": ");
                    ailmentBundle->insert(ailmentPair[0],ailmentPair[1]);
                }

                // Gather all character's stats
                poison               = (ailmentBundle->value("Poison") == "1" ? true : false);
                sadness              = (ailmentBundle->value("Sadness") == "1" ? true : false);
                fury                 = (ailmentBundle->value("Fury") == "1" ? true : false);
                silence              = (ailmentBundle->value("Silence") == "1" ? true : false);
                darkness             = (ailmentBundle->value("Darkness") == "1" ? true : false);
                frog                 = (ailmentBundle->value("Frog") == "1" ? true : false);
            }

            // Create character/enemy
            createNew(type, name, level, hp, mp, hpMax, mpMax, strength, vitality, magic, spirit, dexterity, luck,
                      attack, attackPercent, magAttack, magAttackPercent, critHitPercent,
                      defense, defensePercent, magDefense, magDefPercent, weapon, armor, accessory, factor, mpCost,
                      poison, sadness, fury, silence, darkness, frog);
        }
    }
}

void MainWindow::toggleCharAilment()
{
    QObject *sendingButton = sender();

    // Navigate through char QMap and find the sender
    QMap<QString, QPushButton*>::const_iterator it = m_charAilmentMap->constBegin();
    while (it != m_charAilmentMap->constEnd())
    {
        if(sendingButton == it.value()){toggleAilment("Character", it.key());}
        it++;
    }
}

void MainWindow::toggleEnemyAilment()
{
    QObject *sendingButton = sender();

    // Navigate through enemy QMap and find the sender
    QMap<QString, QPushButton*>::const_iterator it = m_enemyAilmentMap->constBegin();
    while (it != m_enemyAilmentMap->constEnd())
    {
        if(sendingButton == it.value()){toggleAilment("Enemy", it.key());}
        it++;
    }
}

void MainWindow::toggleAilment(QString charType, QString ailment)
{
    // Set storage vector and list view depending on char type
    QVector<Character*> *vector = new QVector<Character*>;
    QListView *listView = new QListView;

    if (charType == "Character"){vector = m_charVector; listView = ui->charListView;}
    else{vector = m_enemyVector; listView = ui->enemyListView;}

    // Get character's name
    QModelIndex index = listView->currentIndex();
    QString name = index.data().toString();

    // Look for character and toggle sleep value
    for (int iChar(0); iChar < vector->size(); iChar++)
    {
        if (vector->at(iChar)->getStats()->value("Name") == name)
        {
            vector->at(iChar)->setAilment(ailment, !vector->at(iChar)->getAilments()->value(ailment));
        }
    }
}

void MainWindow::updateInfo(QString charType, QModelIndex index)
{
    // Get character and enemy attack, magic, and summon if any
    QString charCurrentAttack = ui->charAttackComboBox->currentText();
    QString charCurrentMagic = ui->charMagicComboBox->currentText();
    QString charCurrentSummon = ui->charSummonComboBox->currentText();
    QString enemyCurrentAttack = ui->enemyAttackComboBox->currentText();
    QString enemyCurrentMagic = ui->enemyMagicComboBox->currentText();

    // Update ailments
    updateAilments(charType, index);

    // Update damage
    computeDamage("Character", "Attack", charCurrentAttack);
    computeDamage("Character", "Magic", charCurrentMagic);
    computeDamage("Character", "Summon", charCurrentSummon);
    computeDamage("Enemy", "Attack", enemyCurrentAttack);
    computeDamage("Enemy", "Magic", enemyCurrentMagic);
}

void MainWindow::updateAilments(QString charType, QModelIndex index)
{
    QString name = index.data(Qt::DisplayRole).toString();

    QVector<Character*> *vector = new QVector<Character*>;
    QMap<QString, QPushButton*> *qMap = new QMap<QString, QPushButton*>;

    if (charType == "Character"){vector = m_charVector; qMap = m_charAilmentMap;}
    else {vector = m_enemyVector; qMap = m_enemyAilmentMap;}

    for (int iChar(0); iChar < vector->size(); iChar++)
    {
        if (vector->at(iChar)->getStats()->value("Name") == name)
        {
            // Loop over ailments and activate button if true
            QMap<QString, bool>::const_iterator it = vector->at(iChar)->getAilments()->constBegin();
            while (it != vector->at(iChar)->getAilments()->constEnd())
            {
                // Set button
                qMap->value(it.key())->setChecked(it.value());
                it++;
            }
        }
    }
}

void MainWindow::computeDamage(QString charType, QString attackType, QString attackName)
{
    // Debug
    //std::cout << "Character Type: " << charType.toStdString() << " | Attack Type: " << attackType.toStdString() << " | Attack Name: " << attackName.toStdString() << std::endl;

    // Initialisations
    double attackFactor(0), magicFactor(0), level(0), targetLevel(0), attack(0), magAttack(0), attackDamage(0), magicDamage(0), chance(0), critHitPercent(0);
    double defense(0), magicDefense(0), dexterity(0), attackPercent(0), defensePercent(0), targetDefPercent(0), precision(0), magAttPercent(0);
    QString attackerLevel, attackerAttack, attackerMagAttack;
    QString targetDefense, targetMagDefense;
    QString magAttackPercent;

    // Debug
    //std::cout << "(1) Attack Damage: " << attackDamage << " | Magic Damage: " << magicDamage << std::endl;

    /* ===================================
     * =========== BASE DAMAGE ===========
     * ===================================*/

    // Initialise a few things
    QListView *attackerListView = new QListView;
    QListView *targetListView = new QListView;

    QVector<StatBox*> *attackerVector = new QVector<StatBox*>;
    QVector<StatBox*> *targetVector = new QVector<StatBox*>;

    QMap<QString, QPushButton*> *attackerAilmentMap = new QMap<QString, QPushButton*>;
    QMap<QString, QPushButton*> *targetAilmentMap = new QMap<QString, QPushButton*>;

    if (charType == "Character")
    {
        attackerListView = ui->charListView;
        targetListView = ui->enemyListView;

        attackerVector = m_charStatBoxVector;
        targetVector = m_enemyStatBoxVector;

        attackerAilmentMap = m_charAilmentMap;
        targetAilmentMap = m_enemyAilmentMap;
    }
    else
    {
        attackerListView = ui->enemyListView;
        targetListView = ui->charListView;

        attackerVector = m_enemyStatBoxVector;
        targetVector = m_charStatBoxVector;

        attackerAilmentMap = m_enemyAilmentMap;
        targetAilmentMap = m_charAilmentMap;
    }

    // Get attacker level, attack, and magic
    QModelIndex index = attackerListView->currentIndex();
    int attackerIndex = index.row();
    if (attackerIndex != -1){
        attackerLevel = attackerVector->at(attackerIndex)->getStats()->value("Level")->displayText();
        attackerAttack = attackerVector->at(attackerIndex)->getStats()->value("Attack")->displayText();
        attackerMagAttack = attackerVector->at(attackerIndex)->getStats()->value("MagAttack")->displayText();
    }
    level = attackerLevel.toDouble();
    attack = attackerAttack.toDouble();
    magAttack = attackerMagAttack.toDouble();

    // Attack Damage = attack+[(attack*level)(attack+level]/1024
    attackDamage = attackDamage + (attack+((attack*level)*(attack+level))/1024);

    // Magic Damage = 6*(magic+level)
    magicDamage = magAttack + (6*(magAttack+level));

    // Debug
    //std::cout << "(2) Attack Damage: " << attackDamage << " | Magic Damage: " << magicDamage << std::endl;

    /* ===================================
     * =========== APPLY FACTOR ==========
     * ===================================*/

    // Get attack factor
    for (int iAttack(0); iAttack < m_attackVector->size(); iAttack++)
    {
        if (m_attackVector->at(iAttack)->getStats()->value("Name") == attackName)
        {
            attackFactor = m_attackVector->at(iAttack)->getStats()->value("Factor").toDouble();
        }
    }

    // Get magic factor
    QVector<Item*> *vector = new QVector<Item*>;
    // Define the correct storage vector depending on Magic/Summon
    if (attackType == "Magic"){vector = m_magicVector;}
    else if (attackType == "Summon"){vector = m_summonVector;}

    // Get magic factor
    for (int iMagic(0); iMagic < vector->size(); iMagic++)
    {
        if (vector->at(iMagic)->getStats()->value("Name") == attackName)
        {
            magicFactor = vector->at(iMagic)->getStats()->value("Factor").toDouble();

            // Two birds, one stone: get MagAttPercent and display the value in the stat box
            if (attackerIndex != -1)
            {
                magAttackPercent = vector->at(iMagic)->getStats()->value("MagAttackPercent");
                attackerVector->at(attackerIndex)->getStats()->value("MagAttackPercent")->setText(magAttackPercent);
            }
        }
    }

    attackDamage = attackDamage*attackFactor;
    magicDamage = magicDamage*magicFactor;

    // Debug
    //std::cout << "(3) Attack Damage: " << attackDamage << " | Magic Damage: " << magicDamage << std::endl;

    /* ===================================
     * ========== APPLY DEFENSE ==========
     * ===================================*/

    // Get target attack, and magic
    QModelIndex index2 = targetListView->currentIndex();
    int targetIndex = index2.row();
    if (targetIndex != -1){
        targetDefense = targetVector->at(targetIndex)->getStats()->value("Defense")->displayText();
        targetMagDefense = targetVector->at(targetIndex)->getStats()->value("MagDefense")->displayText();
    }
    defense = targetDefense.toDouble();
    magicDefense = targetMagDefense.toDouble();

    attackDamage = attackDamage*(512-defense)/512.0;
    magicDamage = magicDamage*(512-magicDefense)/512.0;

    // Debug
    //std::cout << "(4) Attack Damage: " << attackDamage << " | Magic Damage: " << magicDamage << std::endl;

    /* ===================================
     * ========= APPLY AILMENTS ==========
     * ===================================*/

    if (attackerAilmentMap->value("Frog")->isChecked()){attackDamage = attackDamage/4.0;}
    if (attackerAilmentMap->value("Sadness")->isChecked()){attackDamage = 7.0/10.0*attackDamage; magicDamage = 7.0/10.0*magicDamage;}
    if (targetAilmentMap->value("Barrier")->isChecked()){attackDamage = 0.5*attackDamage;}
    if (targetAilmentMap->value("MBarrier")->isChecked()){magicDamage = 0.5*magicDamage;}

    // Debug
    //std::cout << "(5) Attack Damage: " << attackDamage << " | Magic Damage: " << magicDamage << std::endl;

    /* ===================================
     * ======== COMPUTE PRECISION ========
     * ===================================*/

    QLineEdit *attPrecEdit = new QLineEdit;
    QLineEdit *magPrecEdit = new QLineEdit;

    if (charType == "Character"){attPrecEdit = ui->charAttPrecEdit; magPrecEdit = ui->charMagPrecEdit;}
    else {attPrecEdit = ui->enemyAttPrecEdit; magPrecEdit = ui->enemyMagPrecEdit;}

    if (attackType == "Attack")
    {
        // precision = dexterity/4 + att% + def% attacker - def% target
        if (attackerIndex != -1 && targetIndex != -1)
        {
            dexterity = attackerVector->at(attackerIndex)->getStats()->value("Dexterity")->displayText().toDouble();

            attackPercent = attackerVector->at(attackerIndex)->getStats()->value("AttackPercent")->displayText().toDouble();
            if (attackerAilmentMap->value("Darkness")->isChecked()){attackPercent = attackPercent/2.0;}

            defensePercent = attackerVector->at(attackerIndex)->getStats()->value("DefensePercent")->displayText().toDouble();

            targetDefPercent = targetVector->at(targetIndex)->getStats()->value("DefensePercent")->displayText().toDouble();

            precision = dexterity/4. + attackPercent + defensePercent - targetDefPercent;
            if (attackerAilmentMap->value("Fury")->isChecked()){precision = precision*0.7;}

            // Final check and display
            if (precision < 0){precision = 0;}
            attPrecEdit->setText(QString::number(qFloor(precision)));
        }
    }
    else if (attackType == "Magic" || attackType == "Summon")
    {
        // precision = mag attack % + level - (target level/2) - 1
        if (attackerIndex != -1 && targetIndex != -1)
        {
            magAttPercent = magAttackPercent.toDouble();
            targetLevel = targetVector->at(targetIndex)->getStats()->value("Level")->displayText().toDouble();

            if (attackerAilmentMap->value("Fury")->isChecked()){magAttPercent = magAttPercent*0.7;}

            precision = magAttPercent + level - (targetLevel/2.) - 1;

            // Final check and display
            if (precision < 0){precision = 0;}
            if (attackType == "Magic"){magPrecEdit->setText(QString::number(qFloor(precision)));}
            else {ui->charSumPrecEdit->setText(QString::number(qFloor(precision)));}
        }
    }

    /* ===================================
     * ======== COMPUTE CRIT. HIT ========
     * ===================================*/

    QLineEdit *attCritEdit = new QLineEdit;
    if (charType == "Character"){attCritEdit = ui->charCritEdit;}
    else {attCritEdit = ui->enemyCritEdit;}

    if (attackType == "Attack")
    {
        // crit. hit% = (chance/4 + Delta level)/4
        if (attackerIndex != -1 && targetIndex != -1)
        {
            chance = attackerVector->at(attackerIndex)->getStats()->value("Luck")->displayText().toDouble();
            targetLevel = targetVector->at(targetIndex)->getStats()->value("Level")->displayText().toDouble();

            critHitPercent = (chance/4. + level - targetLevel)/4.;

            // Add bonus due to weapon
            if (charType == "Character")
            {
                QString weaponName = attackerVector->at(attackerIndex)->getWeaponComboBox()->currentText();
                for (int iWeapon(0); iWeapon < m_weaponVector->size(); iWeapon++)
                {
                    if (m_weaponVector->at(iWeapon)->getStats()->value("Name") == weaponName)
                    {
                        critHitPercent = critHitPercent + m_weaponVector->at(iWeapon)->getStats()->value("CritHitPercent").toDouble();
                    }
                }
            }

            // Display
            if (critHitPercent < 0){critHitPercent = 0;}
            attCritEdit->setText(QString::number(qFloor(critHitPercent)));
        }
    }

    /* ===================================
     * ========= DISPLAY DAMAGE ==========
     * ===================================*/
    QLineEdit *attackEdit = new QLineEdit;
    QLineEdit *magicEdit = new QLineEdit;
    QLineEdit *summonEdit = new QLineEdit;

    if (charType == "Character"){attackEdit = ui->charAttDmgEdit; magicEdit = ui->charMagDmgEdit; summonEdit = ui->charSumDmgEdit;}
    else {attackEdit = ui->enemyAttDmgEdit; magicEdit = ui->enemyMagDmgEdit;}

    if (attackType == "Attack"){attackEdit->setText(QString::number(qFloor(attackDamage)));}
    else if (attackType == "Magic"){magicEdit->setText(QString::number(qFloor(magicDamage)));;}
    else if (attackType == "Summon") {summonEdit->setText(QString::number(qFloor(magicDamage)));}
}

