#include "s21_sprintf_utils.h"

#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

#define UNIT_LENGTH 100

void init_modifiers(Modifiers *mods) {
  mods->pres = 6;
  mods->pres_other = 1;
  mods->is_pres_for_other = 0;
  mods->pow_pres = pow(10, 6);
  mods->pres_star_flag = 0;
  mods->width = 0;
  mods->width_star_flag = 0;
  mods->minus_flag = 0;
  mods->plus_flag = 0;
  mods->zero_flag = 0;
  mods->hash_flag = 0;
  mods->space_flag = 0;
  mods->mod = 0;
  mods->g_spec = 0;
}

int is_non_zero_digit(char c) { return (s21_isdigit(c) && c != '0'); }

int s21_isalpha(int c) {
  return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int s21_isdigit(int c) { return (c >= '0' && c <= '9'); }
int is_format_specifier(char c) {
  const char *spec = "duXxofeEgGpcs%";

  while (*spec != '\0') {
    if (c == *spec) return 1;
    spec++;
  }
  return 0;
}

void reverse(char *str) {
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = temp;
  }
}

int sign(long double num) {
  int flag = 0;
  if (num > 0)
    flag = 1;
  else if (num < 0)
    flag = -1;
  return flag;
}

void insert_char_at_start(char *str, char c) {
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = len + 1; i > 0; i--) {
    str[i] = str[i - 1];
  }
  str[0] = c;
}

void remove_zeros(char *str) {
  s21_size_t len = s21_strlen(str) - 1;
  while (len > 0 && str[len] == '0') {
    str[len] = '\0';
    len--;
  }
  if (str[len] == '.') {
    str[len] = '\0';
  }
}

int number_of_digits(long long x) {
  x = llabs(x);
  int k = 0;
  while (x >= 1) {
    x = x / 10;
    k++;
  }
  return k;
}

void make_char_from_int(char *str, long long x) {
  int len = number_of_digits(x);
  long long rank = pow(10, len - 1);
  int k = s21_strlen(str);
  if (rank == 0) {
    str[k] = '0';
    k++;
  }
  if (len < UNIT_LENGTH) {
    while (rank > 0) {
      str[k] = '0' + x / rank;
      x = x % rank;
      rank = rank / 10;
      k++;
    }
    str[k] = '\0';
  }
}

void to_octal(char *num_str, unsigned long x) {
  int k = s21_strlen(num_str);
  int len = number_of_digits(x);

  if (len < UNIT_LENGTH) {
    while (x > 0) {
      num_str[k] = '0' + x % 8;
      x = x / 8;
      k++;
    }
    num_str[k] = '\0';

    reverse(num_str);
  }
}

void to_hex(char *num_str, unsigned long x) {
  int k = 0;
  int rem;

  int len = number_of_digits(x);

  if (len < UNIT_LENGTH) {
    while (x > 0) {
      rem = x % 16;
      if (rem >= 10 && rem <= 15)
        num_str[k] = 87 + rem;
      else
        num_str[k] = '0' + rem;
      x = x / 16;
      k++;
    }
    num_str[k] = '\0';
    reverse(num_str);
  }
}

void width_process(char *str, s21_size_t len, int width, int minus_flag,
                   char fill_sym) {
  int diff = width - len;
  if (diff > 0) {
    if (minus_flag) {
      for (int t = 0; t < diff; t++) str[len + t] = fill_sym;
      str[width] = '\0';
    } else {
      for (int i = len - 1; i > -1; i--) str[i + diff] = str[i];
      for (int t = 0; t < diff; t++) str[t] = fill_sym;
    }
    str[width] = '\0';
  }
}

