#ifndef history_h
#define history_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Wêze³ podstawowy drzewa, przechowuj¹cy dane
typedef struct WezelD {
    char data[9][9];
    struct WezelD* next;
    struct WezelP* up;
    struct WezelP* down;
} WezelD;
//Wêze³ listy jednokierunkowej przechowuj¹cej wskaŸniki na WezelD
typedef struct WezelP {
    struct WezelD* data;
    struct WezelP* next;
    struct WezelD* up;
    int level;
} WezelP;
//Lista do przechowywania histori rozwi¹zañ
typedef struct List {
    WezelD* start;
    WezelD* end;
} List;

//wypisuje planszê do pliku file, z poziomem zagnie¿d¿enia równym level
void fprintSudokuLeveled(FILE* file, char tab[9][9], int level);
//inicjalizuje now¹ listê
List* listInit(char sudoku[9][9]);
//dodaje element do listy
void listAddNode(List* list, char sudoku[9][9]);
//dodaje rozga³êzienie do listy
void listAddBranch(List* list, char sudoku[9][9]);
//przesuwa koniec listy o poziom wy¿ej
void listUp(List* list);
//wypisuje ga³¹Ÿ listy do strumienia stream, zwraca wskaŸnik na ostatni element
WezelD* listPrintBranch(FILE* stream, WezelD* glowa, int level);
//wypisuje drzewo do strumienia stream
void listPrintTree(FILE* stream, WezelD* glowaD, int level);
//wypisuje listê do strumienia stream
void listPrint(FILE* stream, List* list);
//usuwa z pamiêci wêze³ wraz z potomkami
void listDeleteTree(WezelD* glowaD);
//usuwa ca³¹ listê z pamiêci, zwraca NULL
List* listDelete(List* list);

//Importuje planszê z pliku
char importFromFile(char tab[9][9], char* path);
#endif
