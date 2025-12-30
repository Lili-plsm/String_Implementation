#include <check.h>
#include <string.h>

#include "../s21_string.h"

START_TEST(test_s21_strlen) {
  const char *test_str = "Test the length of a string";
  ck_assert_uint_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_s21_strlen_zero_length) {
  const char *test_str = "\0";
  ck_assert_uint_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_s21_memchr) {
  const char *test_str = "Scan memory for a character";
  ck_assert(s21_memchr(test_str, 'S', 28) == memchr(test_str, 'S', 28));
}
END_TEST

START_TEST(test_s21_memchr_found_at_end) {
  const char *test_str = "Scan memory for a character!";
  ck_assert(s21_memchr(test_str, '!', 29) == memchr(test_str, '!', 29));
}
END_TEST

START_TEST(test_s21_memchr_found_in_middle) {
  const char *test_str = "Scan memory fo!r a character";
  ck_assert(s21_memchr(test_str, '!', 29) == memchr(test_str, '!', 29));
}
END_TEST

START_TEST(test_s21_memchr_zero_length) {
  const char *test_str = "Scan memory fo!r a character";
  ck_assert(s21_memchr(test_str, '!', 0) == memchr(test_str, '!', 0));
}
END_TEST

START_TEST(test_s21_memchr_null_terminator) {
  const char *test_str = "Scan memory fo\0r a character";
  ck_assert(s21_memchr(test_str, '\0', 29) == memchr(test_str, '\0', 29));
}
END_TEST

START_TEST(test_s21_memchr_not_found) {
  const char *test_str = "Scan memory for a character";
  ck_assert(s21_memchr(test_str, '!', 28) == memchr(test_str, '!', 28));
}
END_TEST

START_TEST(test_s21_memchr_beyond_null) {
  const char *test_str = "Scan memory\0 for a character";
  ck_assert(s21_memchr(test_str, 'f', 29) == memchr(test_str, 'f', 29));
}
END_TEST

START_TEST(test_s21_memchr_non_ASCII) {
  const char *test_str = "ab\xFF a";
  ck_assert(s21_memchr(test_str, '\xFF', 6) == memchr(test_str, '\xFF', 6));
}
END_TEST

START_TEST(test_s21_memcpy) {
  const char *dest[10];
  ck_assert_str_eq(s21_memcpy(dest, "school 21", 10),
                   memcpy(dest, "school 21", 10));
}
END_TEST

START_TEST(test_s21_memcpy_zero_bytes) {
  const char *dest[10];
  ck_assert_str_eq(s21_memcpy(dest, "school 21", 0),
                   memcpy(dest, "school 21", 0));
}
END_TEST

START_TEST(test_s21_memcpy_single_byte) {
  const char *dest[10];
  ck_assert_str_eq(s21_memcpy(dest, "1", 1), memcpy(dest, "1", 1));
}
END_TEST

START_TEST(test_s21_memcmp_eq) {
  const char *str1 = "school 21";
  const char *str2 = "school 21";
  ck_assert_int_eq(s21_memcmp(str1, str2, 10), memcmp(str1, str2, 10));
}
END_TEST

START_TEST(test_s21_memcmp_not_eq) {
  const char *str1 = "school 21";
  const char *str2 = "21 school";
  int res = memcmp(str1, str2, 10);
  int s21_res = s21_memcmp(str1, str2, 10);
  ck_assert_int_gt(res, 0);
  ck_assert_int_gt(s21_res, 0);
}
END_TEST

START_TEST(test_s21_memcmp_zero_length) {
  const char *str1 = "school 21";
  const char *str2 = "21 school";
  ck_assert_int_eq(s21_memcmp(str1, str2, 0), memcmp(str1, str2, 0));
}
END_TEST

START_TEST(test_s21_memcmp_partial_eq) {
  const char *str1 = "school 21";
  const char *str2 = "school 32";
  ck_assert_int_eq(s21_memcmp(str1, str2, 6), memcmp(str1, str2, 6));
}
END_TEST

