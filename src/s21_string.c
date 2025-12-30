#include "s21_string.h"

#include <locale.h>
#include <stdlib.h>

#include "s21_sprintf_utils.h"
#include "s21_string_utils.h"

#if defined(__linux__)
#include "s21_linux_err_messages.h"
#elif defined(__APPLE__)
#include "s21_mac_err_messages.h"
#endif

#define UNIT_LENGTH 100

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  for (const char *pstr = str; *pstr != '\0'; ++pstr) length++;
  return length;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = S21_NULL;
  const unsigned char *pmem = str;
  for (; n-- > 0 && p == S21_NULL; pmem++) {
    if (*pmem == (unsigned char)c) p = pmem;
  }
  return (void *)p;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *pstr1 = str1;
  const unsigned char *pstr2 = str2;
  int res = 0;

  while (*pstr1 == *pstr2 && --n > 0) {
    pstr1++;
    pstr2++;
  }

  if (n > 0) res = *pstr1 - *pstr2;

  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *pdest = (unsigned char *)dest;
  const unsigned char *psrc = (unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) {
    pdest[i] = psrc[i];
  }
  return pdest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *pstr = str;
  for (s21_size_t i = 0; i < n; i++) {
    pstr[i] = (unsigned char)c;
  }
  return pstr;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *end = dest + s21_strlen(dest);
  for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
    *end++ = src[i];
  }
  *end = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *res = S21_NULL;
  const char *pstr = str;
  do {
    if (*pstr == c) res = (char *)pstr;
  } while (*pstr++ != '\0' && res == S21_NULL);
  return res;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  unsigned char *pstr1 = (unsigned char *)str1;
  unsigned char *pstr2 = (unsigned char *)str2;
  int res = 0;

  while (n > 0 && *pstr1 == *pstr2 && *pstr1 != '\0') {
    pstr1++;
    pstr2++;
    n--;
  }

  if (n > 0) res = *pstr1 - *pstr2;

  return res;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t index = 0;
  while (index < n && src[index] != '\0') {
    dest[index] = src[index];
    index++;
  }
  while (index < n) {
    dest[index] = '\0';
    index++;
  }
  return dest;
}

int s21_strcspn(const char *s, const char *reject) {
  s21_size_t bytes = 0;
  int time_to_go = 0;
  while (*s != '\0' && !time_to_go) {
    for (s21_size_t i = 0; reject[i] != '\0'; i++) {
      if (reject[i] == *s) time_to_go = 1;
    }
    if (!time_to_go) {
      bytes++;
      s++;
    }
  }
  return bytes;
}

char *s21_strerror(int errnum) {
  const char *err_msg = S21_NULL;
  static char buffer[50];
#if defined(__linux__)
  s21_sprintf(buffer, "Unknown error %d", errnum);
  if (errnum >= 0 && errnum < LINUX_NERR)
    err_msg = linux_error_messages[errnum];
  else
    err_msg = buffer;
#elif defined(__APPLE__)
  s21_sprintf(buffer, "Unknown error: %d", errnum);
  if (errnum >= 0 && errnum < MAC_NERR)
    err_msg = mac_error_messages[errnum];
  else
    err_msg = buffer;
#endif
  return (char *)err_msg;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *pstr = S21_NULL;
  int i = 0, j = 0;
  while (str1[i] != '\0' && pstr == S21_NULL) {
    while (str2[j] != '\0' && pstr == S21_NULL) {
      if (str1[i] == str2[j]) pstr = (char *)&str1[i];
      j++;
    }
    i++;
    j = 0;
  }
  return pstr;
}

char *s21_strrchr(const char *str, int c) {
  const char *last = S21_NULL;
  do {
    if (*str == (char)c) last = str;
  } while (*str++ != '\0');
  return (char *)last;
}

