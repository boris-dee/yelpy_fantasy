#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "CharStatBox.h"
#include "Character.h"

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

    void createNewChar(QString charType);

    QVector<QVector<CharStatBox*>*> getAllCharVector();

private slots:
    void on_addCharButton_clicked();
    void on_exitButton_clicked();
    void on_addEnemyButton_clicked();
    void on_newButton_clicked();

private:
    int m_nPlayers = 4;
    QString m_tableName;
    QString m_windowTitle;

    AddCharDialog *m_addCharDialog;
    CharStatBox *m_charStatBox;

    QVector<CharStatBox*> *m_charStatBoxVector;
    QVector<CharStatBox*> *m_enemyStatBoxVector;

    QVector<Character*> *m_charVector;
    QVector<Character*> *m_enemyVector;

    QVector<QComboBox*> *m_charComboBoxVector;
    QVector<QComboBox*> *m_enemyComboBoxVector;

    QStandardItemModel *m_charComboBoxModel;
    QStandardItemModel *m_enemyComboBoxModel;

    Character *m_newChar;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
