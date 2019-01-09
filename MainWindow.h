#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "CharStatBox.h"
#include "Character.h"
#include "Item.h"

#include <QFile>
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
    void newDialog(QString newType);
    void createNew(QString newType, QString name, QString level, QString hp, QString mp, QString strength, QString vitality, QString magic,
                   QString spirit, QString dexterity, QString chance, QString attack, QString attackPercent, QString magAttack,
                   QString magAttackPercent, QString critHitPercent, QString defense, QString defensePercent,
                   QString magDefense, QString magDefPercent, QString weapon, QString armor, QString accessory);
    void fillStatBox(int i, QString charType, QString charName);
    void updateStats(int i);
    void writeToFile();
    void readFromFile();

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

    void on_saveButton_clicked();

    void on_loadButton_clicked();

private:
    bool m_alreadySaved = false;
    int m_nPlayerStatBox = 4, m_nEnemyStatBox = 2;
    QString m_tableName, m_saveFilePath, m_loadFilePath;
    QString m_windowTitle;
    QString m_nChar, m_nEnemies, m_nWeapons, m_nArmors, m_nAccessories;

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
    QFile *m_saveFile, *m_loadFile;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
