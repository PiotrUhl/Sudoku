#ifndef inout_h
#define inout_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

//Lista do przechowywania histori rozwi¹zañ
struct List;
//wypisuje listê do strumienia stream
void listPrint(FILE* stream, struct List* list);

//Prosi u¿ytkownika o odpowiedŸ tak/nie
bool askBool(char* text, bool def);
//Prosi u¿ytkownika o wybór jednej z trzech opcji
char choose3(char* text, char* opt1, char* opt2, char* opt3, char nr1, char nr2, char nr3);
//ustawia kursor w miejscu cyfry o wspó³rzêdnych (x,y) na planszy sudoku
void cursorSudokuPos(int startRow, int x, int y);
//wypisuje planszê do pliku file
void fprintSudoku(FILE* file, char tab[9][9]);
//Importuje planszê z pliku
char importFromFile(char tab[9][9], char* path);
//pobiera planszê od u¿ytkownika lub z pliku, zwraca kod b³êdu
char input(char sudoku[9][9]);
//Wype³nia planszê sudoku z klawiatury
char inputConsole(char sudoku[9][9]);
//Pyta u¿ytkownica o zapis wynikowej planszy do pliku, o nawzwê pliku i zapisuje
char output(char sudoku[9][9]);
//zapisuje planszê sudoku do pliku path
char outputSave(char sudoku[9][9], char* path);
//Pyta u¿ytkownica o zapis histori rozwi¹zania do pliku i zapisuje
char outputHistory(struct List* list);
//zapisuje planszê sudoku do pliku path
char outputSaveHistory(struct List* list, char* path);

#endif