void c_mod_process(char *add_str, Modifiers *mods, va_list *ap) {
  setlocale(LC_ALL, "");

  if (mods->mod == 'l') {
    wchar_t wsymbol = va_arg(*ap, wchar_t);
    int ret = wctomb(add_str, wsymbol);
    add_str[ret] = '\0';
  } else {
    char symbol = (char)va_arg(*ap, int);
    add_str[0] = symbol;
    add_str[1] = '\0';
  }
  width_process(add_str, s21_strlen(add_str), mods->width, mods->minus_flag,
                mods->zero_flag ? '0' : ' ');
}

void s_mod_process(char *add_str, Modifiers *mods, va_list *ap) {
  setlocale(LC_ALL, "");
  if (mods->mod == 'l') {
    wchar_t *wtemp_str = va_arg(*ap, wchar_t *);
    char mb_str[UNIT_LENGTH] = {0};

    s21_size_t ret = wcstombs(mb_str, wtemp_str, UNIT_LENGTH - 1);
    if (ret == (s21_size_t)-1) mb_str[0] = '\0';
    s21_strncat(add_str, mb_str, UNIT_LENGTH - s21_strlen(add_str) - 1);

  } else {
    char *temp_str = va_arg(*ap, char *);
    s21_strncpy(add_str, temp_str, UNIT_LENGTH - 1);
    add_str[UNIT_LENGTH - 1] = '\0';
  }
  if (mods->is_pres_for_other) add_str[mods->pres_other] = '\0';
  width_process(add_str, s21_strlen(add_str), mods->width, mods->minus_flag,
                mods->zero_flag ? '0' : ' ');
}

void hash_mod_process(char *add_str, Modifiers *mods) {
  add_str[0] = '%';
  add_str[1] = '\0';
  width_process(add_str, s21_strlen(add_str), mods->width, mods->minus_flag,
                mods->zero_flag ? '0' : ' ');
}

void mod_pres(char sec_spec, char third_spec, s21_size_t *i, Modifiers *mods) {
  if (sec_spec == '*') {
    mods->pres_star_flag = 1;
    mods->is_pres_for_other = 1;
    (*i) += 1;
  } else if (s21_isalpha(sec_spec)) {
    mods->pres = 0;
    mods->pres_other = 0;
    mods->is_pres_for_other = 1;
  } else if (s21_isdigit(sec_spec)) {
    if (s21_isdigit(third_spec)) {
      mods->pres = 10 * (sec_spec - '0') + third_spec - '0';
      mods->pres_other = 10 * (third_spec - '0') + third_spec - '0';
      mods->is_pres_for_other = 1;
      (*i) += 1;
    } else {
      mods->pres = sec_spec - '0';
      mods->pres_other = sec_spec - '0';
      mods->is_pres_for_other = 1;
    }
    (*i) += 1;
  }
  mods->pow_pres = pow(10, mods->pres);
}

void mod_process(char spec, char sec_spec, char third_spec, s21_size_t *i,
                 Modifiers *mods) {
  if (spec == '-') mods->minus_flag = 1;
  if (spec == '+') mods->plus_flag = 1;
  if (spec == '0') mods->zero_flag = 1;
  if (spec == '#') mods->hash_flag = 1;
  if (spec == ' ') mods->space_flag = 1;

  if (spec == '*') mods->width_star_flag = 1;

  if (is_non_zero_digit(spec)) {
    if (s21_isdigit(sec_spec)) {
      mods->width = 10 * (spec - '0') + sec_spec - '0';
      (*i) += 1;
    } else
      mods->width = spec - '0';
  }

  if (spec == '.') mod_pres(sec_spec, third_spec, i, mods);

  if (s21_isalpha(spec) && (spec == 'l' || spec == 'h' || spec == 'L')) {
    if (spec == 'l') mods->mod = 'l';
    if (spec == 'h') mods->mod = 'h';
    if (spec == 'L') mods->mod = 'L';
  }
}

