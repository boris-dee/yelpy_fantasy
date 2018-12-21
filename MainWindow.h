#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "CharStatBox.h"

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addCharButton_clicked();
    void on_exitButton_clicked();
    void on_addEnemyButton_clicked();
    void on_newButton_clicked();

    void createNewChar(QString charType);

private:
    int m_nPlayers = 4;
    QString m_tableName;
    QString m_windowTitle;

    AddCharDialog *m_addCharDialog;
    CharStatBox *m_charStatBox;

    QVector<CharStatBox*> *m_charVector;
    QVector<CharStatBox*> *m_enemyVector;
    QVector<QVector<CharStatBox*>*> *m_allCharVector;

    QStandardItemModel *m_comboBoxModel;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
