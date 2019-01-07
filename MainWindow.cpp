#include "MainWindow.h"
#include "AddCharDialog.h"
#include "Character.h"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create models for char/enemy name combo boxes
    m_charComboBoxModel = new QStandardItemModel;
    m_enemyComboBoxModel = new QStandardItemModel;

    // Create storage vector for char/enemy and build the AllChar vector,
    // which stores all characters
    m_charVector = new QVector<Character*>;
    m_enemyVector = new QVector<Character*>;
    m_allCharVector = new QVector<QVector<Character*>*>;
    m_allCharVector->push_back(m_charVector);
    m_allCharVector->push_back(m_enemyVector);

    // Create blank enemy for combo box purpose
    m_newChar = new Character("Enemy");
    m_enemyVector->push_back(m_newChar);
    m_enemyComboBoxModel->appendRow(new QStandardItem(""));

    // Create storage vector for char/enemy combo boxes
    m_charComboBoxVector = new QVector<QComboBox*>;
    m_enemyComboBoxVector = new QVector<QComboBox*>;

    // Create storage vector for char/enemy stat boxes and build the AllStatBox vector,
    // which contains all stat boxes
    m_charStatBoxVector = new QVector<CharStatBox*>;
    m_enemyStatBoxVector = new QVector<CharStatBox*>;
    m_allStatBoxVector = new QVector<QVector<CharStatBox*>*>;
    m_allStatBoxVector->push_back(m_charStatBoxVector);
    m_allStatBoxVector->push_back(m_enemyStatBoxVector);

    // Display character's stat boxes
    for (int iplayer(0); iplayer < m_nPlayers; iplayer++)
    {
        m_charStatBox = new CharStatBox("Character", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->characterLayout->addWidget(m_charStatBox);

        // Save the combo box
        m_charComboBoxVector->push_back(m_charStatBox->getComboBox());

        // Save the char stat box
        m_charStatBoxVector->push_back(m_charStatBox);
    }

    // Display enemy's stat boxes
    for (int ienemies(0); ienemies < 2; ienemies++)
    {
        m_charStatBox = new CharStatBox("Enemy", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->enemyLayout->addWidget(m_charStatBox);

        // Save the combo box
        m_enemyComboBoxVector->push_back(m_charStatBox->getComboBox());

        // Save the enemy stat box
        m_enemyStatBoxVector->push_back(m_charStatBox);
    }

    // Set all QLineEdits to readonly and make them smaller
    QList<QLineEdit*> allQLineEdit = findChildren<QLineEdit*>();
    for (int i(0); i < allQLineEdit.size(); i++)
    {
        allQLineEdit.at(i)->setReadOnly(true);
        allQLineEdit.at(i)->setMaximumHeight(20);
        allQLineEdit.at(i)->setMaximumWidth(40);
    }

    // Set model for all name combo boxes
    for (int i(0); i < m_charComboBoxVector->size(); i++)
    {
        m_charComboBoxVector->at(i)->setModel(m_charComboBoxModel);
    }
    for (int j(0); j < m_enemyComboBoxVector->size(); j++)
    {
        m_enemyComboBoxVector->at(j)->setModel(m_enemyComboBoxModel);
    }

    /* Connect all combo box signal to the corresponding stat box slot.
       Note: Since I cannot pass the combo box index in the signal,
       I could not find a more elegant way to NOT create different slots. */
    QObject::connect(m_charStatBoxVector->at(0)->getComboBox(), SIGNAL(currentIndexChanged(QString)), this, SLOT(displayCharStats1(QString)));
    QObject::connect(m_charStatBoxVector->at(1)->getComboBox(), SIGNAL(currentIndexChanged(QString)), this, SLOT(displayCharStats2(QString)));
    QObject::connect(m_charStatBoxVector->at(2)->getComboBox(), SIGNAL(currentIndexChanged(QString)), this, SLOT(displayCharStats3(QString)));
    QObject::connect(m_charStatBoxVector->at(3)->getComboBox(), SIGNAL(currentIndexChanged(QString)), this, SLOT(displayCharStats4(QString)));
    QObject::connect(m_enemyStatBoxVector->at(0)->getComboBox(), SIGNAL(currentIndexChanged(QString)), this, SLOT(displayEnemyStats1(QString)));
    QObject::connect(m_enemyStatBoxVector->at(1)->getComboBox(), SIGNAL(currentIndexChanged(QString)), this, SLOT(displayEnemyStats2(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCharButton_clicked(){createNewChar("Character");}

void MainWindow::on_addWeaponButton_clicked(){createNewChar("Weapon");}

void MainWindow::on_addEnemyButton_clicked(){createNewChar("Enemy");}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

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

        m_windowTitle = "Yelpy Fantasy: " + m_tableName;
        setWindowTitle(m_windowTitle);
    }
}

void MainWindow::createNewChar(QString charType)
{
    m_addCharDialog = new AddCharDialog(charType, this);
    QString windowTitle = "Add " + charType;
    m_addCharDialog->setWindowTitle(windowTitle);
    int dialogReturn = m_addCharDialog->exec();

    // Gather all character's stats
    QString name      = m_addCharDialog->getCharStatBox()->getStats()->value("Name")->displayText();
    QString level     = m_addCharDialog->getCharStatBox()->getStats()->value("Level")->displayText();
    QString hp        = m_addCharDialog->getCharStatBox()->getStats()->value("HP")->displayText();
    QString mp        = m_addCharDialog->getCharStatBox()->getStats()->value("MP")->displayText();
    QString strength  = m_addCharDialog->getCharStatBox()->getStats()->value("Strength")->displayText();
    QString vitality  = m_addCharDialog->getCharStatBox()->getStats()->value("Vitality")->displayText();
    QString magic     = m_addCharDialog->getCharStatBox()->getStats()->value("Magic")->displayText();
    QString spirit    = m_addCharDialog->getCharStatBox()->getStats()->value("Spirit")->displayText();
    QString dexterity = m_addCharDialog->getCharStatBox()->getStats()->value("Dexterity")->displayText();
    QString chance    = m_addCharDialog->getCharStatBox()->getStats()->value("Chance")->displayText();
    QString attack    = m_addCharDialog->getCharStatBox()->getStats()->value("Attack")->displayText();

    if (dialogReturn == QDialog::Accepted && !name.isEmpty())
    {
        // Create the character/enemy
        m_newChar = new Character(charType, name, level, hp, mp, strength,
                                  vitality, magic, spirit, dexterity, chance,
                                  attack);

        if (charType == "Character")
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
}

void MainWindow::displayCharStats1(QString charName){fillStatBox(0, "Character", charName);}
void MainWindow::displayCharStats2(QString charName){fillStatBox(1, "Character", charName);}
void MainWindow::displayCharStats3(QString charName){fillStatBox(2, "Character", charName);}
void MainWindow::displayCharStats4(QString charName){fillStatBox(3, "Character", charName);}
void MainWindow::displayEnemyStats1(QString enemyName){fillStatBox(0, "Enemy", enemyName);}
void MainWindow::displayEnemyStats2(QString enemyName){fillStatBox(1, "Enemy", enemyName);}

void MainWindow::fillStatBox(int i, QString charType, QString charName)
{
    int itype(0);
    if (charType == "Enemy"){itype = 1;}

    // Find the character in the storage vector
    for (int it(0); it < m_allCharVector->at(itype)->size(); it++)
    {
        if(m_allCharVector->at(itype)->at(it)->getStats()->value("Name") == charName)
        {
            // Get all stats
            QString level     = m_allCharVector->at(itype)->at(it)->getStats()->value("Level");
            QString hp        = m_allCharVector->at(itype)->at(it)->getStats()->value("HP");
            QString hpMax     = m_allCharVector->at(itype)->at(it)->getStats()->value("HPMax");
            QString mp        = m_allCharVector->at(itype)->at(it)->getStats()->value("MP");
            QString mpMax     = m_allCharVector->at(itype)->at(it)->getStats()->value("MPMax");
            QString strength  = m_allCharVector->at(itype)->at(it)->getStats()->value("Strength");
            QString vitality  = m_allCharVector->at(itype)->at(it)->getStats()->value("Vitality");
            QString magic     = m_allCharVector->at(itype)->at(it)->getStats()->value("Magic");
            QString spirit    = m_allCharVector->at(itype)->at(it)->getStats()->value("Spirit");
            QString dexterity = m_allCharVector->at(itype)->at(it)->getStats()->value("Dexterity");
            QString chance    = m_allCharVector->at(itype)->at(it)->getStats()->value("Chance");
            QString attack    = m_allCharVector->at(itype)->at(it)->getStats()->value("Attack");

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
        }
    }
}
