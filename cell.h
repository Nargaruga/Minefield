#ifndef CELL_H
#define CELL_H

//A single cell of the minefield
class Cell
{
public:
    Cell(int i, int j);

    int getRow() { return row; }
    int getColumn() { return column; }

    bool isRevealed() { return revealed; }
    void setRevealed(bool r) { revealed = r; }

    bool isMarked() { return marked; }
    void setMarked(bool m) { marked = m; }

    bool hasMine() { return mine; }
    void setMine(bool m) { mine = m; }

    int getNeighbouringMineCount() { return neighbouringMineCount; }
    void setNeighbouringMineCount(int count) { neighbouringMineCount = count; }

private:
    int row;
    int column;
    bool revealed = false; //Indicates whether this cell was revealed or not
    bool marked = false; //Indicates whether this cell was marked or not
    bool mine = false; //Indicates whether this cell contains a mine or not
    int neighbouringMineCount = 0; //Number of mines in neighbouring cells
};

#endif // CELL_H
