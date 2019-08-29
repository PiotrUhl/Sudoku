#include "solve.h"

//Wype³nia tablicê wartoœciami var
bool* fillBoolTab(bool tab[], int n, bool var) {
	for (int i = 0; i < 9; i++) {
		tab[i] = var;
	}
	return tab;
}

//Sprawdza czy plansza jest poprawn¹, nie zawieraj¹c¹ b³êdów plansz¹ sudoku, 0 jeœli poprawna nierozwi¹zana, 1 jeœli poprawna rozwi¹zana
char checkSudoku(char sudoku[9][9], FILE* logFile) {
	bool done = true; //Czy plansza jest rozwi¹zana
	logDate(logFile);
	logApp(logFile, "checkSudoku:", NULL);
	char tmp = checkSudokuRow(sudoku, logFile);
	if (tmp == 1)
        done = false;
    else if (tmp < 0)
        return tmp;
        // -2 - to nie jest plansza sudoku
        // -11 - plansza b³ednie rozwi¹zana (wiersze)
    if (checkSudokuColumn(sudoku, logFile) == -12)
        return -12; // -12 - plansza b³êdnie rozwi¹zana (kolumny)
    if (checkSudokuSquare(sudoku, logFile) == -13)
        return -13; // -13 - plansza b³êdnie rozwi¹zana (kwadraty)
	if (done == true) {
		logApp(logFile, " plansza poprawna, rozwiazana\n", NULL);
		return 1; //poprawna plansza, poprawnie rozwi¹zanA
	}
	logApp(logFile, " plansza poprawna, nierozwiazana\n", NULL);
	return 0; //poprawna plansza, nierozwi¹zana
}

//Pomocnicza dla checkSudoku(), sprawdza poprawnoœæ w wierszach
char checkSudokuRow(char sudoku[9][9], FILE* logFile) {
    bool tab[9]; //Tablica do przechowywania informacji czy odnaleziono dan¹ cyfrê
    bool done = true;
	for (int i = 0; i < 9; i++) {
		fillBoolTab(tab, 9, false);
		for (int j = 0; j < 9; j++) {
			if (sudoku[i][j] != '_' && (sudoku[i][j] < 0 || sudoku[i][j] > 9)) {
                //{log
                logDate(logFile);
                char logStr[54]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
                snprintf(logStr, 54, " err2  (to nie jest plansza sudoku) sudoku[%d][%d] = %d\n", i, j, sudoku[i][j]);
                logApp(logFile, logStr, sudoku);
                //}
				return -2; // -2 - to nie jest plansza sudoku
			}
			if (sudoku[i][j] > 0 && sudoku[i][j] <= 9) {
				if (tab[sudoku[i][j] - 1] == true) {
                    //{ log
                    logDate(logFile);
                    char logStr[67]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
                    snprintf(logStr, 67, " err11 (plansza b³êdnie rozwi¹zana - wiersze) sudoku[%d][%d] = %d\n", i, j, sudoku[i][j]);
                    logApp(logFile, logStr, sudoku);
                    //}
					return -11; // -11 - plansza b³ednie rozwi¹zana (wiersze)
				}
				tab[sudoku[i][j] - 1] = true;
			}
			else
				done = false;
		}
	}
	if (done == false)
        return 1;
    return 0;
}

//Pomocnicza dla checkSudoku(), sprawdza poprawnoœæ w kolumnach
char checkSudokuColumn(char sudoku[9][9], FILE* logFile) {
    bool tab[9]; //Tablica do przechowywania informacji czy odnaleziono dan¹ cyfrê
	for (int i = 0; i < 9; i++) {
		fillBoolTab(tab, 9, false);
		for (int j = 0; j < 9; j++) {
			if (sudoku[j][i] > 0 && sudoku[j][i] <= 9) {
				if (tab[sudoku[j][i] - 1] == true) {
                    //{ log
                    logDate(logFile);
                    char logStr[67]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
                    snprintf(logStr, 67, " err12 (plansza b³êdnie rozwi¹zana - kolumny) sudoku[%d][%d] = %d\n", i, j, sudoku[i][j]);
                    logApp(logFile, logStr, sudoku);
                    //}
					return -12; // -12 - plansza b³êdnie rozwi¹zana (kolumny)
				}
				tab[sudoku[j][i] - 1] = true;
			}
		}
	}
	return 0;
}

