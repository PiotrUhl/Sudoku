#ifndef history_h
#define history_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//W�ze� podstawowy drzewa, przechowuj�cy dane
typedef struct WezelD {
    char data[9][9];
    struct WezelD* next;
    struct WezelP* up;
    struct WezelP* down;
} WezelD;
//W�ze� listy jednokierunkowej przechowuj�cej wska�niki na WezelD
typedef struct WezelP {
    struct WezelD* data;
    struct WezelP* next;
    struct WezelD* up;
    int level;
} WezelP;
//Lista do przechowywania histori rozwi�za�
typedef struct List {
    WezelD* start;
    WezelD* end;
} List;

//wypisuje plansz� do pliku file, z poziomem zagnie�d�enia r�wnym level
void fprintSudokuLeveled(FILE* file, char tab[9][9], int level);
//inicjalizuje now� list�
List* listInit(char sudoku[9][9]);
//dodaje element do listy
void listAddNode(List* list, char sudoku[9][9]);
//dodaje rozga��zienie do listy
void listAddBranch(List* list, char sudoku[9][9]);
//przesuwa koniec listy o poziom wy�ej
void listUp(List* list);
//wypisuje ga��� listy do strumienia stream, zwraca wska�nik na ostatni element
WezelD* listPrintBranch(FILE* stream, WezelD* glowa, int level);
//wypisuje drzewo do strumienia stream
void listPrintTree(FILE* stream, WezelD* glowaD, int level);
//wypisuje list� do strumienia stream
void listPrint(FILE* stream, List* list);
//usuwa z pami�ci w�ze� wraz z potomkami
void listDeleteTree(WezelD* glowaD);
//usuwa ca�� list� z pami�ci, zwraca NULL
List* listDelete(List* list);

//Importuje plansz� z pliku
char importFromFile(char tab[9][9], char* path);
#endif
