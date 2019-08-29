#include "history.h"

//size_t ALLOCATED_BYTES = 0; //memtest
//size_t ALLOCATED_COUNT = 0; //memtest

//wypisuje planszê do pliku file, z poziomem zagnie¿d¿enia równym level
void fprintSudokuLeveled(FILE* file, char tab[9][9], int level) {
	for (int i = 0; i < 9; i++) {
        for (int l = 0; l < level; l++)
            fprintf(file, "    ");
		if (!(i % 3)) {
			fprintf(file, "+-------+-------+-------+\n");
			for (int l = 0; l < level; l++)
                fprintf(file, "    ");
		}
		for (int j = 0; j < 10; j++) {
			if (j == 9)
				fprintf(file, "| ");
			else {
				if (!(j % 3))
					fprintf(file, "| ");
				if (tab[i][i] > 9 || tab[i][j] < 1)
					fprintf(file, "_ ");
				else
					fprintf(file, "%hd ", (short int)tab[i][j]);
			}
		}
        for (int l = 0; l < level; l++)
            fprintf(file, "    ");
		fprintf(file, "\n");
	}
    for (int l = 0; l < level; l++)
        fprintf(file, "    ");
	fprintf(file, "+-------+-------+-------+\n");
}

//inicjalizuje now¹ listê
List* listInit(char sudoku[9][9]) {
    List* ret = (List*)malloc(sizeof(List));
//    ALLOCATED_BYTES += sizeof(List); //memtest
//    ALLOCATED_COUNT++; //memtest
    if (sudoku == NULL)
        ret->start = ret->end = NULL;
    else
        listAddNode(ret, sudoku);
    return ret;
}

//dodaje element do listy
void listAddNode(List* list, char sudoku[9][9]) {
    WezelD* nowy = (WezelD*)malloc(sizeof(WezelD));
//    ALLOCATED_BYTES += sizeof(WezelD); //memtest
//    ALLOCATED_COUNT++; //memtest
    memcpy(nowy->data, sudoku, sizeof(nowy->data));
    nowy->next = NULL;
    nowy->down = NULL;
    if (list->start == NULL) {
        nowy->up = NULL;
        list->start = nowy;
        list->end = nowy;
    }
    else {
        nowy->up = list->end->up;
        list->end->next = nowy;
        list->end = nowy;
    }
}

//dodaje rozga³êzienie do listy
void listAddBranch(List* list, char sudoku[9][9]) {
    WezelP* nowy = (WezelP*)malloc(sizeof(WezelP));
//    ALLOCATED_BYTES += sizeof(WezelP); //memtest
//    ALLOCATED_COUNT++; //memtest
    nowy->data = (WezelD*)malloc(sizeof(WezelD));
//    ALLOCATED_BYTES += sizeof(WezelD); //memtest
//    ALLOCATED_COUNT++; //memtest
    memcpy(nowy->data->data, sudoku, sizeof(nowy->data->data));
    nowy->data->next = nowy->data->down = NULL;
    nowy->data->up = nowy;
    nowy->next = NULL;
    nowy->up = list->end;
    if (list->end->up == NULL)
        nowy->level = 1;
    else
        nowy->level = (list->end->up->level) + 1;
    if (list->end->down == NULL)
        list->end->down = nowy;
    else {
        WezelP* glowa = list->end->down;
        while (glowa->next != NULL)
            glowa = glowa->next;
        glowa->next = nowy;
    }
    list->end = nowy->data;
}

//przesuwa koniec listy o poziom wy¿ej
void listUp(List* list) {
    list->end = list->end->up->up;
}

//wypisuje ga³¹Ÿ listy do strumienia stream, zwraca wskaŸnik na ostatni element
WezelD* listPrintBranch(FILE* stream, WezelD* glowa, int level) {
    while (glowa->next != NULL) {
        fprintSudokuLeveled(stream, glowa->data, level);
        glowa = glowa->next;
    }
    fprintSudokuLeveled(stream, glowa->data, level);
    return glowa;
}

//wypisuje drzewo do strumienia stream
void listPrintTree(FILE* stream, WezelD* glowaD, int level) {
    glowaD = listPrintBranch(stream, glowaD, level);
    if (glowaD->down == NULL)
        return;
    WezelP* glowaP = glowaD->down;
    while (glowaP != NULL) {
        listPrintTree(stream, glowaP->data, level+1);
        glowaP = glowaP->next;
        if (glowaP != NULL)
            fprintSudokuLeveled(stream, glowaD->data, level);
    }
}

//wypisuje listê do strumienia stream
void listPrint(FILE* stream, List* list) {
    listPrintTree(stream, list->start, 0);
}
//usuwa z pamiêci wêze³ wraz z potomkami
void listDeleteTree(WezelD* glowaD) {
    WezelD* nastD;
    while (glowaD->next != NULL) {
        nastD = glowaD->next;
        free(glowaD);
//        ALLOCATED_BYTES -= sizeof(WezelD); //memtest
//        ALLOCATED_COUNT--; //memtest
        glowaD = nastD;
    }
    if (glowaD->down == NULL) {
        free(glowaD);
//        ALLOCATED_BYTES -= sizeof(WezelD); //memtest
//        ALLOCATED_COUNT--; //memtest
        return;
    }
    else {
        WezelP* glowaP = glowaD->down;
        WezelP* nastP;
        while (glowaP != NULL) {
            nastP = glowaP->next;
            listDeleteTree(glowaP->data);
            free(glowaP);
//            ALLOCATED_BYTES -= sizeof(WezelP); //memtest
//            ALLOCATED_COUNT--; //memtest
            glowaP = nastP;
        }
        free(glowaD);
//        ALLOCATED_BYTES -= sizeof(WezelD); //memtest
//        ALLOCATED_COUNT--; //memtest
    }
}

//usuwa ca³¹ listê z pamiêci, zwraca NULL
List* listDelete(List* list) {
    listDeleteTree(list->start);
    free(list);
//    ALLOCATED_BYTES -= sizeof(List); //memtest
//    ALLOCATED_COUNT--; //memtest
    return NULL;
}