//Pomocnicza dla checkSudoku(), sprawdza poprawnoœæ w kwadratach
char checkSudokuSquare(char sudoku[9][9], FILE* logFile) {
    bool tab[9]; //Tablica do przechowywania informacji czy odnaleziono dan¹ cyfrê
	for (int ii = 0; ii < 3; ii++) {
		for (int ij = 0; ij < 3; ij++) {
			fillBoolTab(tab, 9, false);
			for (int ji = 0; ji < 3; ji++) {
				for (int jj = 0; jj < 3; jj++) {
					if (sudoku[ji + 3 * ii][jj + 3 * ij] > 0 && sudoku[ji + 3 * ii][jj + 3 * ij] <= 9) {
						if (tab[sudoku[ji + 3 * ii][jj + 3 * ij] - 1] == true) {
                            //{ log
                            logDate(logFile);
                            char logStr[76]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
                            snprintf(logStr, 76, " err13 (plansza b³êdnie rozwi¹zana - kwadraty) sudoku[%d+3*%d][%d+3*%d] = %d\n", ji, ii, jj, ij, sudoku[ji + 3 * ii][jj + 3 * ij]);
                            logApp(logFile, logStr, sudoku);
                            //}
							return -13; // -13 - plansza b³êdnie rozwi¹zana (kwadraty)
						}
						tab[sudoku[ji + 3 * ii][jj + 3 * ij] - 1] = true;
					}
				}
			}
		}
	}
	return 0;
}

//tworzy tablicê zawieraj¹c¹ informacje które cyfry s¹ w wierszu, a których nie ma, zwraca iloœæ brakuj¹cych
char listRow(char sudoku[9][9], int row, bool tab[], int n, FILE* logFile) {
	char ilosc = 9;
	for (int i = 0; i < n; i++) {
		if (sudoku[row][i] > 0 && sudoku[row][i] <= 9) {
			tab[sudoku[row][i] - 1] = true;
			ilosc--;
		}
	}
	//log
	char logStr[43]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 43, "listRow(): wiersz %d, ilosc: %d {%d%d%d%d%d%d%d%d%d}\n", row, ilosc, tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
	logApp(logFile, logStr, NULL);
	//endlog
	return ilosc;
}
//tworzy tablicê zawieraj¹c¹ informacje które cyfry s¹ w kolumnie, a których nie ma, zwraca iloœæ brakuj¹cych
char listColumn(char sudoku[9][9], int column, bool tab[], int n, FILE* logFile) {
	char ilosc = 9;
	for (int i = 0; i < n; i++) {
		if (sudoku[i][column] > 0 && sudoku[i][column] <= 9) {
			tab[sudoku[i][column] - 1] = true;
			ilosc--;
		}
	}
	//log
	char logStr[47]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 47, "listColumn(): kolumna %d, ilosc: %d {%d%d%d%d%d%d%d%d%d}\n", column, ilosc, tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
	logApp(logFile, logStr, NULL);
	//endlog
	return ilosc;
}

//tworzy tablicê zawieraj¹c¹ informacje które cyfry s¹ w kwadracie, a których nie ma, zwraca iloœæ brakuj¹cych
char listSquare(char sudoku[9][9], int sx, int sy, bool tab[], int n, FILE* logFile) {
	char ilosc = 9;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (sudoku[i + 3 * sy][j + 3 * sx] > 0 && sudoku[i + 3 * sy][j + 3 * sx] <= 9) {
				tab[sudoku[i + 3 * sy][j + 3 * sx] - 1] = true;
				ilosc--;
			}
		}
	}
	//log
	char logStr[54]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 54, "listSquare(): kwadrat [%d][%d], ilosc: %d {%d%d%d%d%d%d%d%d%d}\n", sy, sx, ilosc, tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
	logApp(logFile, logStr, NULL);
	//endlog
	return ilosc;
}

//sprawdza czy w okreœlonym wierszu wystêpuje cyfra var
bool findInRow(char sudoku[9][9], int row, char var, FILE* logFile) {
	//log
	char logStr[36]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 36, "findInRow(): wiersz %d, szukana: %d, ", row, var);
	logApp(logFile, logStr, NULL);
	//endLog
	for (int i = 0; i < 9; i++) {
		if (sudoku[row][i] == var) {
			logApp(logFile, "result: true\n", NULL);
			return true;
		}
	}
	logApp(logFile, "result: false\n", NULL);
	return false;
}

//sprawdza czy w okreœlonej kolumnie wystêpuje cyfra var
bool findInColumn(char sudoku[9][9], int column, char var, FILE* logFile) {
	//log
	char logStr[40]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 40, "findInColumn(): kolumna %d, szukana: %d, ", column, var);
	logApp(logFile, logStr, NULL);
	//endLog
	for (int i = 0; i < 9; i++) {
		if (sudoku[i][column] == var) {
			logApp(logFile, "result: true\n", NULL);
			return true;
		}
	}
	logApp(logFile, "result: false\n", NULL);
	return false;
}

