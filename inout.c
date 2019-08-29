#include "inout.h"

//Prosi u¿ytkownika o wybór jednej z trzech opcji
char choose3(char* text, char* opt1, char* opt2, char* opt3, char nr1, char nr2, char nr3) {
	while (true) {
		printf("%s [%d, %d, %d]\n", text, nr1, nr2, nr3);
		printf("%d. %s\n", nr1, opt1);
		printf("%d. %s\n", nr2, opt2);
		printf("%d. %s\n", nr3, opt3);
		int ret;
		fflush(stdin);
		scanf("%d", &ret);
		if (ret == nr1 || ret == nr2 || ret == nr3)
			return (char)ret;
	}
}

//pobiera planszê od u¿ytkownika lub z pliku, zwraca kod b³êdu
char input(char sudoku[9][9]) {
	char choose = choose3("Wybierz sposob wprowadzania planszy:", "Z klawiatury", "Z pliku", "Anuluj", 1, 2, 0);
	if (choose == 0)
		return -100;
	if (choose == 1) {
		return inputConsole(sudoku);
	}
	if (choose == 2) {
		char path[FILENAME_MAX];
		printf("Wpisz nazwe pliku zawierajacego plansze do rozwiazania: ");
		scanf("%s", path);
		return importFromFile(sudoku, path);
	}
	return 127;
}

//Prosi u¿ytkownika o odpowiedŸ tak/nie
bool askBool(char* text, bool def) {
	char ret;
	printf("%s", text);
	fflush(stdin);
	scanf("%c", &ret);
	switch (ret) {
	case 'y':
	case 'Y':
	case 't':
	case 'T':
	case '1':
		return true;
	case 'n':
	case 'N':
	case '0':
		return false;
	default:
		return def;
	}
}

//Pyta u¿ytkownica o zapis wynikowej planszy do pliku, o nawzwê pliku i zapisuje
char output(char sudoku[9][9]) {
	if (askBool("Czy chcesz zapisac wynikowa plansze do pliku? [t/N] ", false) == true) {
		char path[FILENAME_MAX];
		printf("Wpisz nazwe pliku do ktorego chcesz zapisac wynikowa plansze: ");
		scanf("%s", path);
		if (outputSave(sudoku, path) == -1) {
            printf("Nie mozna otworzyc pliku \"%s\"", path);
            return -1;
		}
        else
            printf("Zapisano do pliku \"%s\"\n", path);
	}
	return 0;
}

//zapisuje planszê sudoku do pliku path
char outputSave(char sudoku[9][9], char* path) {
    FILE* plik = fopen(path, "w");
    if (plik == NULL) {
        return -1;
    }
    fprintSudoku(plik, sudoku);
    fclose(plik);
    return 0;
}

//Pyta u¿ytkownica o zapis histori rozwi¹zania do pliku i zapisuje
char outputHistory(struct List* list) {
	if (askBool("Czy chcesz historie rozwiazywania planszy do pliku? [t/N] ", false) == true) {
		char path[FILENAME_MAX];
		printf("Wpisz nazwe pliku do ktorego chcesz historie rozwiazywania planszy: ");
		scanf("%s", path);
        if (outputSaveHistory(list, path) == -1) {
            printf("Nie mozna otworzyc pliku \"%s\"", path);
            return -1;
		}
        else
            printf("Zapisano do pliku \"%s\"\n", path);
	}
	return 0;
}

//zapisuje planszê sudoku do pliku path
char outputSaveHistory(struct List* list, char* path) {
    FILE* plik = fopen(path, "w");
    if (plik == NULL) {
        return -1;
    }
    listPrint(plik, list);
    fclose(plik);
    return 0;
}

/*void out(char* prefix, char sudoku[9][9], int i, int j) {
;
}*/

//ustawia kursor w miejscu cyfry o wspó³rzêdnych (x,y) na planszy sudoku
void cursorSudokuPos(int startRow, int x, int y) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = startRow + 1 + x + x / 3;
	pos.X = 2 * (1 + y + y / 3);
	SetConsoleCursorPosition(console, pos);
}

//Wype³nia planszê sudoku z klawaitury
char inputConsole(char sudoku[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			system("cls");
			printf("Wypelnij plansze i zatwierdz klawiszem enter: \n");
			fprintSudoku(stdout, sudoku);
			cursorSudokuPos(1, i, j);
			unsigned char chr = getch();
			if (chr == 224) {
				switch (getch()) {
				case 75: //left
					if (j > 0)
						j--;
					else {
						i--;
						j = 8;
					}
					j--;
					break;
				case 72: //up
					if (i > 0)
						i--;
					j--;
					break;
				case 77: //right
					if (i == 8 && j == 8)
						j--;
					break;
				case 80: //down
					if (i < 8)
						i++;
					j--;
					break;
				}
			}
			if (chr == 27) { //esc
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD pos = { 0,14 };
				SetConsoleCursorPosition(console, pos); //ustawia kursor za plansz¹
				return -100;
			}
			if (chr == 13) { //enter
				HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD pos = { 0,14 };
				SetConsoleCursorPosition(console, pos); //ustawia kursor za plansz¹
				return 0;
			}
			if (chr > '0' && chr <= '9')
				sudoku[i][j] = chr - '0';
			else if (chr == ' ' || chr == '0')
				sudoku[i][j] = 0;
			if (i == 8 && j == 8) {
				i = 0;
				j = -1;
			}
		}
	}
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0,14 };
	SetConsoleCursorPosition(console, pos); //ustawia kursor za plansz¹
	return 0;
}

//wypisuje planszê do pliku file
void fprintSudoku(FILE* file, char tab[9][9]) {
	for (int i = 0; i < 9; i++) {
		if (!(i % 3))
			fprintf(file, "+-------+-------+-------+\n");
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
		fprintf(file, "\n");
	}
	fprintf(file, "+-------+-------+-------+\n");
}

//Importuje planszê z pliku
char importFromFile(char tab[9][9], char* path) {
	FILE* file = fopen(path, "r");
	if (file != NULL) {
		for (char i = 0; i < 9; i++) {
			for (char j = 0; j < 9; j++) {
				int x = getc(file);
				//printf("x = %c\n", x);
				if (x == ' ') {
					i--;
					continue;
				}
				if (x == EOF) {
					fclose(file);
					return 3; // 3 - to nie jest prawid³owa plansza sudoku (b³¹d EOF w wierszu)
				}
				if ((x < '0' || x > '9') && x != '_') {
					fclose(file);
					return 2; // 2 - to nie jest prawdid³owa plansza sudoku (niew³aœciwy znak w wierszu)
				}
				if (x == '0' || x == '_')
					tab[i][j] = 0;
				else
					tab[i][j] = (char)(x - '0');
			}
			if (i != 8) {
				int x = getc(file);
				if (x == EOF) {
					fclose(file);
					return 5; // 5 - to nie jest prawid³owa plansza sudoku (b³¹d EOF miêdzy wierszami)
				}
				if (x != '\n' && x != '\r' && x != '\t') {
					fclose(file);
					return 4; // 4 - to nie jest prawid³owa plansza sudoku (niew³aœciwy znak miêdzy wierszami)
				}
			}
		}
		fclose(file);
		return 0;
	}
	else
		return 1; // 1 - nie mo¿na otworzyæ pliku
}
