#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

// initializing current directory relative path

const char *cur_dir = ".";

int select_csv(const struct dirent *dir_ent) {
    return ends_substr(dir_ent->d_name, ".csv");
}

int get_select_dir_ent_num(const char *dir_name, int select(const struct dirent *)) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        return -1;
    }
    struct dirent **dir_ents;
    int ent_num = scandir(dir_name, &dir_ents, select, alphasort);
    closedir(dir);
    return ent_num;
}

int ls_select_dir_ent(const char *dir_name, int select(const struct dirent *)) {
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        return -1;
    }

    struct dirent **dir_ents;
    int ent_num = scandir(dir_name, &dir_ents, select, alphasort);
    if (ent_num == -1) {
        return -1;
    }

    for (int i = 0; i < ent_num; i++) {
        puts(dir_ents[i]->d_name);
        free(dir_ents[i]);
    }

    closedir(dir);
    free(dir_ents);
    return ent_num;
}

int get_rec_num_csv(const char *csv_name) {
    FILE *db = fopen(csv_name, "r");
    if (db == NULL) {
        return -1;
    }

    int ent_num = 0;
    while (feof(db) == 0) {
        if (getc(db) == '\n') {
            ent_num++;
        }
    }

    return ent_num;
}