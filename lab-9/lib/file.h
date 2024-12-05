#pragma once

#include <dirent.h>
#include <stdlib.h>

// DESCRIPTION
//      current directory relative path
extern const char *cur_dir;

// DESCRIPTION
//      selects csv files for scandir
// RETURN VALUES
//      returns a non-zero integer if dir_ent is a csv file
int select_csv(const struct dirent *dir_ent);

// DESCRIPTION
//      gets number of dir_name directory entries filtered by the select function
// RETURN VALUES
//      returns -1 on error, number of directory entries on success
int get_select_dir_ent_num(const char *dir_name, int select(const struct dirent *));

// DESCRIPTION
//      lists dir_name directory entries filtered by the select function
// RETURN VALUES
//      returns -1 on error, number of directory entries listed on success
int ls_select_dir_ent(const char *dir_name, int (*select)(const struct dirent *));

// DESCRIPTION
//      calculates number of records in a csv file
// RETURN VALUES
//      returns -1 on error, number of entries in a csv file which name is pointed to by csv on success
int get_rec_num_csv(const char *csv_name);