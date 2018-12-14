#include "addcharacter.h"
#include "ui_addcharacter.h"
#include "mainwindow.h"

#include <QGridLayout>

AddCharacter::AddCharacter(QString charType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCharacter)
{
    ui->setupUi(this);

    // Windows title
    QString title("Add " + charType);
    setWindowTitle(title);
}

AddCharacter::~AddCharacter()
{
    delete ui;
}
