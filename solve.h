#ifndef solve_h
#define solve_h

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//dopisuje do pliku z logami
void logApp(FILE* logFile, char* text, char sudoku[9][9]);
//zapisuje do logu aktualn¹ datê z du¿¹ dok³adnoœci¹
void logDate(FILE* logFile);
//Lista do przechowywania histori rozwi¹zañ
struct List;

//rozwi¹zuje sudoku z za³o¿eniem ze [y][x] = var
bool assume(char sudoku[9][9], int y, int x, int var, FILE* logFile, struct List* list);
//kopiuje tablice do tablicy
void boolTabCopy(bool* tabTo, const bool* tabFrom, int n);
//Sprawdza czy plansza jest poprawn¹, nie zawieraj¹c¹ b³êdów plansz¹ sudoku, 0 jeœli poprawna nierozwi¹zana, 1 jeœli poprawna rozwi¹zana
char checkSudoku(char sudoku[9][9], FILE* logFile);
//Pomocnicza dla checkSudoku(), sprawdza poprawnoœæ w wierszach
char checkSudokuRow(char sudoku[9][9], FILE* logFile);
//Pomocnicza dla checkSudoku(), sprawdza poprawnoœæ w kolumnach
char checkSudokuColumn(char sudoku[9][9], FILE* logFile);
//Pomocnicza dla checkSudoku(), sprawdza poprawnoœæ w kwadratacg
char checkSudokuSquare(char sudoku[9][9], FILE* logFile);
//Wype³nia tablicê wartoœciami false
bool* fillBoolTab(bool tab[], int n, bool var);
//Wype³nia luki w wierszu row które mo¿na jednoznacznie okreœliæ, zwraca iloœæ dokonanych zmian
char fillRow(char sudoku[9][9], int row, FILE* logFile, struct List* list);
//znajduje w tablicy wartoœæ var, zwraca indeks
int findBoolTab(bool tab[], int n, bool var);
//sprawdza czy w okreœlonej kolumnie wystêpuje cyfra var
bool findInColumn(char sudoku[9][9], int column, char var, FILE* logFile);
//sprawdza czy w okreœlonym wierszu wystêpuje cyfra var
bool findInRow(char sudoku[9][9], int row, char var, FILE* logFile);
//sprawdza czy w okreœlonym kwadracie (sx, sy)(numerowane od zera) wystêpuje cyfra var
bool findInSquare(char sudoku[9][9], int sx, int sy, char var, FILE* logFile);
//tworzy tablicê zawieraj¹c¹ informacje które cyfry s¹ w kolumnie, a których nie ma, zwraca iloœæ brakuj¹cych
char listColumn(char sudoku[9][9], int column, bool tab[], int n, FILE* logFile);
//tworzy tablicê zawieraj¹c¹ informacje które cyfry s¹ w wierszu, a których nie ma, zwraca iloœæ brakuj¹cych
char listRow(char sudoku[9][9], int row, bool tab[], int n, FILE* logFile);
//tworzy tablicê zawieraj¹c¹ informacje które cyfry s¹ w kwadracie, a których nie ma, zwraca iloœæ brakuj¹cych
char listSquare(char sudoku[9][9], int sx, int sy, bool tab[], int n, FILE* logFile);
//Rozwi¹zuje zadan¹ planszê, zwraca false w przypadku niepowodzenia
bool solve(char sudoku[9][9], FILE* logFile, struct List* list);
#endif
