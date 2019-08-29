//G³ówna czêœæ programu
#include "main.h"

int main(int argc, char **argv) {
    struct Arguments args = readArguments(argc, argv);
    char tmp;
	char sudoku[9][9] = {0};
	if (args.defSource == true) {
        if (args.sourceFile == NULL) {
            printf("Po parametrze \"/i\" nalezy podac sciezke do wejsciowego pliku z plansza sudoku!");
            return -110;
        }
        tmp = importFromFile(sudoku, args.sourceFile);
	}
	else {
        tmp = input(sudoku); //pobranie danych od u¿ytkownika
	}
	if (tmp != 0) {
		if (tmp == -100)
			printf("Przerwane na zyczenie uzytkownika\n");
		if (tmp > 0)
			printf("Nie znaleziono pliku, badz plik nie zawiera poprawnej planszy sudoku!\n");
        printf("Nacisnij dowolny klawisz by zakonczyc dzialanie programu...");
		_getch();
		return tmp;
	}
	if (checkSudoku(sudoku, NULL) != 0) { //kontrola poprawnoœci
		printf("To nie jest poprawna plansza!\n");
        if (argc == 1) {
            printf("Nacisnij dowolny klawisz by zakonczyc dzialanie programu...");
            _getch();
        }
		return 10;
	}
	printf("Plansza do rozwiazania:\n");
	fprintSudoku(stdout, sudoku); //wypisuje sudoku na ekran
	FILE* logFile = prepareLog("log.txt"); //tworzy plik do przechowywania logów
	struct List* list = listInit(sudoku); //tworzy listê do przechowywania histori rozwi¹zywania planszy
	printf("Rozwiazywanie...\n");
	solve(sudoku, logFile, list); //rozwi¹zuje zadane sudoku
	printf("Rozwiazana plansza: \n");
	fprintSudoku(stdout, sudoku); //wypisuje rozwi¹zane sudoku na ekran
	fclose(logFile); //zamyka plik z logami
	if (args.defOutput == true) {
        if (args.outputFile != NULL) {
            if (outputSave(sudoku, args.outputFile) == -1)
                printf("Nie mozna otworzyc pliku \"%s\"", args.outputFile);
            else
                printf("Zapisano rezultat do pliku \"%s\"\n", args.outputFile);
        }
	}
	else
        output(sudoku); //opcjonalnie zapisuje wynik do pliku
	if (args.defHistory == true) {
        if (args.historyFile != NULL) {
            if (outputSaveHistory(list, args.historyFile) == -1)
                printf("Nie mozna otworzyc pliku \"%s\"", args.historyFile);
            else
                printf("Zapisano historie do pliku \"%s\"\n", args.historyFile);
        }
	}
	else
        outputHistory(list); //opcjonalnie zapisuje historie rozwi¹zywania do pliku
	list = listDelete(list);
//	printf("ALLOCATED_BYTES = %d\n", ALLOCATED_BYTES); //memtest
//	printf("ALLOCATED_COUNT = %d\n", ALLOCATED_COUNT); //memtest
    if (argc == 1) {
        printf("Nacisnij dowolny klawisz by zakonczyc dzialanie programu...");
        _getch();
    }
	return 0;
}
