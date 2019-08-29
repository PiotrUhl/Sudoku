#ifndef arguments_h
#define arguments_h

#include <stdio.h>
#include <stdbool.h>

//Informacje podane jako parametry uruchomienia programu
struct Arguments {
    bool defSource; //czy ustawiono �r�d�o danych wej�ciowych
    char* sourceFile; //�cie�ka do pliku z danymi wej�ciowymi, b�d� puste je�eli wprowadzane z klawiatury
    bool defOutput; //czy ustawiono wyj�cie danych
    char* outputFile; //�cie�ka do pliku wyj�ciowego, je�eli puste pomija zapis
    bool defHistory; //czy ustawiono zapis historii rozwi�zania
    char* historyFile; //�cie�ka do pliku na historie, je�eli puste pomija zapis
};

//wype�nia struktur� parametrami zwi�zanymi z wej�ciem danych
struct Arguments findSource(struct Arguments args, int argc, char** argv);
//wype�nia struktur� parametrami zwi�zanymi z plikiem wyj�ciowym
struct Arguments findOutput(struct Arguments args, int argc, char** argv);
//wype�nia struktur� parametrami zwi�zanymi z histori� rozwi�zywania
struct Arguments findHistory(struct Arguments args, int argc, char** argv);
//Wype�nia struktur� arguments parametrami uruchomienia programu
struct Arguments readArguments(int argc, char** argv);
#endif
