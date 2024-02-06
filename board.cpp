#include "board.h"

Plocha::Plocha(int rozPlochy, int pocetMin)
{
    this->rozPlochy = rozPlochy;
    this->setSpacing(0);

    QPixmap emptyBlockIcon = QPixmap(":/block-pictures/empty-block.png");

    for (int row = 0; row < rozPlochy; row ++)
    {
        for (int col = 0; col < rozPlochy; col ++)
        {
            Ctverec * ctverec = new Ctverec(row,col);
            ctverec->setFixedSize(30,30);
            ctverec->setIcon(emptyBlockIcon);
            ctverec->setIconSize(ctverec->size());
            this->addCtverec(ctverec);
        }
    }
}

void Plocha::setMiny(int pocetMin)
{
    for (int i = 0; i < pocetMin;)
    {
        int random = rand() % (rozPlochy * rozPlochy);
        int x = random / rozPlochy;
        int y = random % rozPlochy;
        Ctverec * ctverec = this->getCtverec(x,y);

        if (ctverec->mina == false)
        {
            ctverec->mina = true;
            i++;
        }
    }
    return;
}

void Plocha::clear()
{
    for (auto ctverec : ctvercy)
    {
        ctverec->hide();
        ctvercy.pop_front();
        this->removeWidget(ctverec);
        delete ctverec;
    }
}

int Plocha::checkSousede(int row, int col)
{
    QList<Ctverec*> sousede = getSousede(row,col);
    int numMines = 0;

    for (auto soused : sousede)
    {
        if (soused->mina)
        {
            numMines += 1;
        }
    }
    return numMines;
}

QList<Ctverec*> Plocha::getSousede(int row, int col)
{
    QList<Ctverec*> sousede;

    int sousedeIndex[8][2] =
        {
            {row - 1, col},      //North
            {row + 1, col},      //South
            {row, col + 1},      //East
            {row, col - 1},      //West
            {row - 1, col + 1},  //North-East
            {row - 1, col - 1},  //North-West
            {row + 1, col + 1},  //South-East
            {row + 1 , col - 1}, //South-West
        };

    for (auto index : sousedeIndex)
    {
        if (isValid(index[0],index[1]))
        {
            sousede.push_back(getCtverec(index[0],index[1]));
        }
    }
    return sousede;
}

int Plocha::getMovesLeft()
{
    int movesLeft = 0;

    for (auto ctverec : ctvercy)
    {
        if (ctverec->isEnabled())
        {
            if (!ctverec->mina)
            {
                movesLeft += 1;
            }
        }
    }
    return movesLeft;
}
