#include "s21_string_utils.h"

void remove_leading_delims(char **str, const char *delim) {
  int i = 0;
  int is_delim = 0;
  int done = 0;

  while (!done) {
    if (**str == '\0') {
      done = 1;
    } else {
      is_delim = 0;
      i = 0;
      while (delim[i] != '\0') {
        if (**str == delim[i]) is_delim = 1;
        i++;
      }
      if (is_delim) {
        (*str)++;
      } else {
        done = 1;
      }
    }
  }
}

void find_next(char **str, const char *delim) {
  int i = 0;
  int found_delim = 0;
  int done = 0;

  while (!done) {
    if (**str == '\0') {
      done = 1;
    } else {
      found_delim = 0;
      i = 0;
      while (delim[i] != '\0' && !found_delim) {
        if (**str == delim[i]) found_delim = 1;
        i++;
      }
      if (found_delim) {
        **str = '\0';
        (*str)++;
        done = 1;
      } else {
        (*str)++;
      }
    }
  }
}
