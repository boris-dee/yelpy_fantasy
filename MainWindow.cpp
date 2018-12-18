#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CharStatBox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    charStatBox = new CharStatBox;
    ui->characterLayout->addWidget(charStatBox);
}

MainWindow::~MainWindow()
{
    delete ui;
}
