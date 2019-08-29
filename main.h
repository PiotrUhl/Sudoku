#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

//size_t ALLOCATED_BYTES; //memtest
//size_t ALLOCATED_COUNT; //memtest

//Informacje podane jako parametry uruchomienia programu
struct Arguments {
    bool defSource; //czy ustawiono Ÿród³o danych wejœciowych
    char* sourceFile; //œcie¿ka do pliku z danymi wejœciowymi, b¹dŸ puste je¿eli wprowadzane z klawiatury
    bool defOutput; //czy ustawiono wyjœcie danych
    char* outputFile; //œcie¿ka do pliku wyjœciowego, je¿eli puste pomija zapis
    bool defHistory; //czy ustawiono zapis historii rozwi¹zania
    char* historyFile; //œcie¿ka do pliku na historie, je¿eli puste pomija zapis
};
//Wype³nia strukturê arguments parametrami uruchomienia programu
struct Arguments readArguments(int argc, char** argv);

//pobiera planszê od u¿ytkownika lub z pliku, zwraca kod b³êdu
char input(char sudoku[9][9]);
//Sprawdza czy plansza jest poprawn¹, nie zawieraj¹c¹ b³êdów plansz¹ sudoku, 0 jeœli poprawna nierozwi¹zana, 1 jeœli poprawna rozwi¹zana
char checkSudoku(char sudoku[9][9], FILE* logFile);
//wypisuje planszê do pliku file
void fprintSudoku(FILE* file, char tab[9][9]);
//przygotowuje plik z logami
FILE* prepareLog(char* path);
//Importuje planszê z pliku
char importFromFile(char tab[9][9], char* path);
//Wêze³ podstawowy drzewa, przechowuj¹cy dane
struct WezelD;
//Wêze³ listy jednokierunkowej przechowuj¹cej wskaŸniki na WezelD
struct WezelP;
//Lista do przechowywania histori rozwi¹zañ
struct List;
//inicjalizuje now¹ listê
struct List* listInit(char sudoku[9][9]);
//wypisuje listê do strumienia stream
void listPrint(FILE* stream, struct List* list);
//usuwa ca³¹ listê z pamiêci, zwraca NULL
struct List* listDelete(struct List* list);
//Rozwi¹zuje zadan¹ planszê, zwraca false w przypadku niepowodzenia
bool solve(char sudoku[9][9], FILE* logFile, struct List* list);
//Pyta u¿ytkownica o zapis wynikowej planszy do pliku, o nawzwê pliku i zapisuje
char output(char sudoku[9][9]);
//zapisuje planszê sudoku do pliku path
char outputSave(char sudoku[9][9], char* path);
//Pyta u¿ytkownica o zapis histori rozwi¹zania do pliku i zapisuje
char outputHistory(struct List* list);
//zapisuje planszê sudoku do pliku path
char outputSaveHistory(struct List* list, char* path);
#endif
