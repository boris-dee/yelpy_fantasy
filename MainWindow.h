#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "CharStatBox.h"
#include "Character.h"
#include "Item.h"

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

    void initialization();
    void displayStatBoxes();
    void formatLineEdits();
    void setComboBoxModels();
    void connectSignals();
    void createNew(QString newType);
    void fillStatBox(int i, QString charType, QString charName);
    void updateStats(int i);

private slots:
    void on_addCharButton_clicked();
    void on_addWeaponButton_clicked();
    void on_addArmorButton_clicked();
    void on_addEnemyButton_clicked();
    void on_addAccessoryButton_clicked();
    void on_exitButton_clicked();
    void on_newButton_clicked();

    void fillCharStatBox1(QString charName);
    void fillCharStatBox2(QString charName);
    void fillCharStatBox3(QString charName);
    void fillCharStatBox4(QString charName);
    void fillEnemyStatBox1(QString enemyName);
    void fillEnemyStatBox2(QString enemyName);
    void updateStats1();
    void updateStats2();
    void updateStats3();
    void updateStats4();

private:
    int m_nPlayers = 4, m_nEnemies = 2;
    QString m_tableName;
    QString m_windowTitle;

    AddCharDialog *m_addCharDialog;
    CharStatBox *m_charStatBox;

    QVector<CharStatBox*> *m_charStatBoxVector, *m_enemyStatBoxVector;
    QVector<QVector<CharStatBox*>*> *m_allStatBoxVector;

    QVector<Character*> *m_charVector, *m_enemyVector;
    QVector<QVector<Character*>*> *m_allCharVector;

    QVector<Item*> *m_weaponVector, *m_armorVector, *m_accessoryVector;

    QVector<QComboBox*> *m_charComboBoxVector, *m_enemyComboBoxVector;
    QVector<QComboBox*> *m_weaponComboBoxVector, *m_armorComboBoxVector;
    QVector<QComboBox*> *m_accessoryComboBoxVector;

    QStandardItemModel *m_charComboBoxModel, *m_enemyComboBoxModel;
    QStandardItemModel *m_weaponComboBoxModel, *m_armorComboBoxModel;
    QStandardItemModel *m_accessoryComboBoxModel;

    Character *m_newChar;
    Item *m_newWeapon, *m_newArmor, *m_newAccessory;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
