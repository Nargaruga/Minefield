#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include "cell.h"
#include <QToolButton>

//Class that implements a clickable cell
class CellButton: public QToolButton
{
    Q_OBJECT

public:
    CellButton();
    ~CellButton();

    Cell* getCell() { return cell; }
    void setCell(Cell* c) { cell = c; }

    void reveal();
    void conceal();
    void leftClicked();
    void rightClicked();

signals:
    void leftClick();
    void mineHit();
    void shouldRevealNeighbours(int row, int column);

protected:
    void mouseReleaseEvent(QMouseEvent* e) override;

private:
    Cell* cell; //Cell associated with this button
};

#endif // CELLBUTTON_H
