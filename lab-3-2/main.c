#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clndr.h"
#include "clear_input.h"
#include "string_parsing.h"

#define INPUT_BUFFER_SIZE (4 + 2)
#define MENU_BUFFER_SIZE (1 + 2)
#define DAY_MAX 31
#define MONTHS_NUM 12
#define YEAR_MAX 10000

int main() {
  int day, month, year, day_of_week;

  const char *week[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                        "Thursday", "Friday", "Saturday"};

  int common_calendar[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int leap_calendar[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Inform the user about limitations of the program
  printf("The year number should be less than %d.\n", YEAR_MAX);

  // User interface of the program in a do while loop
  char *buffer = malloc(INPUT_BUFFER_SIZE);
  bool exit_condition = false;

  do {
    // Get day
    printf("Enter the day: ");
    fgets(buffer, INPUT_BUFFER_SIZE, stdin);

    if (!ends_on_newline(buffer)) {
      printf("The entered string is larger than the input buffer.\n");
      clear_input();
      continue;
    } else if (!is_int(buffer)) {
      printf("The entered string is not an integer number.\n");
      continue;
    } else {
      day = (int)strtol(buffer, NULL, 10);
    }

    if (day <= 0) {
      printf("The day number can only be positive.\n");
      continue;
    } else if (day > DAY_MAX) {
      printf(
          "The day number exceeds the possible amount of days in any month.\n");
      continue;
    }

    // Get month
    printf("Enter the month: ");
    fgets(buffer, INPUT_BUFFER_SIZE, stdin);

    if (!ends_on_newline(buffer)) {
      printf("The entered string is larger than the input buffer.\n");
      clear_input();
      continue;
    } else if (!is_int(buffer)) {
      printf("The entered string is not an integer number.\n");
      continue;
    } else {
      month = (int)strtol(buffer, NULL, 10);
    }

    if (month <= 0) {
      printf("The month number can only be positive.\n");
      continue;
    } else if (month > MONTHS_NUM) {
      printf(
          "The month number exceeds the possible number of months in a "
          "year.\n");
      continue;
    } else if (day > leap_calendar[month - 1]) {
      printf(
          "The day number exceeds the possible amount of days in this "
          "month.\n");
      continue;
    }

    // Get year
    printf("Enter the year: ");
    fgets(buffer, INPUT_BUFFER_SIZE, stdin);

    if (!ends_on_newline(buffer)) {
      printf("The entered string is larger than the input buffer.\n");
      clear_input();
      continue;
    } else if (!is_int(buffer)) {
      printf("The entered string is not an integer number.\n");
      continue;
    } else {
      year = (int)strtol(buffer, NULL, 10);
    }

    if (year <= 0) {
      printf("The year number can only be positive.\n");
      continue;
      // Optional, depends on the desired upper limit and
      // input buffer size
    } else if (year >= YEAR_MAX) {
      printf("The year number exceeds the operational range.\n");
      continue;
    }

    // Check whether the entered date exists
    if (day > (is_leap(year) ? leap_calendar[month - 1]
                             : common_calendar[month - 1])) {
      printf("The entered date does not exist.\n");
      continue;
    }

    // Print out the day of the week
    day_of_week = gauss_day_of_week(day, month, year);
    printf("%d.%d.%d is %s.\n", day, month, year, week[day_of_week]);

    // Prompt user with a choice to restart or quit the program
    do {
      printf(
          "Enter r to restart the program or q to quit "
          "it: ");
      fgets(buffer, MENU_BUFFER_SIZE, stdin);

      if (!ends_on_newline(buffer)) {
        clear_input();
      } else if (strcasecmp(buffer, "q\n") == 0) {
        exit_condition = true;
      }
    } while (strcasecmp(buffer, "q\n") != 0 && strcasecmp(buffer, "r\n") != 0);
  } while (!exit_condition);

  free(buffer);

  return 0;
}