#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"
#include "dialogs.h"
#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setNewPlocha(int sideLength, int numMines);
    void newGame();
    void chooseSlozitost();
    void quit();

public slots:
    void onCtverecClicked(bool isBomb, int row, int col);
    void aboutClicked();

private:
    Plocha * plochaLayout;
    Ui::MainWindow *ui;
    bool gameOver = false;
    bool success = false;
    bool isFirstMove = true;

    // 0 = easy, 1 = medium, 2 = hard
    int slozitost = 0;
    // 10 = easy, 16 = medium, 24 = hard
    int rozPlochy = 10;
    // 9 = easy, 40 = medium, 99 = hard
    int pocetMin = 4;       //pro kontrolu vyherne zpravy
};

#endif // MAINWINDOW_H
