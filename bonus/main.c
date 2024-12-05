// clearerr(), ferror(), feof(), rewind(), rename()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strnrev(char *str, size_t n);

int main(int argc, char **argv) {
    // check count of args
    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // get file contents length
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    fseek(f, 0, SEEK_END);
    size_t fconts_len = ftell(f);
    rewind(f);

    // get file contents
    char *fconts = (char*)calloc(fconts_len + 1, sizeof(char));
    fread(fconts, fconts_len, sizeof(char), f);

    // reverse file contents
    freopen(argv[1], "w", f);
    strnrev(fconts, fconts_len - 1);
    fwrite(fconts, sizeof(char), strlen(fconts), f);

    if (ferror(f) != 0) {
        perror("error");
        exit(EXIT_FAILURE);
    }

    // print out change
    freopen(argv[1], "r", f);
    printf("contents of %s have been changed to:\n", argv[1]);
    while (!feof(f)) {
        fputc(fgetc(f), stdout);
    }

    fclose(f);

    // get file name
    char *fname = (char*)calloc(strlen(argv[1]) + 1, sizeof(char));
    strncpy(fname, argv[1], strlen(argv[1]));

    // reverse file name
    if (rename(argv[1], strnrev(fname, strlen(fname))) != 0) {
        perror("error");
        exit(EXIT_FAILURE);
    } else fprintf(stdout, "%s has been renamed to %s\n", argv[1], fname);

    // free allocated memory
    free(fconts);
    free(fname);

    return EXIT_SUCCESS;
}

char *strnrev(char *str, size_t n) {
    char tmp;
    for (int i = 0; i < n / 2; i++) {
        tmp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = tmp;
    }
    return str;
}