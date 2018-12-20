#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "Character.h"
#include "CharStatBox.h"
#include "EnemyStatBox.h"
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
    QString m_tableName;
    QString m_windowTitle;

    CharStatBox *m_charStatBox;
    EnemyStatBox *m_enemyStatBox;
    AddCharDialog *m_addCharDialog;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
