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
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("Test");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(lineEdit);
    charStatBox->setLayout(vbox);

    return charStatBox;
}