//sprawdza czy w okreœlonym kwadracie (sx, sy)(numerowane od zera) wystêpuje cyfra var
bool findInSquare(char sudoku[9][9], int sx, int sy, char var, FILE* logFile) {
	//log
	char logStr[46]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 46, "findInSquare(): kwadrat [%d][%d], szukana: %d, ", sy, sx, var);
	logApp(logFile, logStr, NULL);
	//endLog
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (sudoku[i + 3 * sy][j + 3 * sx] == var) {
				logApp(logFile, "result: true\n", NULL);
				return true;
			}
		}
	}
	logApp(logFile, "result: false\n", NULL);
	return false;
}

//znajduje w tablicy wartoœæ var, zwraca indeks
int findBoolTab(bool tab[], int n, bool var) {
	for (int i = 0; i < n; i++) {
		if (tab[i] == var) {
			return i;
		}
	}
	return -1;
}

//kopiuje tablice do tablicy
void boolTabCopy(bool* tabTo, const bool* tabFrom, int n) {
	for (int i = 0; i < n; i++) {
		tabTo[i] = tabFrom[i];
	}
}

//Wype³nia luki w wierszu row które mo¿na jednoznacznie okreœliæ, zwraca iloœæ dokonanych zmian
char fillRow(char sudoku[9][9], int row, FILE* logFile, struct List* list) {
	//log
	char logStr[86]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 21, "fillRow(): wiersz %d\n", row);
	logApp(logFile, logStr, sudoku);
	//endLog
	bool done = true; //czy rz¹d rozwi¹zany w ca³oœci //nieu¿ywana
	bool did = true; //czy podczas przejœcia pêtli dokonano jakiejœ zmiany
	char changes = 0; //iloœæ dokonanych zmian
	bool is[9]; //cyfry które s¹ uzupe³nionefillRow
	fillBoolTab(is, 9, false);
	while (did) {
		did = false;
		char miss = listRow(sudoku, row, is, 9, logFile); //iloœc cyfr brakuj¹cych
		//je¿eli jest tylko jedno puste pole
		if (miss == 1) {
			char tmp = findBoolTab(is, 9, false); //wartoœæ do uzupe³nienia
			for (int i = 0; i < 9; i++) {
				if (sudoku[row][i] == 0) {
					sudoku[row][i] = tmp + 1; //wpisaæ
					did = true; //dokonano zmiany
					changes++; //jedna zmiana wiêcej
					snprintf(logStr, 79, "      jedyna brakuj¹ca: %d, uzupelniono: [%d][%d] = %d\n      wiersz %d uzupe³niony\n", tmp + 1, row, i, tmp + 1, row);
					logApp(logFile, logStr, NULL);
				}
			}
		}
		//metoda dopasowania cyfry do pola
		for (int i = 0; i < 9; i++) { //dla ka¿dego pustego pola
			if (sudoku[row][i] == 0) {
				//log
				snprintf(logStr, 20, "      pole [%d][%d]:\n", row, i);
				logApp(logFile, logStr, NULL);
				//endLog
				char missT = miss; //iloœæ cyfr potencjalnie pasuj¹cych
				bool isT[9]; //cyfry których tam byæ nie mo¿e
				boolTabCopy(isT, is, 9);
				for (int j = 0; j < 9; j++) { //dla ka¿dej potencjalnie pasuj¹cej cyfry
					if (isT[j] == false) {
						if (findInColumn(sudoku, i, j + 1, logFile)) { //je¿eli jest w kolumnie, to nie pasuje
							isT[j] = true; //nie pasuje
							missT--; //jedna potencjalnie pasuj¹ca mniej
									 //do nastêpnej potencjalnie pasuj¹cej cyfry
						}
						else if (findInSquare(sudoku, i / 3, row / 3, j + 1, logFile)) { //je¿eli jest w kwadracie, to nie pasuje
							isT[j] = true; //nie pasuje
							missT--; //jedna potencjalnie pasuj¹ca mniej
									 //do nastêpnej potencjalnie pasuj¹cej cyfry
						}
						else { //jeœeli nie ma
							if (missT == 1) { //je¿eli to jest jedyna potencjalna to pasuje
								sudoku[row][i] = j + 1; //wpisaæ
								did = true; //dokonano zmiany
								changes++; //jedna zmiana wiêcej
								is[j] = true; //luka uzupe³niona
								miss--; //jedna luka mniej
								missT = 0;
								listAddNode(list, sudoku); //dopisaæ do listy rozwi¹zañ
								//out("fillRow()", sudoku, row, i); //poinformuj o front-end o zmianie
								//log
								snprintf(logStr, 45, "      cyfra nr = %d: uzupelniono: [%d][%d] = %d\n", i, row, i, j + 1);
								logApp(logFile, logStr, sudoku);
								//endLog
								break; //do nastêpnej luki
							}
							snprintf(logStr, 25, "      cyfra nr = %d -> _\n", i);
							logApp(logFile, logStr, NULL);
						}
					}
				}
				if (missT == 1) { //je¿eli to jest jedyna potencjalna to pasuje
					char tmp = findBoolTab(isT, 9, false); //wartoœæ do uzupe³nienia
					sudoku[row][i] = tmp + 1; //wpisaæ
					did = true; //dokonano zmiany
					changes++; //jedna zmiana wiêcej
					is[tmp] = true; //luka uzupe³niona
					miss--; //jedna luka mniej
					listAddNode(list, sudoku); //dopisaæ do listy rozwi¹zañ
                    //out("fillRow()", sudoku, row, i); //poinformuj o front-end o zmianie
					snprintf(logStr, 52, "      jedyna brakuj¹ca: %d, uzupelniono: [%d][%d] = %d\n", tmp + 1, row, i, tmp + 1);
					logApp(logFile, logStr, sudoku);
					//do nastêpnej luki
				}
				else if (miss > 0) {
					done = false;
					snprintf(logStr, 31, "      wiersz %d nieuzupelniony\n", row);
					logApp(logFile, logStr, NULL);
				}
				else if (miss == 0) {
					done = true;
					snprintf(logStr, 28, " %d    wiersz %d uzupelniony\n", miss, row);
					logApp(logFile, logStr, NULL);
				}
			}
		}
	}
	return changes;
}