START_TEST(test_s21_memcmp_non_ASCII) {
  const char *str1 = "\xFF\x00";
  const char *str2 = "\xFE\x00";
  ck_assert_int_eq(s21_memcmp(str1, str2, 2), memcmp(str1, str2, 2));
}
END_TEST

START_TEST(test_s21_memcmp_non_zero) {
  const char *str1 = "\0\0\0";
  const char *str2 = "abc";
  ck_assert_int_eq(s21_memcmp(str1, str2, 3), memcmp(str1, str2, 3));
}
END_TEST

START_TEST(test_s21_memcmp_same_ptr) {
  const char *str1 = "school 21";
  ck_assert_int_eq(s21_memcmp(str1, str1, 10), memcmp(str1, str1, 10));
}
END_TEST

START_TEST(test_s21_memset) {
  int buf[10];
  int s21_buf[10];
  size_t size = 10 * sizeof(int);
  ck_assert_mem_eq(s21_memset(s21_buf, 0, size), memset(buf, 0, size), size);
}
END_TEST

START_TEST(test_s21_memset_char) {
  char buf[10];
  char s21_buf[10];
  size_t size = 10 * sizeof(char);
  ck_assert_mem_eq(s21_memset(s21_buf, 0x41, size), memset(buf, 0x41, size),
                   size);
}
END_TEST

START_TEST(test_s21_memset_single_byte) {
  char buf[2];
  char s21_buf[2];
  ck_assert_mem_eq(s21_memset(s21_buf, 0xFF, 1), memset(buf, 0xFF, 1), 1);
}
END_TEST

START_TEST(test_s21_memset_zero_length) {
  int buf[2];
  int s21_buf[2];
  ck_assert_mem_eq(s21_memset(s21_buf, 3, 0), memset(buf, 3, 0), 0);
}
END_TEST

START_TEST(test_s21_memset_negative_val) {
  int buf[2];
  int s21_buf[2];
  size_t size = 2 * sizeof(int);
  ck_assert_mem_eq(s21_memset(s21_buf, -1, size), memset(buf, -1, size), size);
}
END_TEST

START_TEST(test_s21_strncat) {
  char dest[10] = "school ";
  char s21_dest[10] = "school ";
  ck_assert_str_eq(s21_strncat(s21_dest, "21", 3), strncat(dest, "21", 3));
}
END_TEST

START_TEST(test_s21_strncat_partial) {
  char dest[10] = "school ";
  char s21_dest[10] = "school ";
  ck_assert_str_eq(s21_strncat(s21_dest, "21", 2), strncat(dest, "21", 2));
}
END_TEST

START_TEST(test_s21_strncat_empty_src) {
  char dest[10] = "school ";
  char s21_dest[10] = "school ";
  ck_assert_str_eq(s21_strncat(s21_dest, "", 2), strncat(dest, "", 2));
}
END_TEST

START_TEST(test_s21_strncat_empty_dest) {
  char dest[10] = "";
  char s21_dest[10] = "";
  ck_assert_str_eq(s21_strncat(s21_dest, "school 21", 10),
                   strncat(dest, "school 21", 10));
}
END_TEST

START_TEST(test_s21_strncat_zero_length) {
  char dest[10] = "school ";
  char s21_dest[10] = "school ";
  ck_assert_str_eq(s21_strncat(s21_dest, "21", 0), strncat(dest, "21", 0));
}
END_TEST

START_TEST(test_s21_strncat_larger_length) {
  char dest[10] = "school ";
  char s21_dest[10] = "school ";
  ck_assert_str_eq(s21_strncat(s21_dest, "21", 5), strncat(dest, "21", 5));
}
END_TEST

START_TEST(test_s21_strchr) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strchr(str, 's'), strchr(str, 's'));
}
END_TEST

START_TEST(test_s21_strchr_middle) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strchr(str, 'o'), strchr(str, 'o'));
}
END_TEST

START_TEST(test_s21_strchr_end) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strchr(str, '1'), strchr(str, '1'));
}
END_TEST

START_TEST(test_s21_strchr_not_found) {
  const char *str = "school 21";
  ck_assert(s21_strchr(str, '3') == strchr(str, '3'));
}
END_TEST

