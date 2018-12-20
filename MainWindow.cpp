#include "MainWindow.h"
#include "AddCharDialog.h"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int iplayer(0); iplayer < m_nPlayers; iplayer++)
    {
        m_charStatBox = new CharStatBox("Character", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->characterLayout->addWidget(m_charStatBox);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCharButton_clicked()
{
    m_addCharDialog = new AddCharDialog("Character", this);
    m_addCharDialog->setWindowTitle(tr("Add a Character"));
    int dialogReturn = m_addCharDialog->exec();
//    if (dialogReturn == QDialog::Accepted && !m_addCharDialog->m_charStatBox->getStats().at(0)->displayText().isEmpty())
    if (dialogReturn == QDialog::Accepted)
    {
        // Get all stats and store them
        QString name = m_addCharDialog->m_charStatBox->getStats().at(0)->displayText();
        QString level = m_addCharDialog->m_charStatBox->getStats().at(1)->displayText();
        QString hp = m_addCharDialog->m_charStatBox->getStats().at(2)->displayText();
        QString mp = m_addCharDialog->m_charStatBox->getStats().at(3)->displayText();

        // Create the character and add it to the characters bundle
        m_charBundle = new QVector<Character*>;
        m_character = new Character(name, level, hp, mp);
        m_charBundle->push_back(m_character);
    }
}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_addEnemyButton_clicked()
{
    m_addCharDialog = new AddCharDialog("Enemy", this);
    m_addCharDialog->setWindowTitle(tr("Add an Enemy"));
    int dialogReturn = m_addCharDialog->exec();
//    if (dialogReturn == QDialog::Accepted && !m_addCharDialog->m_charStatBox->getStats().at(0)->displayText().isEmpty())
    if (dialogReturn == QDialog::Accepted)
    {
        // Get all stats and store them
        QString name = m_addCharDialog->m_charStatBox->getStats().at(0)->displayText();
        QString level = m_addCharDialog->m_charStatBox->getStats().at(1)->displayText();
        QString hp = m_addCharDialog->m_charStatBox->getStats().at(2)->displayText();
        QString mp = m_addCharDialog->m_charStatBox->getStats().at(3)->displayText();

        // Create the enemy and add it to the enemy bundle
        m_enemyBundle = new QVector<Character*>;
        m_enemy = new Character(name, level, hp, mp);
        m_enemyBundle->push_back(m_enemy);

        // Display enemy
        m_charStatBox = new CharStatBox("Enemy", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->enemyLayout->addWidget(m_charStatBox);
    }
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
