#ifndef log_h
#define log_h

#include <stdio.h>
#include <time.h>

//wypisuje plansz� do pliku file
void fprintSudoku(FILE* file, char tab[9][9]);

//przygotowuje plik z logami
FILE* prepareLog(char* path);
//dopisuje do pliku z logami
void logApp(FILE* logFile, char* text, char sudoku[9][9]);
//zapisuje do logu aktualn� dat� z du�� dok�adno�ci�
void logDate(FILE* logFile);

#endif