START_TEST(test_s21_strchr_search_for_null) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_s21_strchr_search_for_null_mid) {
  const char *str = "scho\0ol 21";
  ck_assert_str_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(test_s21_strchr_empty) {
  const char *str = "";
  ck_assert(s21_strchr(str, '2') == strchr(str, '2'));
}
END_TEST

START_TEST(test_s21_strchr_unsigned_chr) {
  const char *str = "school 21";
  ck_assert(s21_strchr(str, -1) == strchr(str, -1));
}
END_TEST

START_TEST(test_s21_strchr_same_ptr) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strchr(str, str[0]), strchr(str, str[0]));
}
END_TEST

START_TEST(test_s21_strncmp) {
  const char *str1 = "school 21";
  const char *str2 = "school 21";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_s21_strncmp_smaller) {
  const char *str1 = "achool 21";
  const char *str2 = "school 21";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_s21_strncmp_larger) {
  const char *str1 = "school 21";
  const char *str2 = "achool 21";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_s21_strncmp_zero_length) {
  const char *str1 = "abc";
  const char *str2 = "vbn";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0), strncmp(str1, str2, 0));
}
END_TEST

START_TEST(test_s21_strncmp_null_cmp_str1) {
  const char *str1 = "school 2";
  const char *str2 = "school 21";
  ck_assert_int_eq(s21_strncmp(str1, str2, 9), strncmp(str1, str2, 9));
}
END_TEST

START_TEST(test_s21_strncmp_null_cmp_str2) {
  const char *str1 = "school 21";
  const char *str2 = "school 2";
  ck_assert_int_eq(s21_strncmp(str1, str2, 9), strncmp(str1, str2, 9));
}
END_TEST

START_TEST(test_s21_strncmp_null_mid) {
  const char *str1 = "schoo\0l 21";
  const char *str2 = "schoo\0w 44";
  ck_assert_int_eq(s21_strncmp(str1, str2, 11), strncmp(str1, str2, 11));
}
END_TEST

START_TEST(test_s21_strncmp_null_one_str) {
  const char *str1 = "school 21";
  const char *str2 = "sc\0hoow 44";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10), strncmp(str1, str2, 10));
}
END_TEST

START_TEST(test_s21_strncmp_partianl_eq) {
  const char *str1 = "school 21";
  const char *str2 = "school 44";
  ck_assert_int_eq(s21_strncmp(str1, str2, 7), strncmp(str1, str2, 7));
}
END_TEST

START_TEST(test_s21_strncmp_same_ptr) {
  const char *str1 = "school 21";
  ck_assert_int_eq(s21_strncmp(str1, str1, 10), strncmp(str1, str1, 10));
}
END_TEST

START_TEST(test_s21_strncpy) {
  char dest[10];
  char s21_dest[10];
  const char *str = "school 21";
  s21_strncpy(s21_dest, str, 10);
  strncpy(dest, str, 10);
  ck_assert_mem_eq(dest, s21_dest, 10);
}
END_TEST

START_TEST(test_s21_strncpy_exact_len) {
  char dest[10];
  char s21_dest[10];
  const char *str = "school 21";
  s21_strncpy(s21_dest, str, 9);
  strncpy(dest, str, 9);
  ck_assert_mem_eq(dest, s21_dest, 9);
}
END_TEST

START_TEST(test_s21_strncpy_partial_cpy) {
  char dest[10];
  char s21_dest[10];
  const char *str = "school 21";
  s21_strncpy(s21_dest, str, 5);
  strncpy(dest, str, 5);
  ck_assert_mem_eq(dest, s21_dest, 5);
}
END_TEST

START_TEST(test_s21_strncpy_null_padding) {
  char dest[10] = "school 21";
  char s21_dest[10] = "school 21";
  const char *str = "21";
  s21_strncpy(s21_dest, str, 10);
  strncpy(dest, str, 10);
  ck_assert_mem_eq(dest, s21_dest, 10);
}
END_TEST

START_TEST(test_s21_strncpy_zero_length) {
  char dest[10] = "school 21";
  char s21_dest[10] = "school 21";
  const char *str = "21";
  s21_strncpy(s21_dest, str, 0);
  strncpy(dest, str, 0);
  ck_assert_mem_eq(dest, s21_dest, 10);
}
END_TEST