void read_variable(char spec, void *x, Modifiers *mods, va_list *ap) {
  int is_unsigned = (spec == 'u' || spec == 'x' || spec == 'X' || spec == 'o');

  if (is_unsigned) {
    unsigned long long val = 0;
    if (mods->mod == 'l')
      val = va_arg(*ap, unsigned long);
    else if (mods->mod == 'h')
      val = (unsigned short)va_arg(*ap, unsigned int);
    else
      val = va_arg(*ap, unsigned int);

    *(unsigned long long *)x = val;

  } else {
    long long val = 0;
    if (mods->mod == 'l')
      val = va_arg(*ap, long);
    else if (mods->mod == 'h')
      val = (short)va_arg(*ap, int);
    else
      val = va_arg(*ap, int);
    *(long long *)x = val;
  }
}

void d_u_mod_process(char spec, char *add_str, Modifiers *mods, va_list *ap) {
  long long x = 0;
  read_variable(spec, &x, mods, ap);
  int is_neg = (x < 0);
  int should_print_zero = !(x == 0 && mods->pres == 0);

  int width_du = mods->width;

  if (should_print_zero) make_char_from_int(add_str, labs(x));

  if (mods->is_pres_for_other)
    width_process(add_str, s21_strlen(add_str), mods->pres, 0, '0');

  if (should_print_zero) {
    int shift = (is_neg || mods->plus_flag || mods->space_flag) ? 1 : 0;

    if (mods->zero_flag)
      width_process(add_str, s21_strlen(add_str), width_du - shift,
                    mods->minus_flag, '0');

    if (is_neg)
      insert_char_at_start(add_str, '-');
    else if (mods->plus_flag)
      insert_char_at_start(add_str, '+');
    else if (mods->space_flag)
      insert_char_at_start(add_str, ' ');

    if (!mods->zero_flag)
      width_process(add_str, s21_strlen(add_str), width_du, mods->minus_flag,
                    mods->zero_flag ? '0' : ' ');
  }
}

void x_o_mod_process(char spec, char *add_str, Modifiers *mods, va_list *ap) {
  long long x = 0;
  read_variable(spec, &x, mods, ap);
  int should_print_zero = !(x == 0 && mods->pres == 0);

  char *num_str = malloc(UNIT_LENGTH * sizeof(char));
  num_str[0] = '\0';
  if (x != 0) {
    if (spec == 'x' || spec == 'X') to_hex(num_str, x);
    if (spec == 'o') to_octal(num_str, x);
  }

  if (should_print_zero && mods->is_pres_for_other)
    width_process(num_str, s21_strlen(num_str), mods->pres, 0, '0');

  if (should_print_zero && x == 0)
    s21_strncat(add_str, "0", UNIT_LENGTH);

  else if (x != 0) {
    if (mods->hash_flag && (x != 0)) {
      if (spec == 'x' || spec == 'X') {
        insert_char_at_start(num_str, 'x');

        insert_char_at_start(num_str, '0');
      }
      if (spec == 'o') insert_char_at_start(num_str, '0');
    }
  }
  s21_strncat(add_str, num_str, UNIT_LENGTH);

  if (spec == 'X') s21_to_upper_in_place(add_str);
  width_process(add_str, s21_strlen(add_str), mods->width, mods->minus_flag,
                mods->zero_flag ? '0' : ' ');

  free(num_str);
}

void print_float(int is_negative, int f_width, char *add_str, Modifiers *mods) {
  if (mods->zero_flag) {
    if (is_negative || mods->space_flag || mods->plus_flag)
      f_width = mods->width - 1;
    width_process(add_str, s21_strlen(add_str), f_width, mods->minus_flag,
                  mods->zero_flag ? '0' : ' ');
  }

  if (is_negative) insert_char_at_start(add_str, '-');
  if (mods->plus_flag && !is_negative)
    insert_char_at_start(add_str, '+');
  else if (mods->space_flag && !is_negative)
    insert_char_at_start(add_str, ' ');

  if (mods->g_spec) remove_zeros(add_str);

  if (!mods->zero_flag) {
    width_process(add_str, s21_strlen(add_str), f_width, mods->minus_flag,
                  mods->zero_flag ? '0' : ' ');
  }
}

