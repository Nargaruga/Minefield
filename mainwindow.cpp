#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cellbutton.h"
#include "config.h"

#include <chrono>
#include <QDebug>

//TODO: refactor, this class does too many things.

MainWindow::MainWindow(QWidget *parent, int nRows, int nColumns, int nMines)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rows = nRows;
    columns = nColumns;
    mines = nMines;

    initUi();

    grid->layMines();

    connect(grid, SIGNAL(victory()), this, SLOT(onVictory()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(onReset()));
}

MainWindow::~MainWindow()
{
    clearUi();
    delete ui;
    delete grid;
}

void MainWindow::initUi()
{
    grid = new Grid(rows, columns, mines);
    vector<vector<CellButton*>*>* buttons = grid->getButtons();

    for(int i = 0; i < rows; i++)
    {
        buttons->push_back(new vector<CellButton*>);
        for(int j = 0; j < columns; j++)
        {

            Cell* cell = new Cell(i, j);
            CellButton* btn = new CellButton();
            btn->setCell(cell);
            btn->setFixedSize(CELL_SIZE, CELL_SIZE);
            btn->setStyleSheet(QString("background-color: %1;").arg(defaultColor));
            buttons->at(i)->push_back(btn);

            ui->gridLayout->addWidget(btn, i, j, 1, 1);

            connect(btn, SIGNAL(mineHit()), this, SLOT(onMineHit()));
            connect(btn, SIGNAL(shouldRevealNeighbours(int, int)), grid, SLOT(revealNeighbours(int, int)));
            connect(btn, SIGNAL(leftClick()), grid, SLOT(onButtonLeftClicked()));
        }
    }

    ui->gridLayout->setSpacing(0);
}

void MainWindow::clearUi()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            CellButton* btn = grid->getButtons()->at(i)->at(j);
            ui->gridLayout->removeWidget(btn);
            delete btn;
        }
    }

    delete grid;
}

void MainWindow::onReset()
{
    grid->clearMines();
    grid->layMines();
    concealGrid();
    ui->label->setText("");
}

void MainWindow::revealGrid()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            grid->getButtons()->at(i)->at(j)->reveal();
        }
    }
}

void MainWindow::concealGrid()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            grid->getButtons()->at(i)->at(j)->conceal();
        }
    }
    grid->resetConcealedCount();
}

void MainWindow::onMineHit()
{
    ui->label->setText("You Lost!");
    revealGrid();
}

void MainWindow::onVictory()
{
    ui->label->setText("You Won!");
}


void MainWindow::on_actionEasy_triggered()
{
    clearUi();

    rows = EASY_ROWS;
    columns = EASY_COLUMNS;
    mines = EASY_MINES;

    initUi();
    grid->layMines();
    connect(grid, SIGNAL(victory()), this, SLOT(onVictory()));
}


void MainWindow::on_actionMedium_triggered()
{
    clearUi();

    rows = MEDIUM_ROWS;
    columns = MEDIUM_COLUMNS;
    mines = MEDIUM_MINES;

    initUi();
    grid->layMines();
    connect(grid, SIGNAL(victory()), this, SLOT(onVictory()));
}

void MainWindow::on_actionHard_triggered()
{
    clearUi();

    rows = HARD_ROWS;
    columns = HARD_COLUMNS;
    mines = HARD_MINES;

    initUi();

    grid->layMines();
    connect(grid, SIGNAL(victory()), this, SLOT(onVictory()));
}

void MainWindow::on_actionREVEAL_triggered()
{
    revealGrid();
}

void MainWindow::on_actionCONCEAL_triggered()
{
    concealGrid();
}
