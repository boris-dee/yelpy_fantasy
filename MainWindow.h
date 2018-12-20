#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "Character.h"
#include "CharStatBox.h"

#include <QMainWindow>
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

private:
    int m_nPlayers = 4;
    QString m_tableName;
    QString m_windowTitle;
    QVector<Character*> *m_charBundle;
    QVector<Character*> *m_enemyBundle;
    QVector<QString> *m_statBundle;

    AddCharDialog *m_addCharDialog;
    CharStatBox *m_charStatBox;
    Character *m_character;
    Character *m_enemy;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
