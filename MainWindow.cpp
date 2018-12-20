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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addCharButton_clicked()
{
    m_addCharDialog = new AddCharDialog("Character", this);
    int dialogReturn = m_addCharDialog->exec();
    if (dialogReturn == QDialog::Accepted)
    {
        MainWindow::close();
    }
}

void MainWindow::on_exitButton_clicked()
{
    MainWindow::close();
}

void MainWindow::on_addEnemyButton_clicked()
{
    m_addCharDialog = new AddCharDialog("Enemy");
    int dialogReturn = m_addCharDialog->exec();
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