void f_mod_process(long double y, char *add_str, Modifiers *mods) {
  int is_negative = signbit(y);
  int f_width = mods->width;

  y = fabsl(y);
  char *fract_part = malloc(UNIT_LENGTH * sizeof(char));
  fract_part[0] = '\0';

  if (mods->pres == 0) {
    y = round(y);
    make_char_from_int(add_str, y);
  } else {
    if (trunc(y) > 0)
      make_char_from_int(add_str, trunc(y));
    else
      s21_strncat(add_str, "0", UNIT_LENGTH);
  }

  long double fract_part_num = fabsl(y - trunc(y));
  long long powed_sec_part = round(mods->pow_pres * fract_part_num);

  make_char_from_int(fract_part, powed_sec_part);

  if (!mods->hash_flag) remove_zeros(add_str);
  if (mods->pres > 0) {
    s21_strncat(add_str, ".", UNIT_LENGTH);
    width_process(fract_part, s21_strlen(fract_part), mods->pres, 0, '0');
    s21_strncat(add_str, fract_part, UNIT_LENGTH);
  } else if (mods->hash_flag)
    s21_strncat(add_str, ".", UNIT_LENGTH);

  print_float(is_negative, f_width, add_str, mods);

  free(fract_part);
}

void e_mod_process(char spec, long double y, int power, char *add_str,
                   Modifiers *mods) {
  int is_negative = signbit(y);
  char *exp_format = malloc(UNIT_LENGTH * sizeof(char));
  exp_format[0] = '\0';
  char *fract_part = malloc(UNIT_LENGTH * sizeof(char));
  fract_part[0] = '\0';
  char *sign = "+";

  y = fabsl(y);
  y = y / pow(10, number_of_digits(y) - 1);

  long double fract_part_num = fabsl(y - trunc(y));
  make_char_from_int(add_str, trunc(y));
  make_char_from_int(fract_part,
                     round(mods->pow_pres * (fract_part_num + 1e-6L)));

  if (!mods->hash_flag && (spec == 'x' || spec == 'X'))
    remove_zeros(fract_part);
  if (mods->pres > 0) {
    s21_strncat(add_str, ".", UNIT_LENGTH);
    width_process(fract_part, s21_strlen(fract_part), mods->pres, 0, '0');
    s21_strncat(add_str, fract_part, UNIT_LENGTH);
  } else if (mods->hash_flag)
    s21_strncat(add_str, ".", UNIT_LENGTH);

  if (mods->g_spec) remove_zeros(add_str);

  s21_strncat(add_str, spec == 'e' ? "e" : "E", UNIT_LENGTH);
  sign = (power < 0 ? "-\0" : "+\0");

  make_char_from_int(exp_format, abs(power));
  width_process(exp_format, s21_strlen(exp_format), 2, 0, '0');
  s21_strncat(add_str, sign, UNIT_LENGTH);
  s21_strncat(add_str, exp_format, UNIT_LENGTH);
  print_float(is_negative, mods->width, add_str, mods);

  free(exp_format);
  free(fract_part);
}

int get_power_and_float(void *y, void *orig_y, Modifiers *mods, va_list *ap) {
  int len_fract_part = 0;
  int find = 0;
  long double temp_y = 0;

  if (mods->mod == 'L')
    temp_y = va_arg(*ap, long double);
  else
    temp_y = va_arg(*ap, double);
  *(long double *)orig_y = temp_y;

  float fract_part_num = fabsl(temp_y - trunc(temp_y));

  if (temp_y != 0 && fabsl(temp_y) < 1.0) {
    while (find == 0) {
      if (pow(10, len_fract_part) * fract_part_num > 1) find = 1;
      len_fract_part++;
    }
    temp_y = sign(temp_y) * pow(10, len_fract_part - 1) * fract_part_num;
  }

  int len = number_of_digits(temp_y);
  int power = len - len_fract_part;
  if (power > 0) power--;
  *(long double *)y = temp_y;
  return power;
}

