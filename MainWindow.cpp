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

    // Create model for all name combo boxes
    m_comboBoxModel = new QStandardItemModel;

    // Create char/enemy storage vectors and build the All Vector
    m_charVector = new QVector<CharStatBox*>;
    m_enemyVector = new QVector<CharStatBox*>;
    m_allCharVector = new QVector<QVector<CharStatBox*>*>;
    m_allCharVector->push_back(m_charVector);
    m_allCharVector->push_back(m_enemyVector);

    for (int iplayer(0); iplayer < m_nPlayers; iplayer++)
    {
        m_charStatBox = new CharStatBox("Character", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->characterLayout->addWidget(m_charStatBox);
    }

    // Display enemies
    for (int ienemies(0); ienemies < 2; ienemies++)
    {
        m_charStatBox = new CharStatBox("Enemy", false);
        m_charStatBox->setMaximumWidth(800);
        m_charStatBox->setMaximumHeight(250);
        ui->enemyLayout->addWidget(m_charStatBox);
    }

    // Set all QLineEdits to readonly and make them smaller
    QList<QLineEdit*> allQLineEdit = findChildren<QLineEdit*>();
    for (int i(0); i < allQLineEdit.size(); ++i)
    {
        allQLineEdit.at(i)->setReadOnly(true);
        allQLineEdit.at(i)->setMaximumHeight(20);
        allQLineEdit.at(i)->setMaximumWidth(40);
    }

    // Set model for all name combo boxes
    QList<QComboBox*> allQComboBox = findChildren<QComboBox*>();
    for (int i(0); i < allQComboBox.size(); ++i)
    {
        allQComboBox.at(i)->setModel(m_comboBoxModel);
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
        // Add the created statBox to the respecting vector depending on char/enemy and add it to the general Vector
        if (charType == "Character"){m_charVector->push_back(m_charStatBox);}
        else                        {m_enemyVector->push_back(m_charStatBox);}

        // Populate the model for combo boxes
        QStandardItem *item = new QStandardItem(name);
        m_comboBoxModel->appendRow(item);
    }
}