//rozwi¹zuje sudoku z za³o¿eniem ze [y][x] = var
bool assume(char sudoku[9][9], int y, int x, int var, FILE* logFile, struct List* list) {

	//log
	char logStr[46]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 22, "assume(): [%d][%d] = %d\n", y, x, var);
	logApp(logFile, logStr, NULL);
	//endLog
	char sudokuCp[9][9];
	memcpy(sudokuCp, sudoku, 9 * 9 * sizeof(char));
	sudokuCp[y][x] = var;
	listAddBranch(list, sudokuCp);
	//out("assume()", sudokuCp, y, x); //poinformuj o front-end o zmianie
	if (solve(sudokuCp, logFile, list) == true) {
		//out("assume()", sudokuCp, y, x); //poinformuj o front-end o zmianie
		snprintf(logStr, 46, "assume(): [%d][%d] = %d - za³o¿enie poprawne\n", y, x, var);
		logApp(logFile, logStr, NULL);
		memcpy(sudoku, sudokuCp, 9 * 9 * sizeof(char));
		return true;
	}
	else {
		//log
		logDate(logFile);
		snprintf(logStr, 44, "assume(): [%d][%d] = %d - za³o¿enie b³êdne\n", y, x, var);
		logApp(logFile, logStr, NULL);
		//endLog
		listUp(list);
		//out("assume()", sudoku, y, x); //poinformuj o front-end o zmianie
		return false;
	}
}

//Rozwi¹zuje zadan¹ planszê, zwraca false w przypadku niepowodzenia
bool solve(char sudoku[9][9], FILE* logFile, struct List* list) {
	//log
	char logStr[53]; //szacowana najwiêksza mo¿liwa d³ugoœæ wpisu
	logDate(logFile);
	snprintf(logStr, 10, "solve():\n");
	logApp(logFile, logStr, NULL);
	//endLog
	char changes = 1;
	while (changes) {
		changes = 0;
		for (int i = 0; i < 9; i++) { //rozwi¹¿ wiersze
			changes += fillRow(sudoku, i, logFile, list);
			char check = checkSudoku(sudoku, logFile); //test poprawnoœci rowi¹zania
			if (check < 0) {
				//log
				snprintf(logStr, 72, " !### niepoprawnie rozwi¹zany, kod bledu: %d, rozwi¹zywanie przerwane!\n", check);
				logApp(logFile, logStr, sudoku);
				//endLog
				return false;
			}
			if (check == 1) {
				return true;
			}
		}
	}
	if (checkSudoku(sudoku, logFile) == 1) {
		//log
		logDate(logFile);
		snprintf(logStr, 28, "solve(): plansza rozwi¹zana\n");
		logApp(logFile, logStr, NULL);
		//endLog
		return true;
	}
	//log
	logDate(logFile);
	snprintf(logStr, 53, "solve(): plansza nierozwi¹zana, konieczne za³o¿enia\n");
	logApp(logFile, logStr, NULL);
	//endLog
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (sudoku[i][j] == 0) {
				bool is[9];
				fillBoolTab(is, 9, false);
				listRow(sudoku, i, is, 9, logFile);
				listColumn(sudoku, j, is, 9, logFile);
				listSquare(sudoku, j / 3, i / 3, is, 9, logFile);
				for (int k = 0; k < 9; k++) {
					if (is[k] == 0) {
						if (assume(sudoku, i, j, k + 1, logFile, list) == true) {
							return true;
						}
					}
				}
				//log
				logDate(logFile);
				snprintf(logStr, 32, "solve(): plansza nierozwi¹zana\n");
				logApp(logFile, logStr, NULL);
				//endLog
				return false;
			}
		}
	}
	return false;
}