void g_mod_process(char spec, char *add_str, Modifiers *mods, va_list *ap) {
  long double y;
  long double orig_y;
  mods->pow_pres = powl(10.0L, mods->pres);
  int power = get_power_and_float(&y, &orig_y, mods, ap);
  int not_nan_inf = 1;

  if (isnan(y)) {
    s21_strncat(add_str, "nan", UNIT_LENGTH);
    not_nan_inf = 0;
  }

  if (isinf(y)) {
    if (signbit(y))
      s21_strncat(add_str, "-inf", UNIT_LENGTH);
    else
      s21_strncat(add_str, "inf", UNIT_LENGTH);
    not_nan_inf = 0;
  }

  if (not_nan_inf) {
    if (spec == 'e' || spec == 'E')
      e_mod_process(spec == 'e' ? 'e' : 'E', y, power, add_str, mods);
    else if (spec == 'f')
      f_mod_process(orig_y, add_str, mods);
    else {
      mods->g_spec = 1;
      int p = mods->pres;
      if (mods->pres == 0) p = 1;

      if (p > power && power >= -4) {
        mods->pres = p - 1 - power;
        mods->pow_pres = powl(10.0L, mods->pres);
        f_mod_process(orig_y, add_str, mods);
      } else {
        mods->pres = mods->pres - 1;
        mods->pow_pres = powl(10.0L, mods->pres);
        e_mod_process(spec == 'g' ? 'e' : 'E', y, power, add_str, mods);
      }
    }
  }
}

void spec_procees(s21_size_t *index, int *k, s21_size_t string_len, char *str,
                  char *add_str, const char *format, Modifiers *mods,
                  va_list *ap) {
  s21_size_t i = *index;

  while ((i + 3 < string_len) && (!is_format_specifier(format[i + 1]))) {
    mod_process(format[i + 1], format[i + 2], format[i + 3], &i, mods);
    i++;
  }

  if (mods->width_star_flag) mods->width = va_arg(*ap, int);
  if (mods->pres_star_flag) mods->pres = va_arg(*ap, int);

  if (mods->width > UNIT_LENGTH) mods->width = UNIT_LENGTH;
  if (mods->pres > UNIT_LENGTH) mods->pres = UNIT_LENGTH;

  if (format[i + 1] == 'c') c_mod_process(add_str, mods, ap);
  if (format[i + 1] == 's') s_mod_process(add_str, mods, ap);
  if (format[i + 1] == 'p') p_mod_process(add_str, ap);
  if (format[i + 1] == '%') hash_mod_process(add_str, mods);

  if (format[i + 1] == 'd' || format[i + 1] == 'u')
    d_u_mod_process(format[i + 1], add_str, mods, ap);
  if (format[i + 1] == 'x' || format[i + 1] == 'X' || format[i + 1] == 'o')
    x_o_mod_process(format[i + 1], add_str, mods, ap);
  if (format[i + 1] == 'f' || format[i + 1] == 'e' || format[i + 1] == 'E' ||
      format[i + 1] == 'g' || format[i + 1] == 'G') {
    g_mod_process(format[i + 1], add_str, mods, ap);
  }
  i++;
  *k += s21_strlen(add_str);
  *index = i;
  s21_strncat(str, add_str, UNIT_LENGTH);
}

void p_mod_process(char *buf, va_list *ap) {
  void *ptr = va_arg(*ap, void *);
  s21_size_t address = (s21_size_t)ptr;

  char temp[2 + sizeof(s21_size_t) * 2 + 1];
  to_hex(temp, address);

  s21_strncat(buf, "0x", UNIT_LENGTH);
  s21_strncat(buf, temp, UNIT_LENGTH);
}
