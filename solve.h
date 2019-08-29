#ifndef solve_h
#define solve_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//dopisuje do pliku z logami
void logApp(FILE* logFile, char* text, char sudoku[9][9]);
//zapisuje do logu aktualn� dat� z du�� dok�adno�ci�
void logDate(FILE* logFile);
//Lista do przechowywania histori rozwi�za�
struct List;

//rozwi�zuje sudoku z za�o�eniem ze [y][x] = var
bool assume(char sudoku[9][9], int y, int x, int var, FILE* logFile, struct List* list);
//kopiuje tablice do tablicy
void boolTabCopy(bool* tabTo, const bool* tabFrom, int n);
//Sprawdza czy plansza jest poprawn�, nie zawieraj�c� b��d�w plansz� sudoku, 0 je�li poprawna nierozwi�zana, 1 je�li poprawna rozwi�zana
char checkSudoku(char sudoku[9][9], FILE* logFile);
//Pomocnicza dla checkSudoku(), sprawdza poprawno�� w wierszach
char checkSudokuRow(char sudoku[9][9], FILE* logFile);
//Pomocnicza dla checkSudoku(), sprawdza poprawno�� w kolumnach
char checkSudokuColumn(char sudoku[9][9], FILE* logFile);
//Pomocnicza dla checkSudoku(), sprawdza poprawno�� w kwadratacg
char checkSudokuSquare(char sudoku[9][9], FILE* logFile);
//Wype�nia tablic� warto�ciami false
bool* fillBoolTab(bool tab[], int n, bool var);
//Wype�nia luki w wierszu row kt�re mo�na jednoznacznie okre�li�, zwraca ilo�� dokonanych zmian
char fillRow(char sudoku[9][9], int row, FILE* logFile, struct List* list);
//znajduje w tablicy warto�� var, zwraca indeks
int findBoolTab(bool tab[], int n, bool var);
//sprawdza czy w okre�lonej kolumnie wyst�puje cyfra var
bool findInColumn(char sudoku[9][9], int column, char var, FILE* logFile);
//sprawdza czy w okre�lonym wierszu wyst�puje cyfra var
bool findInRow(char sudoku[9][9], int row, char var, FILE* logFile);
//sprawdza czy w okre�lonym kwadracie (sx, sy)(numerowane od zera) wyst�puje cyfra var
bool findInSquare(char sudoku[9][9], int sx, int sy, char var, FILE* logFile);
//tworzy tablic� zawieraj�c� informacje kt�re cyfry s� w kolumnie, a kt�rych nie ma, zwraca ilo�� brakuj�cych
char listColumn(char sudoku[9][9], int column, bool tab[], int n, FILE* logFile);
//tworzy tablic� zawieraj�c� informacje kt�re cyfry s� w wierszu, a kt�rych nie ma, zwraca ilo�� brakuj�cych
char listRow(char sudoku[9][9], int row, bool tab[], int n, FILE* logFile);
//tworzy tablic� zawieraj�c� informacje kt�re cyfry s� w kwadracie, a kt�rych nie ma, zwraca ilo�� brakuj�cych
char listSquare(char sudoku[9][9], int sx, int sy, bool tab[], int n, FILE* logFile);
//Rozwi�zuje zadan� plansz�, zwraca false w przypadku niepowodzenia
bool solve(char sudoku[9][9], FILE* logFile, struct List* list);
#endif
