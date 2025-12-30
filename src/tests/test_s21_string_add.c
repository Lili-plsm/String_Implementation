#include <check.h>
#include <stdlib.h>

#include "../s21_string.h"

START_TEST(test_s21_to_upper_basic) {
  const char *s = "abcXYZ123!";
  char *res = s21_to_upper(s);
  ck_assert_str_eq(res, "ABCXYZ123!");
  free(res);
}
END_TEST

START_TEST(test_s21_to_upper_empty) {
  const char *s = "";
  char *res = s21_to_upper(s);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_s21_to_upper_null) {
  ck_assert_ptr_null(s21_to_upper(S21_NULL));
}
END_TEST

START_TEST(test_s21_to_lower_basic) {
  const char *s = "ABCxyz123!";
  char *res = s21_to_lower(s);
  ck_assert_str_eq(res, "abcxyz123!");
  free(res);
}
END_TEST

START_TEST(test_s21_to_lower_empty) {
  const char *s = "";
  char *res = s21_to_lower(s);
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_s21_to_lower_null) {
  ck_assert_ptr_null(s21_to_lower(S21_NULL));
}
END_TEST

START_TEST(test_s21_insert_middle) {
  const char *src = "HelloWorld";
  const char *ins = "_my_";
  char *res = s21_insert(src, ins, 6);
  ck_assert_str_eq(res, "Hello_my_World");
  free(res);
}
END_TEST

START_TEST(test_s21_insert_out_of_bounds_high) {
  const char *src = "StartEnd";
  char *res = s21_insert(src, "Back", strlen(src) + 2);
  ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_s21_insert_invalid_index) {
  const char *src = "StartEnd";
  char *res = s21_insert(src, "Fail", 100);
  ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_s21_trim_general) {
  const char *src = "__abc_pupa_pupa_def___";
  const char *trim_chars = "_pa";
  char *res = s21_trim(src, trim_chars);
  ck_assert_str_eq(res, "bc_pupa_pupa_def");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_empty_str) {
  char *res = s21_trim("", "abc");
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_empty_chars) {
  char *res = s21_trim("abc", "");
  ck_assert_str_eq(res, "abc");
  free(res);
}
END_TEST

START_TEST(test_s21_trim_null_src) {
  ck_assert_ptr_null(s21_trim(S21_NULL, "abc"));
}
END_TEST

START_TEST(test_s21_trim_null_chars) {
  ck_assert_ptr_null(s21_trim("abc", S21_NULL));
}
END_TEST

Suite *string_suite_add(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("String_add");
  tc_core = tcase_create("Core");

  /* test s21_to_upper */
  tcase_add_test(tc_core, test_s21_to_upper_basic);
  tcase_add_test(tc_core, test_s21_to_upper_empty);
  tcase_add_test(tc_core, test_s21_to_upper_null);
  /* test s21_to_lower */
  tcase_add_test(tc_core, test_s21_to_lower_basic);
  tcase_add_test(tc_core, test_s21_to_lower_empty);
  tcase_add_test(tc_core, test_s21_to_lower_null);
  /* test s21_insert */
  tcase_add_test(tc_core, test_s21_insert_middle);
  tcase_add_test(tc_core, test_s21_insert_out_of_bounds_high);
  tcase_add_test(tc_core, test_s21_insert_invalid_index);
  /* test s21_trim */
  tcase_add_test(tc_core, test_s21_trim_general);
  tcase_add_test(tc_core, test_s21_trim_empty_str);
  tcase_add_test(tc_core, test_s21_trim_empty_chars);
  tcase_add_test(tc_core, test_s21_trim_null_src);
  tcase_add_test(tc_core, test_s21_trim_null_chars);

  suite_add_tcase(s, tc_core);

  return s;
}
