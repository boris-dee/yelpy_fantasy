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

    QGroupBox *groupBox = new QGroupBox(tr("Test"));
    QLabel *label = new QLabel(tr("Test"));
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("Test");

    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("Test");
    lineEdit->setFocus();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(comboBox, 0, 1);
    layout->addWidget(lineEdit, 1, 0, 1, 2);
    groupBox->setLayout(layout);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(groupBox, 0, 0);
    setLayout(mainLayout);

    QWidget *screenLayout = new QWidget;
    screenLayout->setLayout(mainLayout);
    setCentralWidget(screenLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
