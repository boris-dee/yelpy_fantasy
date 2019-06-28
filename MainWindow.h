#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AddCharDialog.h"
#include "StatBox.h"
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
    void setComboBoxModels();
    void setListModels();
    void connectSignals();
    void loadLevelData();
    void newDialog(QString newType);
    void createNew(QString newType, QString name, QString level, QString expPoints, QString hp, QString mp, QString hpMax, QString mpMax, QString strength, QString vitality,
                   QString magic, QString spirit, QString dexterity, QString luck, QString limitBreak, QString attack, QString attackPercent, QString magAttack,
                   QString magAttackPercent, QString critHitPercent, QString defense, QString defensePercent,
                   QString magDefense, QString magDefPercent, QString weapon, QString armor, QString accessory, QString factor, QString mpCost,
                   bool poison, bool sadness, bool fury, bool silence, bool darkness, bool frog);
    void fillStatBox(int i, QString charType, QString charName);
    void updateStats(int i);
    void checkHPMP(int i, QString charType);
    void setHPMP(int i, QString charType);
    void writeToFile();
    void readFromFile();
    void enableButtons();
    void computeDamage(QString charType, QString type, QString name);
    void updateInfo(QString charType, QModelIndex index);
    void updateAilments(QString charType, QModelIndex index);
    void loadPlayers(int nChar);

private slots:
    void on_addCharButton_clicked();
    void on_addWeaponButton_clicked();
    void on_addArmorButton_clicked();
    void on_addEnemyButton_clicked();
    void on_addAccessoryButton_clicked();
    void on_exitButton_clicked();
    void on_newTableButton_clicked();
    void on_addAttackButton_clicked();
    void on_addMagicButton_clicked();
    void on_addSummonButton_clicked();
    void on_addItemButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_fullRegenButton_clicked();
    void on_expButton_clicked();
    void on_charAttackButton_clicked();
    void on_charMagicButton_clicked();
    void on_charSummonButton_clicked();
    void on_charItemButton_clicked();
    void on_enemyAttackButton_clicked();
    void on_enemyMagicButton_clicked();
    void on_charAttackComboBox_currentIndexChanged(QString attackName);
    void on_charMagicComboBox_currentIndexChanged(QString attackName);
    void on_charSummonComboBox_currentIndexChanged(QString attackName);
    void on_enemyAttackComboBox_currentIndexChanged(QString attackName);
    void on_enemyMagicComboBox_currentIndexChanged(QString attackName);
    void on_charListView_clicked(QModelIndex index);
    void on_enemyListView_clicked(QModelIndex index);
    void toggleCharAilment();
    void toggleEnemyAilment();
    void toggleAilment(QString charType, QString ailment);

    void fillStatBox1(QString charName);
    void fillStatBox2(QString charName);
    void fillStatBox3(QString charName);
    void fillStatBox4(QString charName);
    void fillStatBox5(QString charName);
    void fillEnemyStatBox1(QString enemyName);
    void fillEnemyStatBox2(QString enemyName);
    void fillEnemyStatBox3(QString enemyName);
    void updateStats1();
    void updateStats2();
    void updateStats3();
    void updateStats4();
    void updateStats5();
    void checkCharHPMP1();
    void checkCharHPMP2();
    void checkCharHPMP3();
    void checkCharHPMP4();
    void checkCharHPMP5();
    void checkEnemyHPMP1();
    void checkEnemyHPMP2();
    void checkEnemyHPMP3();
    void setCharHPMP1();
    void setCharHPMP2();
    void setCharHPMP3();
    void setCharHPMP4();
    void setCharHPMP5();
    void setEnemyHPMP1();
    void setEnemyHPMP2();
    void setEnemyHPMP3();

private:
    bool m_alreadySaved = false;
    int m_nPlayerStatBox = 5, m_nEnemyStatBox = 3;
    QString m_tableName, m_saveFilePath, m_loadFilePath;
    QString m_windowTitle;
    QString m_nChar, m_nEnemies, m_nWeapons, m_nArmors, m_nAccessories;
    QString m_nAttacks, m_nMagic, m_nSummons, m_nItems;

    AddCharDialog *m_addCharDialog;
    StatBox *m_charStatBox;

    QVector<QStringList> *m_levelVector;

    QVector<StatBox*> *m_charStatBoxVector, *m_enemyStatBoxVector;
    QVector<QVector<StatBox*>*> *m_allStatBoxVector;

    QVector<Character*> *m_charVector, *m_enemyVector;
    QVector<QVector<Character*>*> *m_allCharVector;

    QVector<Item*> *m_weaponVector, *m_armorVector, *m_accessoryVector;
    QVector<Item*> *m_attackVector, *m_magicVector, *m_summonVector, *m_itemVector;

    QVector<QComboBox*> *m_charComboBoxVector, *m_enemyComboBoxVector;
    QVector<QComboBox*> *m_weaponComboBoxVector, *m_armorComboBoxVector;
    QVector<QComboBox*> *m_accessoryComboBoxVector, *m_attackComboBoxVector;
    QVector<QComboBox*> *m_magicComboBoxVector, *m_summonComboBoxVector;
    QVector<QComboBox*> *m_itemComboBoxVector;

    QStandardItemModel *m_charComboBoxModel, *m_enemyComboBoxModel;
    QStandardItemModel *m_weaponComboBoxModel, *m_armorComboBoxModel;
    QStandardItemModel *m_accessoryComboBoxModel;
    QStandardItemModel *m_charListViewModel, *m_enemyListViewModel;
    QStandardItemModel *m_attackComboBoxModel, *m_magicComboBoxModel, *m_summonComboBoxModel, *m_itemComboBoxModel;
    QVector<QStandardItemModel*> *m_allComboBoxModels;

    QMap<QString, QPushButton*> *m_charAilmentMap, *m_enemyAilmentMap;
    QVector<QMap<QString, QPushButton*>*> *m_ailmentMapVector;

    Character *m_newChar;
    Item *m_newWeapon, *m_newArmor, *m_newAccessory;
    Item *m_newAttack, *m_newMagic, *m_newSummon, *m_newItem;
    QFile *m_saveFile, *m_loadFile;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
