#include "log.h"

//przygotowuje plik z logami
FILE* prepareLog(char* path) {
	FILE* logFile = fopen(path, "w"); //czyœci plik path
	int i = 0;
	while (logFile == NULL && i < 3) { //w razie niepowodzenia w otwarciu pliku próbuje jeszcze trzykrotnie
		logFile = fopen(path, "w");
		i++;
	}
	if (logFile == NULL) //jeœli siê nie uda, zwraca NULL
		return NULL;
	fprintf(logFile, "Log generated ");
	logDate(logFile);
	fprintf(logFile, "\n");
	fclose(logFile);
	logFile = fopen(path, "a"); //otwiera plik w trybie do dopisywania
	i = 0;
	while (logFile == NULL && i < 3) {
		logFile = fopen(path, "a");
		i++;
	}
	if (logFile == NULL) //jeœli siê nie uda, zwraca NULL
		return NULL;
	fprintf(logFile, "Log ready to write\n");
	return logFile;
}

//dopisuje do pliku z logami
void logApp(FILE* logFile, char* text, char sudoku[9][9]) {
	if (logFile == NULL)
		return;
	fprintf(logFile, "%s", text);
	if (sudoku != NULL) {
		fprintSudoku(logFile, sudoku);
	}
}

//zapisuje do logu aktualn¹ date
void logDate(FILE* logFile) {
    char bufor[21];
    time_t cza = time(NULL);
    strftime(bufor, 21, "<%d.%m.%y %X> ", localtime(&cza));
	fprintf(logFile, bufor);
}
