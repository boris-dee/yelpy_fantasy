#include "MainWindow.h"
#include "AddCharDialog.h"
#include "Character.h"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QString>

// === Debug ===
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create models for char/enemy name combo boxes
    m_charComboBoxModel = new QStandardItemModel;
    m_enemyComboBoxModel = new QStandardItemModel;

    // Create storage vector for char/enemy
    m_charVector = new QVector<Character*>;
    m_enemyVector = new QVector<Character*>;

    // Create storage vector for char/enemy combo boxes
    m_charComboBoxVector = new QVector<QComboBox*>;
    m_enemyComboBoxVector = new QVector<QComboBox*>;

    // Display character's stat boxes
    for (int iplayer(0); iplayer < m_nPlayers; iplayer++)
    {
        m_charStatBox = new CharStatBox("Character", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->characterLayout->addWidget(m_charStatBox);

        // Save the combo box
        m_charComboBoxVector->push_back(m_charStatBox->getComboBox());

        // Connect the combo box to the corresponding stat box
        QObject::connect(m_charStatBox->getComboBox(), SIGNAL(currentTextChanged(QString)), m_charStatBox, SLOT(displayCharStats(QString)));
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

        // Connect the combo box signal to the corresponding stat box slot
        QObject::connect(m_charStatBox->getComboBox(), SIGNAL(currentIndexChanged(QString)), m_charStatBox, SLOT(displayEnemyStats(QString)));
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCharButton_clicked(){createNewChar("Character");}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_addEnemyButton_clicked(){createNewChar("Enemy");}

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

    QString name = m_addCharDialog->m_charStatBox->getStats()->value("Name")->displayText();
    if (dialogReturn == QDialog::Accepted && !name.isEmpty())
    {
        if (charType == "Character")
        {
            // Create the character
            m_newChar = new Character("Character", "Yuffie");

            // Fill character's stats
            //m_newChar->m_name = name;

            // Store the character
            m_charVector->push_back(m_newChar);

            // Populate the model for char combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_charComboBoxModel->appendRow(item);
        }
        else
        {
            // Create the enemy
            m_newChar = new Character("Enemy", "Sephiroth");

            // Store the enemy
            m_enemyVector->push_back(m_newChar);

            // Populate the model for enemy combo boxes
            QStandardItem *item = new QStandardItem(name);
            m_enemyComboBoxModel->appendRow(item);
        }
    }
}

//
