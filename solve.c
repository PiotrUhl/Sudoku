#include "solve.h"

//Wype�nia tablic� warto�ciami var
bool* fillBoolTab(bool tab[], int n, bool var) {
	for (int i = 0; i < 9; i++) {
		tab[i] = var;
	}
	return tab;
}

//Sprawdza czy plansza jest poprawn�, nie zawieraj�c� b��d�w plansz� sudoku, 0 je�li poprawna nierozwi�zana, 1 je�li poprawna rozwi�zana
char checkSudoku(char sudoku[9][9], FILE* logFile) {
	bool done = true; //Czy plansza jest rozwi�zana
	logDate(logFile);
	logApp(logFile, "checkSudoku:", NULL);
	char tmp = checkSudokuRow(sudoku, logFile);
	if (tmp == 1)
        done = false;
    else if (tmp < 0)
        return tmp;
        // -2 - to nie jest plansza sudoku
        // -11 - plansza b�ednie rozwi�zana (wiersze)
    if (checkSudokuColumn(sudoku, logFile) == -12)
        return -12; // -12 - plansza b��dnie rozwi�zana (kolumny)
    if (checkSudokuSquare(sudoku, logFile) == -13)
        return -13; // -13 - plansza b��dnie rozwi�zana (kwadraty)
	if (done == true) {
		logApp(logFile, " plansza poprawna, rozwiazana\n", NULL);
		return 1; //poprawna plansza, poprawnie rozwi�zanA
	}
	logApp(logFile, " plansza poprawna, nierozwiazana\n", NULL);
	return 0; //poprawna plansza, nierozwi�zana
}

