#ifndef arguments_h
#define arguments_h

#include <stdio.h>
#include <stdbool.h>

//Informacje podane jako parametry uruchomienia programu
struct Arguments {
    bool defSource; //czy ustawiono Ÿród³o danych wejœciowych
    char* sourceFile; //œcie¿ka do pliku z danymi wejœciowymi, b¹dŸ puste je¿eli wprowadzane z klawiatury
    bool defOutput; //czy ustawiono wyjœcie danych
    char* outputFile; //œcie¿ka do pliku wyjœciowego, je¿eli puste pomija zapis
    bool defHistory; //czy ustawiono zapis historii rozwi¹zania
    char* historyFile; //œcie¿ka do pliku na historie, je¿eli puste pomija zapis
};

//wype³nia strukturê parametrami zwi¹zanymi z wejœciem danych
struct Arguments findSource(struct Arguments args, int argc, char** argv);
//wype³nia strukturê parametrami zwi¹zanymi z plikiem wyjœciowym
struct Arguments findOutput(struct Arguments args, int argc, char** argv);
//wype³nia strukturê parametrami zwi¹zanymi z histori¹ rozwi¹zywania
struct Arguments findHistory(struct Arguments args, int argc, char** argv);
//Wype³nia strukturê arguments parametrami uruchomienia programu
struct Arguments readArguments(int argc, char** argv);
#endif
