#ifndef S21_SPRINTF_UTILS_H
#define S21_SPRINTF_UTILS_H

#include <stdarg.h>

#include "s21_string.h"

typedef struct {
  int pres;
  int pres_other;
  int is_pres_for_other;
  long double pow_pres;
  int width;
  int minus_flag;
  int space_flag;
  int zero_flag;
  int hash_flag;
  int pres_star_flag;
  int width_star_flag;
  int g_spec;
  int plus_flag;
  char mod;

} Modifiers;

int s21_isalpha(int c);

int s21_isdigit(int c);

void print_float(int is_negative, int f_width, char *add_str, Modifiers *mods);

void init_modifiers(Modifiers *mods);

int number_of_digits(long long x);

void make_char_from_int(char *str, long long x);

void width_process(char *str, s21_size_t len, int width, int min_flag,
                   char fill_sym);

void c_mod_process(char *add_str, Modifiers *mods, va_list *ар);

void s_mod_process(char *add_str, Modifiers *mods, va_list *ар);

void hash_mod_process(char *add_str, Modifiers *mods);

void d_u_mod_process(char spec, char *add_str, Modifiers *mods, va_list *ар);

void read_variable(char spec, void *out, Modifiers *mods, va_list *ap);

void insert_char_at_start(char *str, char c);

void reverse(char *str);

void to_octal(char *num_str, unsigned long x);

void to_hex(char *num_str, unsigned long x);

void x_o_mod_process(char spec, char *add_str, Modifiers *mods, va_list *ap);

int is_format_specifier(char c);

void g_mod_process(char spec, char *add_str, Modifiers *mods, va_list *ap);

int get_power_and_float(void *y, void *orig_y, Modifiers *mods, va_list *ap);

int sign(long double num);

void e_mod_process(char spec, long double y, int power, char *add_str,
                   Modifiers *mods);

void f_mod_process(long double y, char *add_str, Modifiers *mods);

void remove_zeros(char *str);

void mod_process(char spec, char sec_spec, char third_spec, s21_size_t *i,
                 Modifiers *mods);
void mod_pres(char sec_spec, char third_spec, s21_size_t *i, Modifiers *mods);

int is_non_zero_digit(char c);

void spec_procees(s21_size_t *index, int *k, s21_size_t string_len, char *str,
                  char *add_str, const char *format, Modifiers *mods,
                  va_list *ap);

void p_mod_process(char *buf, va_list *ap);

#endif
