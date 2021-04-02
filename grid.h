#ifndef GRID_H
#define GRID_H

#include "config.h"

#include <cellbutton.h>
#include <vector>

#define RESET false
#define COUNT true

using std::vector;

//A grid of CellButtons
class Grid: public QObject
{
    Q_OBJECT

public:
    Grid(int rows = DEFAULT_ROWS, int columns = DEFAULT_COLUMNS, int mines = DEFAULT_MINES);
    ~Grid();

    int getRows() { return rows; }
    void setRows(int n) { rows = n; }

    int getColumns() { return columns; }
    void setColumns(int n) { columns = n; }

    int getMines() { return mines; }
    void setMines(int m) { mines = m; }

    int getConcealedCount() { return concealedCount; }
    void decrementConcealedCount() { concealedCount--; }
    void resetConcealedCount() { concealedCount = rows * columns; }

    vector<vector<CellButton*>*>* getButtons() { return buttons; }

    //Randomly places mines in the grid
    void layMines();

    //Clears all mines
    void clearMines();

    //Returns the number of occupied cells neighbouring the cell at cells[row][column]
    int countOccupiedNeighbours(int row, int column);

    //Sets the number of occupied neighbouring cells for every cell in the grid.
    //  The number is set to the actual count if action == COUNT, else it's set to 0.
    void setNeighbourCounts(bool action);

signals:
    void victory();

public slots:
    void revealNeighbours(int row, int column);
    void onButtonLeftClicked();

private:
    int rows;
    int columns;
    int mines;
    int concealedCount;
    vector<vector<CellButton*>*>* buttons;
};

#endif // GRID_H
