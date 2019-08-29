#include "arguments.h"

//wype�nia struktur� parametrami zwi�zanymi z wej�ciem danych
struct Arguments findSource(struct Arguments args, int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "/i")) {
            args.defSource = true;
            if (i+1 < argc) {
                if (argv[i+1][0] == 47) { //47 == "\"
                    args.sourceFile = NULL;
                }
                else
                    args.sourceFile = argv[i+1];
            }
            else {
                args.sourceFile = NULL;
            }
        }
    }
    return args;
}

//wype�nia struktur� parametrami zwi�zanymi z plikiem wyj�ciowym
struct Arguments findOutput(struct Arguments args, int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "/o")) {
            args.defOutput = true;
            if (i+1 < argc) {
                if (argv[i+1][0] == 47) { //47 == "\"
                    args.outputFile = NULL;
                }
                else
                    args.outputFile = argv[i+1];
            }
            else {
                args.outputFile = NULL;
            }
        }
    }
    return args;
}

//wype�nia struktur� parametrami zwi�zanymi z histori� rozwi�zywania
struct Arguments findHistory(struct Arguments args, int argc, char** argv) {
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "/h")) {
            args.defHistory = true;
            if (i+1 < argc) {
                if (argv[i+1][0] == 47) { //47 == "\"
                    args.historyFile = NULL;
                }
                else
                    args.historyFile = argv[i+1];
            }
            else {
                args.historyFile = NULL;
            }
        }
    }
    return args;
}

//Wype�nia struktur� arguments parametrami uruchomienia programu
struct Arguments readArguments(int argc, char** argv) {
    struct Arguments ret;
    ret.defSource = ret.defOutput = ret.defHistory = false;
    if (argc == 1)
        return ret;
    ret = findSource(ret, argc, argv);
    ret = findOutput(ret, argc, argv);
    ret = findHistory(ret, argc, argv);
    return ret;
}
