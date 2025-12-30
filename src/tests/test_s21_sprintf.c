#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_1) {
  char str1[2000], str2[2000];
  double nan_val = NAN, pos_inf = INFINITY, neg_inf = -INFINITY;

  const char *f1 = "|%f| |%e| |%g| |%f|";
  s21_sprintf(str1, f1, nan_val, pos_inf, neg_inf, -0.0);
  sprintf(str2, f1, nan_val, pos_inf, neg_inf, -0.0);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char str1[2000], str2[2000];
  double fl = -12345.6789, small = -0.0000004892, big = 123456789.0;

  const char *f2 = "|%+#12.3f| |% -10.5e| |%#08g| |%020.4G|";
  s21_sprintf(str1, f2, fl, small, big, big);
  sprintf(str2, f2, fl, small, big, big);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char str1[2000], str2[2000];
  int i = -42;
  unsigned u = 3000000000U;

  const char *f3 = "|%d| |%#10x| |%#10o| |%-10u|";
  s21_sprintf(str1, f3, i, i, i, u);
  sprintf(str2, f3, i, i, i, u);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char str1[2000], str2[2000];
  char ch = 'A';
  const char *s = "Hello, world!";

  const char *f4 = "|%5c| |%-15s| |%.7s| |%20.5s|";
  s21_sprintf(str1, f4, ch, s, s, s);
  sprintf(str2, f4, ch, s, s, s);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char str1[2000], str2[2000];
  short sh = SHRT_MAX;
  long lg = LONG_MAX;
  long double ld = 432342422423424.4323422423424L;

  const char *f5 = "|%hd| |%ld| |%Lf|";
  s21_sprintf(str1, f5, sh, lg, ld);
  sprintf(str2, f5, sh, lg, ld);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char str1[2000], str2[2000];
  double fl = -12345.6789, small = -0.0000005892, big = 123456789.0;

  const char *f6 = "|%*.*f| |%*.*e| |%*.*g|";
  s21_sprintf(str1, f6, 10, 3, fl, 12, 3, small, 14, 5, big);
  sprintf(str2, f6, 10, 3, fl, 12, 3, small, 14, 5, big);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char str1[2000], str2[2000];
  int i = -42;
  int *ptr = &i;

  const char *f7 = "|%p| |%%| |%#x| |%#o|";
  s21_sprintf(str1, f7, ptr, i, i);
  sprintf(str2, f7, ptr, i, i);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char str1[2000], str2[2000];
  long double ld = 432342422423424.4323422423424L;
  int i = -42;

  const char *f8 = "|%-+#20.10Lf| |%#08.3x| |%+10.5d|";
  s21_sprintf(str1, f8, ld, i, i);
  sprintf(str2, f8, ld, i, i);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char str1[2000], str2[2000];

  const char *f9 = "|%.19ls| |%lc|";
  s21_sprintf(str1, f9, L"Proverochka€", L'€');
  sprintf(str2, f9, L"Proverochka€", L'€');

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char str1[2000], str2[2000];
  double val = 0.0;

  const char *f = "|%+f| |% f| |%-f| |%0f|";
  s21_sprintf(str1, f, val, val, val, val);
  sprintf(str2, f, val, val, val, val);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char str1[2000], str2[2000];
  int a = 22, b = -1;

  const char *f = "|%#x| |%.17o| |%#X| |%#o|";
  s21_sprintf(str1, f, a, a, b, b);
  sprintf(str2, f, a, a, b, b);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char str1[2000], str2[2000];
  unsigned u = 4294967295U;

  const char *f = "|%010u| |%-10u| |%#x| |%#o|";
  s21_sprintf(str1, f, u, u, u, u);
  sprintf(str2, f, u, u, u, u);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_13) {
  char str1[2000], str2[2000];
  int a = 123, width = 10, prec = 5;

  const char *f = "|%*.*d|";
  s21_sprintf(str1, f, width, prec, a);
  sprintf(str2, f, width, prec, a);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_14) {
  char str1[2000], str2[2000];
  wchar_t wc = L'Ж';
  const wchar_t *ws = L"Юникод";

  const char *f = "|%lc| |%ls|";
  s21_sprintf(str1, f, wc, ws);
  sprintf(str2, f, wc, ws);

  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *sprintf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sprintf");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  tcase_add_test(tc_core, test_5);
  tcase_add_test(tc_core, test_6);
  tcase_add_test(tc_core, test_7);
  tcase_add_test(tc_core, test_8);
  tcase_add_test(tc_core, test_9);
  tcase_add_test(tc_core, test_10);
  tcase_add_test(tc_core, test_11);
  tcase_add_test(tc_core, test_12);
  tcase_add_test(tc_core, test_13);
  tcase_add_test(tc_core, test_14);
  suite_add_tcase(s, tc_core);

  return s;
}
