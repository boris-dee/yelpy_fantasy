#include "AddCharDialog.h"
#include "MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

AddCharDialog::AddCharDialog(QString charType, QWidget *parent) : QDialog(parent)
{
    m_dialogBox = new QDialog;

    // Layouts and objects
    QVBoxLayout *gridLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    m_charStatBox = new CharStatBox(charType, true);

    QPushButton *saveCharButton = new QPushButton;
    saveCharButton->setMaximumWidth(80);
    saveCharButton->setText(tr("Add"));
    saveCharButton->setDefault(true);

    QPushButton *cancelButton = new QPushButton;
    cancelButton->setMaximumWidth(80);
    cancelButton->setText(tr("Cancel"));

    // Assemble everything
    buttonLayout->addWidget(saveCharButton);
    buttonLayout->addWidget(cancelButton);

    gridLayout->addWidget(m_charStatBox);
    gridLayout->addLayout(buttonLayout);
    m_dialogBox->setLayout(gridLayout);

    // Create and assemble the upper (widget) grid
    QHBoxLayout *upperGrid = new QHBoxLayout(this);
    upperGrid->addWidget(m_dialogBox);

    // Connecting everything
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(saveCharButton, SIGNAL(clicked()), this, SLOT(accept()));
}

CharStatBox* AddCharDialog::getCharStatBox() const
{
    return m_charStatBox;
}
