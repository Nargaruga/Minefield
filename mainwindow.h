#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "config.h"
#include "grid.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int nRows = DEFAULT_ROWS, int nColumns = DEFAULT_COLUMNS, int nMines = DEFAULT_MINES);
    ~MainWindow();

public slots:
    void onMineHit();
    void onVictory();
    void onReset();

private slots:
    void on_actionEasy_triggered();

    void on_actionMedium_triggered();

    void on_actionHard_triggered();

    void on_actionREVEAL_triggered();

    void on_actionCONCEAL_triggered();

private:
    Ui::MainWindow *ui;
    int rows;
    int columns;
    int mines;
    Grid* grid;

    void initUi();
    void clearUi();
    void revealGrid();
    void concealGrid();
};
#endif // MAINWINDOW_H