START_TEST(test_s21_strncpy_embedded_null) {
  char dest[10];
  char s21_dest[10];
  const char *str = "sch\0ool 2";
  s21_strncpy(s21_dest, str, 10);
  strncpy(dest, str, 10);
  ck_assert_mem_eq(dest, s21_dest, 10);
}
END_TEST

START_TEST(test_s21_strcspn) {
  const char *str = "school 21";
  const char *reject = "yui";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_start_match) {
  const char *str = "school 21";
  const char *reject = "s";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_mid_match) {
  const char *str = "school 21";
  const char *reject = "l";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_last_match) {
  const char *str = "school 21";
  const char *reject = "1";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_multiple_match) {
  const char *str = "school 21";
  const char *reject = "ol";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_empty_str) {
  const char *str = "";
  const char *reject = "ol";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_empty_reject) {
  const char *str = "school 21";
  const char *reject = "";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_empty_both) {
  const char *str = "";
  const char *reject = "";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_all_match) {
  const char *str = "aaaa";
  const char *reject = "a";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_null_str) {
  const char *str = "sch\0ool 21";
  const char *reject = "o";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_null_reject) {
  const char *str = "school 21";
  const char *reject = "\0";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_ASCII) {
  const char *str = "\xFF\x00";
  const char *reject = "\x00";
  ck_assert_int_eq(s21_strcspn(str, reject), strcspn(str, reject));
}
END_TEST

START_TEST(test_s21_strcspn_same_str) {
  const char *str = "school 21";
  ck_assert_int_eq(s21_strcspn(str, str), strcspn(str, str));
}
END_TEST

START_TEST(test_s21_strpbrk) {
  const char *str = "school 21";
  const char *accept = "s";
  ck_assert_str_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_mid_match) {
  const char *str = "school 21";
  const char *accept = "o";
  ck_assert_str_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_end_match) {
  const char *str = "school 21";
  const char *accept = "1";
  ck_assert_str_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_no_matches) {
  const char *str = "school 21";
  const char *accept = "4";
  ck_assert_pstr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_multiple_matches) {
  const char *str = "school 21";
  const char *accept = "o2";
  ck_assert_str_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str) {
  const char *str = "";
  const char *accept = "21";
  ck_assert_pstr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_accept) {
  const char *str = "school 21";
  const char *accept = "";
  ck_assert_pstr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_both) {
  const char *str = "";
  const char *accept = "";
  ck_assert_pstr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_all_match) {
  const char *str = "aaa";
  const char *accept = "a";
  ck_assert_str_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_null_str) {
  const char *str = "schoo\0l 21";
  const char *accept = "2";
  ck_assert_pstr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strpbrk_null_accept) {
  const char *str = "school 21";
  const char *accept = "\0";
  ck_assert_pstr_eq(s21_strpbrk(str, accept), strpbrk(str, accept));
}
END_TEST

START_TEST(test_s21_strrchr) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
}
END_TEST

START_TEST(test_s21_strrchr_mid_match) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strrchr(str, 'h'), strrchr(str, 'h'));
}
END_TEST

START_TEST(test_s21_strrchr_end_match) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strrchr(str, '1'), strrchr(str, '1'));
}
END_TEST

START_TEST(test_s21_strrchr_multiple_match) {
  const char *str = "school 21";
  ck_assert_str_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));
}
END_TEST

START_TEST(test_s21_strrchr_no_match) {
  const char *str = "school 21";
  ck_assert_pstr_eq(s21_strrchr(str, 'z'), strrchr(str, 'z'));
}
END_TEST

