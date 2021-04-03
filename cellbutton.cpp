#include "cellbutton.h"
#include "config.h"
#include <QKeyEvent>
#include <iostream>

CellButton::CellButton()
{

}

CellButton::~CellButton()
{
    delete cell;
}

//Handles mouse click events
void CellButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton) leftClicked();
    else if(e->button() == Qt::RightButton) rightClicked();

}

void CellButton::leftClicked()
{
    if(getCell() == nullptr) return; //TODO HANDLE ERROR

    emit leftClick();

    reveal();
    if(getCell()->hasMine()) emit mineHit();
    else if(getCell()->getNeighbouringMineCount() == 0) emit shouldRevealNeighbours(cell->getRow(), cell->getColumn());
}

void CellButton::rightClicked()
{
    if(getCell() == nullptr) return; //TODO HANDLE ERROR

    if(getCell()->isMarked())
    {
        setStyleSheet(QString("background-color: %1;").arg(defaultColor));
        getCell()->setMarked(false);
    }
    else
    {
        setStyleSheet(QString("background-color: %1;").arg(markedColor));
        getCell()->setMarked(true);
    }
}

void CellButton::reveal()
{
    setDisabled(true);
    cell->setRevealed(true);

    if(cell->hasMine()) setStyleSheet(QString("background-color: %1;").arg(mineColor));
    else
    {
        setStyleSheet(QString("background-color: %1;").arg(emptyColor));
        if(cell->getNeighbouringMineCount() > 0)
        {
            setText(QString::number(cell->getNeighbouringMineCount()));
            setStyleSheet(styleSheet().append("color: black;"));
        }
    }
}

void CellButton::conceal()
{
    setDisabled(false);
    setText("");
        cell->setRevealed(false);
    setStyleSheet(QString("background-color: %1;").arg(defaultColor));
}
