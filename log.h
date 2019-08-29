#ifndef log_h
#define log_h

#include <stdio.h>
#include <time.h>

//wypisuje planszê do pliku file
void fprintSudoku(FILE* file, char tab[9][9]);

//przygotowuje plik z logami
FILE* prepareLog(char* path);
//dopisuje do pliku z logami
void logApp(FILE* logFile, char* text, char sudoku[9][9]);
//zapisuje do logu aktualn¹ datê z du¿¹ dok³adnoœci¹
void logDate(FILE* logFile);

#endif