START_TEST(test_s21_strrchr_null) {
  const char *str = "scho\0ol 21";
  ck_assert_str_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(test_s21_strrchr_empty_str) {
  const char *str = "";
  ck_assert_pstr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
}
END_TEST

START_TEST(test_s21_strrchr_negative) {
  const char *str = "abc";
  ck_assert_pstr_eq(s21_strrchr(str, -1), strrchr(str, -1));
}
END_TEST

START_TEST(test_s21_strrchr_same_str) {
  const char *str = "school 21";
  ck_assert_pstr_eq(s21_strrchr(str, str[0]), strrchr(str, str[0]));
}
END_TEST

START_TEST(test_s21_strstr_end_match) {
  const char *haystack = "school 21";
  const char *needle = "21";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_mid_match) {
  const char *haystack = "school 21";
  const char *needle = "oo";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_start_match) {
  const char *haystack = "school 21";
  const char *needle = "school";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_no_match) {
  const char *haystack = "school 21";
  const char *needle = "55";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_multiple_matches) {
  const char *haystack = "school 21sc";
  const char *needle = "sc";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_needle) {
  const char *haystack = "school 21";
  const char *needle = "";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_haystack) {
  const char *haystack = "";
  const char *needle = "school";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_both) {
  const char *haystack = "";
  const char *needle = "";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_same_ptr) {
  const char *haystack = "school 21";
  ck_assert_str_eq(s21_strstr(haystack, haystack), strstr(haystack, haystack));
}
END_TEST

START_TEST(test_s21_strstr_null_haystack) {
  const char *haystack = "sch\0ool 21";
  const char *needle = "21";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_null_needle) {
  const char *haystack = "school 21";
  const char *needle = "o\0ol";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_ASCII) {
  const char *haystack = "\xFF\x00";
  const char *needle = "\x00";
  ck_assert_str_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_long_needle) {
  const char *haystack = "school";
  const char *needle = "school 21";
  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strtok) {
  char str1[] = "school 21";
  char str2[] = "school 21";
  const char *delim = " ";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_multiple_delims) {
  char str1[] = "school 21,22";
  char str2[] = "school 21,22";
  const char *delim = " ,";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "21"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "22"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_no_delim_in_str) {
  char str1[] = "school 21";
  char str2[] = "school 21";
  const char *delim = ",";

  ck_assert_str_eq(s21_strtok(str1, delim),
                   strtok(str2, delim));  // "school 21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_no_delim) {
  char str1[] = "school 21";
  char str2[] = "school 21";
  const char *delim = "";

  ck_assert_str_eq(s21_strtok(str1, delim),
                   strtok(str2, delim));  // "school 21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_consecutive_delim) {
  char str1[] = "school   21";
  char str2[] = "school   21";
  const char *delim = " ";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_interleaved) {
  char str1[] = "school 21";
  char str2[] = "school 21";
  char str3[] = "21,school";
  char str4[] = "21,school";
  const char *delim = " ";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(str3, ","), strtok(str4, ","));      // "21"
}
END_TEST