char *s21_strstr(const char *haystack, const char *needle) {
  const char *phaystack = S21_NULL;
  char *res = (char *)haystack;
  int match = 0;

  while (*haystack != '\0' && !match) {
    const char *ph = haystack;
    const char *pn = needle;

    while (*ph != '\0' && *pn != '\0' && *ph == *pn) {
      ph++;
      pn++;
    }

    if (*pn == '\0') {
      phaystack = haystack;
      match = 1;
    }

    haystack++;
  }

  if (s21_strlen(needle) != 0) res = (char *)phaystack;

  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last_token = S21_NULL;
  char *start_token = S21_NULL;

  if (str != S21_NULL) last_token = str;

  if (last_token != S21_NULL && *last_token != '\0') {
    remove_leading_delims(&last_token, delim);

    if (*last_token != '\0') {
      start_token = last_token;

      find_next(&last_token, delim);

      if (*last_token == '\0') last_token = S21_NULL;
    }
  }

  return start_token;
}

int s21_sprintf(char *str, const char *format, ...) {
  setlocale(LC_ALL, "C");

  Modifiers mods = {0};
  size_t string_len = s21_strlen(format);
  va_list ap;
  va_start(ap, format);
  int k = 0;

  for (size_t i = 0; i < string_len; i++) {
    init_modifiers(&mods);
    char *add_str = malloc(UNIT_LENGTH * sizeof(char));
    add_str[0] = '\0';
    if (format[i] == '%')
      spec_procees(&i, &k, string_len, str, add_str, format, &mods, &ap);
    else {
      str[k] = format[i];
      k++;
      str[k] = '\0';
    }
    free(add_str);
  }
  return k;
}

void s21_to_upper_in_place(char *str) {
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i < len + 1; i++) {
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] = str[i] - 32;
    else
      str[i] = str[i];
  }
}

void *s21_to_upper(const char *str) {
  int err = 0;
  char *upper_str = S21_NULL;

  if (str == S21_NULL) err = 1;

  if (!err) {
    s21_size_t len = s21_strlen(str);
    upper_str = malloc((len + 1) * sizeof(char));

    if (upper_str == S21_NULL) err = 1;

    if (!err) {
      for (s21_size_t i = 0; i < len + 1; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
          upper_str[i] = str[i] - 32;
        else
          upper_str[i] = str[i];
      }
    }
  }

  return upper_str;
}

void *s21_to_lower(const char *str) {
  int err = 0;
  char *lower_str = S21_NULL;

  if (str == S21_NULL) err = 1;

  if (!err) {
    s21_size_t len = s21_strlen(str);
    lower_str = malloc((len + 1) * sizeof(char));

    if (lower_str == S21_NULL) err = 1;

    if (!err) {
      for (s21_size_t i = 0; i < len + 1; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
          lower_str[i] = str[i] + 32;
        else
          lower_str[i] = str[i];
      }
    }
  }

  return lower_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int err = 0;
  char *insert = S21_NULL;

  start_index = start_index - 1;

  if (src == S21_NULL || str == S21_NULL) err = 1;

  if (!err) {
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_str = s21_strlen(str);

    if (start_index > len_src) err = 1;

    if (!err) {
      insert = malloc((len_src + len_str + 1) * sizeof(char));

      if (insert == S21_NULL) err = 1;

      if (!err) {
        for (s21_size_t i = 0; i < start_index; i++) {
          insert[i] = src[i];
        }
        for (s21_size_t i = 0; i < len_str; i++) {
          insert[start_index + i] = str[i];
        }
        for (s21_size_t i = 0; src[start_index + i] != '\0'; i++) {
          insert[start_index + len_str + i] = src[i + start_index];
        }
        insert[len_str + len_src] = '\0';
      }
    }
  }

  return insert;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int err = 0;
  char *output_str = S21_NULL;

  if (src == S21_NULL || trim_chars == S21_NULL) err = 1;

  if (!err) {
    const char *start = src;
    const char *end = src + s21_strlen(src) - 1;

    while (*start && s21_strchr(trim_chars, *start)) {
      start++;
    }

    while (end > start && s21_strchr(trim_chars, *end)) {
      end--;
    }

    s21_size_t len = end >= start ? (end - start + 1) : 0;
    output_str = malloc(len + 1);

    if (output_str == S21_NULL) err = 1;

    if (!err) {
      for (s21_size_t i = 0; i < len; i++) {
        output_str[i] = start[i];
      }
    }

    output_str[len] = '\0';
  }

  return output_str;
}
