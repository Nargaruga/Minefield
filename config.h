#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

#define CELL_SIZE 30

#define DEFAULT_ROWS 16
#define DEFAULT_COLUMNS 30
#define DEFAULT_MINES 99

#define EASY_ROWS 8
#define EASY_COLUMNS 8
#define EASY_MINES 10

#define MEDIUM_ROWS 16
#define MEDIUM_COLUMNS 16
#define MEDIUM_MINES 40

#define HARD_ROWS 16
#define HARD_COLUMNS 30
#define HARD_MINES 99

extern QString defaultColor;
extern QString emptyColor;
extern QString markedColor;
extern QString mineColor;



#endif // CONFIG_H