START_TEST(test_s21_strtok_empty_str) {
  char str1[] = "";
  char str2[] = "";
  const char *delim = ",";

  ck_assert_pstr_eq(s21_strtok(str1, delim), strtok(str2, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_all_delims) {
  char str1[] = ",,,";
  char str2[] = ",,,";
  const char *delim = ",";

  ck_assert_pstr_eq(s21_strtok(str1, delim), strtok(str2, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_delim_at_start) {
  char str1[] = ",school 21";
  char str2[] = ",school 21";
  const char *delim = ", ";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_delim_at_end) {
  char str1[] = ",school 21 ";
  char str2[] = ",school 21 ";
  const char *delim = ", ";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

START_TEST(test_s21_strtok_multiple_consecutive_delim) {
  char str1[] = ", ,school;; ,; 21 ";
  char str2[] = ", ,school;; ,; 21 ";
  const char *delim = ", ;";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));  // "school"
  ck_assert_str_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));   // "21"
  ck_assert_pstr_eq(s21_strtok(S21_NULL, delim), strtok(NULL, delim));  // NULL
}
END_TEST

Suite *string_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("String");
  tc_core = tcase_create("Core");

  /* test s21_strlen */
  tcase_add_test(tc_core, test_s21_strlen);
  tcase_add_test(tc_core, test_s21_strlen_zero_length);
  /* test s21_memchr */
  tcase_add_test(tc_core, test_s21_memchr);
  tcase_add_test(tc_core, test_s21_memchr_found_at_end);
  tcase_add_test(tc_core, test_s21_memchr_found_in_middle);
  tcase_add_test(tc_core, test_s21_memchr_zero_length);
  tcase_add_test(tc_core, test_s21_memchr_null_terminator);
  tcase_add_test(tc_core, test_s21_memchr_not_found);
  tcase_add_test(tc_core, test_s21_memchr_beyond_null);
  tcase_add_test(tc_core, test_s21_memchr_non_ASCII);
  /* test s21_memcpy */
  tcase_add_test(tc_core, test_s21_memcpy);
  tcase_add_test(tc_core, test_s21_memcpy_zero_bytes);
  tcase_add_test(tc_core, test_s21_memcpy_single_byte);
  /* test s21_memcmp */
  tcase_add_test(tc_core, test_s21_memcmp_eq);
  tcase_add_test(tc_core, test_s21_memcmp_not_eq);
  tcase_add_test(tc_core, test_s21_memcmp_zero_length);
  tcase_add_test(tc_core, test_s21_memcmp_partial_eq);
  tcase_add_test(tc_core, test_s21_memcmp_non_ASCII);
  tcase_add_test(tc_core, test_s21_memcmp_non_zero);
  tcase_add_test(tc_core, test_s21_memcmp_same_ptr);
  /* test s21_memset */
  tcase_add_test(tc_core, test_s21_memset);
  tcase_add_test(tc_core, test_s21_memset_char);
  tcase_add_test(tc_core, test_s21_memset_single_byte);
  tcase_add_test(tc_core, test_s21_memset_zero_length);
  tcase_add_test(tc_core, test_s21_memset_negative_val);
  /* test s21_strncat */
  tcase_add_test(tc_core, test_s21_strncat);
  tcase_add_test(tc_core, test_s21_strncat_partial);
  tcase_add_test(tc_core, test_s21_strncat_empty_src);
  tcase_add_test(tc_core, test_s21_strncat_empty_dest);
  tcase_add_test(tc_core, test_s21_strncat_zero_length);
  tcase_add_test(tc_core, test_s21_strncat_larger_length);
  /* test s21_strchr */
  tcase_add_test(tc_core, test_s21_strchr);
  tcase_add_test(tc_core, test_s21_strchr_middle);
  tcase_add_test(tc_core, test_s21_strchr_end);
  tcase_add_test(tc_core, test_s21_strchr_not_found);
  tcase_add_test(tc_core, test_s21_strchr_search_for_null);
  tcase_add_test(tc_core, test_s21_strchr_search_for_null_mid);
  tcase_add_test(tc_core, test_s21_strchr_empty);
  tcase_add_test(tc_core, test_s21_strchr_unsigned_chr);
  tcase_add_test(tc_core, test_s21_strchr_same_ptr);
  /* test s21_strncmp */
  tcase_add_test(tc_core, test_s21_strncmp);
  tcase_add_test(tc_core, test_s21_strncmp_smaller);
  tcase_add_test(tc_core, test_s21_strncmp_larger);
  tcase_add_test(tc_core, test_s21_strncmp_zero_length);
  tcase_add_test(tc_core, test_s21_strncmp_null_cmp_str1);
  tcase_add_test(tc_core, test_s21_strncmp_null_cmp_str2);
  tcase_add_test(tc_core, test_s21_strncmp_null_mid);
  tcase_add_test(tc_core, test_s21_strncmp_null_one_str);
  tcase_add_test(tc_core, test_s21_strncmp_partianl_eq);
  tcase_add_test(tc_core, test_s21_strncmp_same_ptr);
  /* test s21_strncpy */
  tcase_add_test(tc_core, test_s21_strncpy);
  tcase_add_test(tc_core, test_s21_strncpy_partial_cpy);
  tcase_add_test(tc_core, test_s21_strncpy_exact_len);
  tcase_add_test(tc_core, test_s21_strncpy_null_padding);
  tcase_add_test(tc_core, test_s21_strncpy_zero_length);
  tcase_add_test(tc_core, test_s21_strncpy_embedded_null);
  /* test s21_strcspn */
  tcase_add_test(tc_core, test_s21_strcspn);
  tcase_add_test(tc_core, test_s21_strcspn_start_match);
  tcase_add_test(tc_core, test_s21_strcspn_mid_match);
  tcase_add_test(tc_core, test_s21_strcspn_last_match);
  tcase_add_test(tc_core, test_s21_strcspn_multiple_match);
  tcase_add_test(tc_core, test_s21_strcspn_empty_str);
  tcase_add_test(tc_core, test_s21_strcspn_empty_reject);
  tcase_add_test(tc_core, test_s21_strcspn_empty_both);
  tcase_add_test(tc_core, test_s21_strcspn_all_match);
  tcase_add_test(tc_core, test_s21_strcspn_null_str);
  tcase_add_test(tc_core, test_s21_strcspn_null_reject);
  tcase_add_test(tc_core, test_s21_strcspn_ASCII);
  tcase_add_test(tc_core, test_s21_strcspn_same_str);
  /* test s21_strpbrk */
  tcase_add_test(tc_core, test_s21_strpbrk);
  tcase_add_test(tc_core, test_s21_strpbrk_mid_match);
  tcase_add_test(tc_core, test_s21_strpbrk_end_match);
  tcase_add_test(tc_core, test_s21_strpbrk_no_matches);
  tcase_add_test(tc_core, test_s21_strpbrk_multiple_matches);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_str);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_accept);
  tcase_add_test(tc_core, test_s21_strpbrk_empty_both);
  tcase_add_test(tc_core, test_s21_strpbrk_all_match);
  tcase_add_test(tc_core, test_s21_strpbrk_null_str);
  tcase_add_test(tc_core, test_s21_strpbrk_null_accept);
  /* test s21_strrchr */
  tcase_add_test(tc_core, test_s21_strrchr);
  tcase_add_test(tc_core, test_s21_strrchr_mid_match);
  tcase_add_test(tc_core, test_s21_strrchr_end_match);
  tcase_add_test(tc_core, test_s21_strrchr_multiple_match);
  tcase_add_test(tc_core, test_s21_strrchr_no_match);
  tcase_add_test(tc_core, test_s21_strrchr_null);
  tcase_add_test(tc_core, test_s21_strrchr_empty_str);
  tcase_add_test(tc_core, test_s21_strrchr_negative);
  tcase_add_test(tc_core, test_s21_strrchr_same_str);
  /* test s21_strstr */
  tcase_add_test(tc_core, test_s21_strstr_end_match);
  tcase_add_test(tc_core, test_s21_strstr_mid_match);
  tcase_add_test(tc_core, test_s21_strstr_start_match);
  tcase_add_test(tc_core, test_s21_strstr_no_match);
  tcase_add_test(tc_core, test_s21_strstr_multiple_matches);
  tcase_add_test(tc_core, test_s21_strstr_empty_needle);
  tcase_add_test(tc_core, test_s21_strstr_empty_haystack);
  tcase_add_test(tc_core, test_s21_strstr_empty_both);
  tcase_add_test(tc_core, test_s21_strstr_same_ptr);
  tcase_add_test(tc_core, test_s21_strstr_null_haystack);
  tcase_add_test(tc_core, test_s21_strstr_null_needle);
  tcase_add_test(tc_core, test_s21_strstr_ASCII);
  tcase_add_test(tc_core, test_s21_strstr_long_needle);
  /* test s21_strtok */
  tcase_add_test(tc_core, test_s21_strtok);
  tcase_add_test(tc_core, test_s21_strtok_multiple_delims);
  tcase_add_test(tc_core, test_s21_strtok_no_delim_in_str);
  tcase_add_test(tc_core, test_s21_strtok_no_delim);
  tcase_add_test(tc_core, test_s21_strtok_consecutive_delim);
  tcase_add_test(tc_core, test_s21_strtok_interleaved);
  tcase_add_test(tc_core, test_s21_strtok_empty_str);
  tcase_add_test(tc_core, test_s21_strtok_all_delims);
  tcase_add_test(tc_core, test_s21_strtok_delim_at_start);
  tcase_add_test(tc_core, test_s21_strtok_delim_at_end);
  tcase_add_test(tc_core, test_s21_strtok_multiple_consecutive_delim);

  suite_add_tcase(s, tc_core);

  return s;
}
