#include "preprocessor.h"

int main(int argc, char **argv) {
    if(argc == 1) {
        printf("No argument!\n");

        exit(1);
    }

    char *path = argv[1];

    process(path);

    return 0;
}