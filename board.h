#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QPushButton>
#include <QGridLayout>
#include <QMouseEvent>
#include <QPixmap>

class Ctverec : public QPushButton
{
    Q_OBJECT;
public:
    bool mina = false;
    int row;
    int col;
    bool isFlagged;

    Ctverec(int row, int col):QPushButton()
    {
        this->row = row;
        this->col = col;
        connect(this,SIGNAL(clicked()),SLOT(onClicked()));
    }

private slots:
    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button() == Qt::RightButton)
        {
            if (this->isFlagged) {
                this->isFlagged = false;
                this->setIcon(QIcon(":/block-pictures/empty-block.png"));
            } else {
                this->isFlagged = true;
                this->setIcon(QIcon(":/bombs-and-flags-pictures/flag.png"));
            }
        }
        else if (e->button() == Qt::LeftButton && isEnabled())
        {
            emit clicked();
        }
    }
    void onClicked()
    {
        this->clearFocus();
        this->setDisabled(true);
        emit ctverecClicked(this->mina,this->row,this->col);
    }
signals:
    void ctverecClicked(bool isBomb, int row, int col);
};

class Plocha : public QGridLayout
{
public:
    Plocha(int rozPlochy, int pocetMin);
    void addCtverec(Ctverec * ctverec)
    {
        ctvercy.append(ctverec);
        this->addWidget(ctverec, ctverec->row,ctverec->col);
    }
    QList<Ctverec*> getCtvercy()
    {
        return ctvercy;
    }
    Ctverec * getCtverec(int row, int col)
    {
        return ctvercy[rozPlochy*row + col];
    }
    void setMiny(int pocetMin);
    void clear();
    int checkSousede(int row, int col);
    QList<Ctverec*> getSousede(int row, int col);
    bool isValid(int row, int col)      // hranice = lezi v rozsahu
    {
        return (row >= 0) && (row < rozPlochy) &&
               (col >= 0) && (col < rozPlochy);
    }
    QList<Ctverec*> ctvercy;        //  ctvercy -> list
    int getMovesLeft();
private:
    int rozPlochy;
};

#endif // BOARD_H
