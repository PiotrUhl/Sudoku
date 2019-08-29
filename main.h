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
    bool defSource; //czy ustawiono �r�d�o danych wej�ciowych
    char* sourceFile; //�cie�ka do pliku z danymi wej�ciowymi, b�d� puste je�eli wprowadzane z klawiatury
    bool defOutput; //czy ustawiono wyj�cie danych
    char* outputFile; //�cie�ka do pliku wyj�ciowego, je�eli puste pomija zapis
    bool defHistory; //czy ustawiono zapis historii rozwi�zania
    char* historyFile; //�cie�ka do pliku na historie, je�eli puste pomija zapis
};
//Wype�nia struktur� arguments parametrami uruchomienia programu
struct Arguments readArguments(int argc, char** argv);

//pobiera plansz� od u�ytkownika lub z pliku, zwraca kod b��du
char input(char sudoku[9][9]);
//Sprawdza czy plansza jest poprawn�, nie zawieraj�c� b��d�w plansz� sudoku, 0 je�li poprawna nierozwi�zana, 1 je�li poprawna rozwi�zana
char checkSudoku(char sudoku[9][9], FILE* logFile);
//wypisuje plansz� do pliku file
void fprintSudoku(FILE* file, char tab[9][9]);
//przygotowuje plik z logami
FILE* prepareLog(char* path);
//Importuje plansz� z pliku
char importFromFile(char tab[9][9], char* path);
//W�ze� podstawowy drzewa, przechowuj�cy dane
struct WezelD;
//W�ze� listy jednokierunkowej przechowuj�cej wska�niki na WezelD
struct WezelP;
//Lista do przechowywania histori rozwi�za�
struct List;
//inicjalizuje now� list�
struct List* listInit(char sudoku[9][9]);
//wypisuje list� do strumienia stream
void listPrint(FILE* stream, struct List* list);
//usuwa ca�� list� z pami�ci, zwraca NULL
struct List* listDelete(struct List* list);
//Rozwi�zuje zadan� plansz�, zwraca false w przypadku niepowodzenia
bool solve(char sudoku[9][9], FILE* logFile, struct List* list);
//Pyta u�ytkownica o zapis wynikowej planszy do pliku, o nawzw� pliku i zapisuje
char output(char sudoku[9][9]);
//zapisuje plansz� sudoku do pliku path
char outputSave(char sudoku[9][9], char* path);
//Pyta u�ytkownica o zapis histori rozwi�zania do pliku i zapisuje
char outputHistory(struct List* list);
//zapisuje plansz� sudoku do pliku path
char outputSaveHistory(struct List* list, char* path);
#endif
