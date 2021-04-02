#include "grid.h"
#include <QDebug>

using std::vector;

int shouldPlace()
{
    return rand() % 2;
}

//Creates a n x m grid
Grid::Grid(int n, int m, int k)
{
    rows = n;
    columns = m;
    mines = k;
    buttons = new vector<vector<CellButton*>*>;
    concealedCount = rows * columns;
}

Grid::~Grid()
{
    for(int i = 0; i < rows; i++)
    {
        delete(buttons->at(i));
    }

    delete buttons;
}

void Grid::layMines()
{
    int count = 0;

    while(count < mines)
    {
        int row = rand() % rows;
        int column = rand() % columns;

        if(!buttons->at(row)->at(column)->getCell()->hasMine())
        {
            buttons->at(row)->at(column)->getCell()->setMine(true);
            count++;
        }
    }

    setNeighbourCounts(COUNT);
}

void Grid::clearMines()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            buttons->at(i)->at(j)->getCell()->setMine(false);
        }
    }
    setNeighbourCounts(RESET);
}

int Grid::countOccupiedNeighbours(int row, int column)
{
    int count = 0;

    for(int rowOffset = -1; rowOffset < 2; rowOffset++)
    {
        for(int columnOffset = -1; columnOffset < 2; columnOffset++)
        {
            int neighbourRow = row + rowOffset;
            int neighbourColumn = column + columnOffset;

            if(neighbourRow < 0 || neighbourRow >= rows ||
                    neighbourColumn < 0 || neighbourColumn >= columns) continue;

            if(buttons->at(neighbourRow)->at(neighbourColumn)->getCell()->hasMine()) count++;
        }
    }

    return count;
}

void Grid::setNeighbourCounts(bool action)
{
    int count = 0;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(action == COUNT) count = countOccupiedNeighbours(i, j);

            buttons->at(i)->at(j)->getCell()->setNeighbouringMineCount(count);
        }
    }
}

void Grid::revealNeighbours(int row, int column)
{
    for(int rowOffset = -1; rowOffset < 2; rowOffset++)
    {
        for(int columnOffset = -1; columnOffset < 2; columnOffset++)
        {
            int neighbourRow = row + rowOffset;
            int neighbourColumn = column + columnOffset;

            if(neighbourRow < 0 || neighbourRow >= rows ||
                    neighbourColumn < 0 || neighbourColumn >= columns) continue;

            CellButton* neighbour = buttons->at(neighbourRow)->at(neighbourColumn);

            if(!neighbour->getCell()->hasMine() && !neighbour->getCell()->isRevealed())
            {
                neighbour->leftClicked();
            }
        }
    }
}

void Grid::onButtonLeftClicked()
{
    concealedCount--;
    if(concealedCount == mines) emit victory();
}
