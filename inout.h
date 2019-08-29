#ifndef inout_h
#define inout_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

//Lista do przechowywania histori rozwi�za�
struct List;
//wypisuje list� do strumienia stream
void listPrint(FILE* stream, struct List* list);

//Prosi u�ytkownika o odpowied� tak/nie
bool askBool(char* text, bool def);
//Prosi u�ytkownika o wyb�r jednej z trzech opcji
char choose3(char* text, char* opt1, char* opt2, char* opt3, char nr1, char nr2, char nr3);
//ustawia kursor w miejscu cyfry o wsp�rz�dnych (x,y) na planszy sudoku
void cursorSudokuPos(int startRow, int x, int y);
//wypisuje plansz� do pliku file
void fprintSudoku(FILE* file, char tab[9][9]);
//Importuje plansz� z pliku
char importFromFile(char tab[9][9], char* path);
//pobiera plansz� od u�ytkownika lub z pliku, zwraca kod b��du
char input(char sudoku[9][9]);
//Wype�nia plansz� sudoku z klawiatury
char inputConsole(char sudoku[9][9]);
//Pyta u�ytkownica o zapis wynikowej planszy do pliku, o nawzw� pliku i zapisuje
char output(char sudoku[9][9]);
//zapisuje plansz� sudoku do pliku path
char outputSave(char sudoku[9][9], char* path);
//Pyta u�ytkownica o zapis histori rozwi�zania do pliku i zapisuje
char outputHistory(struct List* list);
//zapisuje plansz� sudoku do pliku path
char outputSaveHistory(struct List* list, char* path);

#endif
