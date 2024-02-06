#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setNewPlocha(this->rozPlochy,this->pocetMin);
    connect(this->ui->actionNew_Game, &QAction::triggered,this, &MainWindow::newGame);
    connect(this->ui->actionQuit, &QAction::triggered,this, &MainWindow::quit);
    connect(this->ui->actionAuthor, &QAction::triggered,this, &MainWindow::aboutClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::quit()
{
    this->hide();
    std::exit(0);
}

void MainWindow::setNewPlocha(int rozPlochy,int pocetMin)
{
    this->setFixedSize(0,0);
    plochaLayout = new Plocha(rozPlochy, pocetMin);

    for (auto ctverec : plochaLayout->ctvercy)
    {
        connect(ctverec, &Ctverec::ctverecClicked, this, &MainWindow::onCtverecClicked);
    }

    ui->centralwidget->setLayout(plochaLayout);
    this->resize(plochaLayout->minimumSize());
}

void MainWindow::onCtverecClicked(bool isMina, int row, int col)
{
    if (isFirstMove)
    {
        plochaLayout->setMiny(pocetMin);
        isFirstMove = false;
    }
    if (isMina)
    {
        gameOver = true;
        QPixmap unclickedBomb(":/bombs-and-flags-pictures/unclicked-bomb.png");
        for (auto ctverec : plochaLayout->ctvercy)
        {
            if (ctverec->mina){
                ctverec->setIcon(unclickedBomb);
            }
        }
        newGame();
        return;
    }

    int pocetMin = plochaLayout->checkSousede(row,col);

    if (pocetMin)
    {
        plochaLayout->getCtverec(row, col)->setIcon(QIcon((":/block-pictures/" + std::to_string(pocetMin) + ".png").c_str()));
    }
    else
    {
        QPixmap blankIcon (":/block-pictures/blank.png");
        plochaLayout->getCtverec(row, col)->setIcon(blankIcon);
        QList<Ctverec*> sousede = plochaLayout->getSousede(row,col);

        for (auto soused : sousede)
        {
            soused->click();
        }
    }

    if (plochaLayout->getMovesLeft() == 0)
    {
        success = true;
        newGame();
    }
}

void MainWindow::newGame()
{
    this->chooseSlozitost();
    plochaLayout->clear();
    delete plochaLayout;
    this->setNewPlocha(rozPlochy,pocetMin);
    success = false;
    gameOver = false;
    isFirstMove = true;
}

void MainWindow::chooseSlozitost()
{
    QStringList slozitost({"Easy","Medium","Hard"});
    QString zprava = "Vyberte slozitost:";

    if (gameOver)
    {
        zprava = "Hra skoncila! Chces zacit znovu?";
        gameOver = false;
    }

    if (success)
    {
        zprava = "Hurra! Jsi vyhral. Chces zacit znovu?";
    }

    Dialog dialog(slozitost, zprava);

    if (dialog.exec() == QDialog::Accepted)
    {
        QString vyber = dialog.comboBox()->currentText();
        this->slozitost = slozitost.indexOf(vyber);

        switch(this->slozitost)
        {
        case 0:
            this->rozPlochy = 7;
            this->pocetMin = 7;
            break;

        case 1:
            this->rozPlochy = 12;
            this->pocetMin = 22;
            break;

        case 2:
            this->rozPlochy = 15;
            this->pocetMin = 50;
            break;
        }
    }
}

void MainWindow::aboutClicked() {
    QMessageBox msg;
    msg.about(this, "About","Autor Ilya Vorobyev");
}