//Pomocnicza dla checkSudoku(), sprawdza poprawno�� w wierszach
char checkSudokuRow(char sudoku[9][9], FILE* logFile) {
    bool tab[9]; //Tablica do przechowywania informacji czy odnaleziono dan� cyfr�
    bool done = true;
	for (int i = 0; i < 9; i++) {
		fillBoolTab(tab, 9, false);
		for (int j = 0; j < 9; j++) {
			if (sudoku[i][j] != '_' && (sudoku[i][j] < 0 || sudoku[i][j] > 9)) {
                //{log
                logDate(logFile);
                char logStr[54]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
                snprintf(logStr, 54, " err2  (to nie jest plansza sudoku) sudoku[%d][%d] = %d\n", i, j, sudoku[i][j]);
                logApp(logFile, logStr, sudoku);
                //}
				return -2; // -2 - to nie jest plansza sudoku
			}
			if (sudoku[i][j] > 0 && sudoku[i][j] <= 9) {
				if (tab[sudoku[i][j] - 1] == true) {
                    //{ log
                    logDate(logFile);
                    char logStr[67]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
                    snprintf(logStr, 67, " err11 (plansza b��dnie rozwi�zana - wiersze) sudoku[%d][%d] = %d\n", i, j, sudoku[i][j]);
                    logApp(logFile, logStr, sudoku);
                    //}
					return -11; // -11 - plansza b�ednie rozwi�zana (wiersze)
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

//Pomocnicza dla checkSudoku(), sprawdza poprawno�� w kolumnach
char checkSudokuColumn(char sudoku[9][9], FILE* logFile) {
    bool tab[9]; //Tablica do przechowywania informacji czy odnaleziono dan� cyfr�
	for (int i = 0; i < 9; i++) {
		fillBoolTab(tab, 9, false);
		for (int j = 0; j < 9; j++) {
			if (sudoku[j][i] > 0 && sudoku[j][i] <= 9) {
				if (tab[sudoku[j][i] - 1] == true) {
                    //{ log
                    logDate(logFile);
                    char logStr[67]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
                    snprintf(logStr, 67, " err12 (plansza b��dnie rozwi�zana - kolumny) sudoku[%d][%d] = %d\n", i, j, sudoku[i][j]);
                    logApp(logFile, logStr, sudoku);
                    //}
					return -12; // -12 - plansza b��dnie rozwi�zana (kolumny)
				}
				tab[sudoku[j][i] - 1] = true;
			}
		}
	}
	return 0;
}

//Pomocnicza dla checkSudoku(), sprawdza poprawno�� w kwadratach
char checkSudokuSquare(char sudoku[9][9], FILE* logFile) {
    bool tab[9]; //Tablica do przechowywania informacji czy odnaleziono dan� cyfr�
	for (int ii = 0; ii < 3; ii++) {
		for (int ij = 0; ij < 3; ij++) {
			fillBoolTab(tab, 9, false);
			for (int ji = 0; ji < 3; ji++) {
				for (int jj = 0; jj < 3; jj++) {
					if (sudoku[ji + 3 * ii][jj + 3 * ij] > 0 && sudoku[ji + 3 * ii][jj + 3 * ij] <= 9) {
						if (tab[sudoku[ji + 3 * ii][jj + 3 * ij] - 1] == true) {
                            //{ log
                            logDate(logFile);
                            char logStr[76]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
                            snprintf(logStr, 76, " err13 (plansza b��dnie rozwi�zana - kwadraty) sudoku[%d+3*%d][%d+3*%d] = %d\n", ji, ii, jj, ij, sudoku[ji + 3 * ii][jj + 3 * ij]);
                            logApp(logFile, logStr, sudoku);
                            //}
							return -13; // -13 - plansza b��dnie rozwi�zana (kwadraty)
						}
						tab[sudoku[ji + 3 * ii][jj + 3 * ij] - 1] = true;
					}
				}
			}
		}
	}
	return 0;
}

//tworzy tablic� zawieraj�c� informacje kt�re cyfry s� w wierszu, a kt�rych nie ma, zwraca ilo�� brakuj�cych
char listRow(char sudoku[9][9], int row, bool tab[], int n, FILE* logFile) {
	char ilosc = 9;
	for (int i = 0; i < n; i++) {
		if (sudoku[row][i] > 0 && sudoku[row][i] <= 9) {
			tab[sudoku[row][i] - 1] = true;
			ilosc--;
		}
	}
	//log
	char logStr[43]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
	logDate(logFile);
	snprintf(logStr, 43, "listRow(): wiersz %d, ilosc: %d {%d%d%d%d%d%d%d%d%d}\n", row, ilosc, tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
	logApp(logFile, logStr, NULL);
	//endlog
	return ilosc;
}
//tworzy tablic� zawieraj�c� informacje kt�re cyfry s� w kolumnie, a kt�rych nie ma, zwraca ilo�� brakuj�cych
char listColumn(char sudoku[9][9], int column, bool tab[], int n, FILE* logFile) {
	char ilosc = 9;
	for (int i = 0; i < n; i++) {
		if (sudoku[i][column] > 0 && sudoku[i][column] <= 9) {
			tab[sudoku[i][column] - 1] = true;
			ilosc--;
		}
	}
	//log
	char logStr[47]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
	logDate(logFile);
	snprintf(logStr, 47, "listColumn(): kolumna %d, ilosc: %d {%d%d%d%d%d%d%d%d%d}\n", column, ilosc, tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
	logApp(logFile, logStr, NULL);
	//endlog
	return ilosc;
}

//tworzy tablic� zawieraj�c� informacje kt�re cyfry s� w kwadracie, a kt�rych nie ma, zwraca ilo�� brakuj�cych
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
	char logStr[54]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
	logDate(logFile);
	snprintf(logStr, 54, "listSquare(): kwadrat [%d][%d], ilosc: %d {%d%d%d%d%d%d%d%d%d}\n", sy, sx, ilosc, tab[0], tab[1], tab[2], tab[3], tab[4], tab[5], tab[6], tab[7], tab[8]);
	logApp(logFile, logStr, NULL);
	//endlog
	return ilosc;
}

//sprawdza czy w okre�lonym wierszu wyst�puje cyfra var
bool findInRow(char sudoku[9][9], int row, char var, FILE* logFile) {
	//log
	char logStr[36]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
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

//sprawdza czy w okre�lonej kolumnie wyst�puje cyfra var
bool findInColumn(char sudoku[9][9], int column, char var, FILE* logFile) {
	//log
	char logStr[40]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
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

//sprawdza czy w okre�lonym kwadracie (sx, sy)(numerowane od zera) wyst�puje cyfra var
bool findInSquare(char sudoku[9][9], int sx, int sy, char var, FILE* logFile) {
	//log
	char logStr[46]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
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

//znajduje w tablicy warto�� var, zwraca indeks
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

//Wype�nia luki w wierszu row kt�re mo�na jednoznacznie okre�li�, zwraca ilo�� dokonanych zmian
char fillRow(char sudoku[9][9], int row, FILE* logFile, struct List* list) {
	//log
	char logStr[86]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
	logDate(logFile);
	snprintf(logStr, 21, "fillRow(): wiersz %d\n", row);
	logApp(logFile, logStr, sudoku);
	//endLog
	bool done = true; //czy rz�d rozwi�zany w ca�o�ci //nieu�ywana
	bool did = true; //czy podczas przej�cia p�tli dokonano jakiej� zmiany
	char changes = 0; //ilo�� dokonanych zmian
	bool is[9]; //cyfry kt�re s� uzupe�nionefillRow
	fillBoolTab(is, 9, false);
	while (did) {
		did = false;
		char miss = listRow(sudoku, row, is, 9, logFile); //ilo�c cyfr brakuj�cych
		//je�eli jest tylko jedno puste pole
		if (miss == 1) {
			char tmp = findBoolTab(is, 9, false); //warto�� do uzupe�nienia
			for (int i = 0; i < 9; i++) {
				if (sudoku[row][i] == 0) {
					sudoku[row][i] = tmp + 1; //wpisa�
					did = true; //dokonano zmiany
					changes++; //jedna zmiana wi�cej
					snprintf(logStr, 79, "      jedyna brakuj�ca: %d, uzupelniono: [%d][%d] = %d\n      wiersz %d uzupe�niony\n", tmp + 1, row, i, tmp + 1, row);
					logApp(logFile, logStr, NULL);
				}
			}
		}
		//metoda dopasowania cyfry do pola
		for (int i = 0; i < 9; i++) { //dla ka�dego pustego pola
			if (sudoku[row][i] == 0) {
				//log
				snprintf(logStr, 20, "      pole [%d][%d]:\n", row, i);
				logApp(logFile, logStr, NULL);
				//endLog
				char missT = miss; //ilo�� cyfr potencjalnie pasuj�cych
				bool isT[9]; //cyfry kt�rych tam by� nie mo�e
				boolTabCopy(isT, is, 9);
				for (int j = 0; j < 9; j++) { //dla ka�dej potencjalnie pasuj�cej cyfry
					if (isT[j] == false) {
						if (findInColumn(sudoku, i, j + 1, logFile)) { //je�eli jest w kolumnie, to nie pasuje
							isT[j] = true; //nie pasuje
							missT--; //jedna potencjalnie pasuj�ca mniej
									 //do nast�pnej potencjalnie pasuj�cej cyfry
						}
						else if (findInSquare(sudoku, i / 3, row / 3, j + 1, logFile)) { //je�eli jest w kwadracie, to nie pasuje
							isT[j] = true; //nie pasuje
							missT--; //jedna potencjalnie pasuj�ca mniej
									 //do nast�pnej potencjalnie pasuj�cej cyfry
						}
						else { //je�eli nie ma
							if (missT == 1) { //je�eli to jest jedyna potencjalna to pasuje
								sudoku[row][i] = j + 1; //wpisa�
								did = true; //dokonano zmiany
								changes++; //jedna zmiana wi�cej
								is[j] = true; //luka uzupe�niona
								miss--; //jedna luka mniej
								missT = 0;
								listAddNode(list, sudoku); //dopisa� do listy rozwi�za�
								//out("fillRow()", sudoku, row, i); //poinformuj o front-end o zmianie
								//log
								snprintf(logStr, 45, "      cyfra nr = %d: uzupelniono: [%d][%d] = %d\n", i, row, i, j + 1);
								logApp(logFile, logStr, sudoku);
								//endLog
								break; //do nast�pnej luki
							}
							snprintf(logStr, 25, "      cyfra nr = %d -> _\n", i);
							logApp(logFile, logStr, NULL);
						}
					}
				}
				if (missT == 1) { //je�eli to jest jedyna potencjalna to pasuje
					char tmp = findBoolTab(isT, 9, false); //warto�� do uzupe�nienia
					sudoku[row][i] = tmp + 1; //wpisa�
					did = true; //dokonano zmiany
					changes++; //jedna zmiana wi�cej
					is[tmp] = true; //luka uzupe�niona
					miss--; //jedna luka mniej
					listAddNode(list, sudoku); //dopisa� do listy rozwi�za�
                    //out("fillRow()", sudoku, row, i); //poinformuj o front-end o zmianie
					snprintf(logStr, 52, "      jedyna brakuj�ca: %d, uzupelniono: [%d][%d] = %d\n", tmp + 1, row, i, tmp + 1);
					logApp(logFile, logStr, sudoku);
					//do nast�pnej luki
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

//rozwi�zuje sudoku z za�o�eniem ze [y][x] = var
bool assume(char sudoku[9][9], int y, int x, int var, FILE* logFile, struct List* list) {

	//log
	char logStr[46]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
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
		snprintf(logStr, 46, "assume(): [%d][%d] = %d - za�o�enie poprawne\n", y, x, var);
		logApp(logFile, logStr, NULL);
		memcpy(sudoku, sudokuCp, 9 * 9 * sizeof(char));
		return true;
	}
	else {
		//log
		logDate(logFile);
		snprintf(logStr, 44, "assume(): [%d][%d] = %d - za�o�enie b��dne\n", y, x, var);
		logApp(logFile, logStr, NULL);
		//endLog
		listUp(list);
		//out("assume()", sudoku, y, x); //poinformuj o front-end o zmianie
		return false;
	}
}

//Rozwi�zuje zadan� plansz�, zwraca false w przypadku niepowodzenia
bool solve(char sudoku[9][9], FILE* logFile, struct List* list) {
	//log
	char logStr[53]; //szacowana najwi�ksza mo�liwa d�ugo�� wpisu
	logDate(logFile);
	snprintf(logStr, 10, "solve():\n");
	logApp(logFile, logStr, NULL);
	//endLog
	char changes = 1;
	while (changes) {
		changes = 0;
		for (int i = 0; i < 9; i++) { //rozwi�� wiersze
			changes += fillRow(sudoku, i, logFile, list);
			char check = checkSudoku(sudoku, logFile); //test poprawno�ci rowi�zania
			if (check < 0) {
				//log
				snprintf(logStr, 72, " !### niepoprawnie rozwi�zany, kod bledu: %d, rozwi�zywanie przerwane!\n", check);
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
		snprintf(logStr, 28, "solve(): plansza rozwi�zana\n");
		logApp(logFile, logStr, NULL);
		//endLog
		return true;
	}
	//log
	logDate(logFile);
	snprintf(logStr, 53, "solve(): plansza nierozwi�zana, konieczne za�o�enia\n");
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
				snprintf(logStr, 32, "solve(): plansza nierozwi�zana\n");
				logApp(logFile, logStr, NULL);
				//endLog
				return false;
			}
		}
	}
	return false;
}
