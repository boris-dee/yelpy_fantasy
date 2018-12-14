#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QGroupBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Method that creates characters and enemies stats group box
    QGroupBox *createCharStatBox(const int ichar);
    QGroupBox *createEnemyStatBox();

private slots:
    void on_exitButton_clicked();
    void on_addCharButton_clicked();
    void on_addEnemyButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
