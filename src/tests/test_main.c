#include <check.h>

#include "test_suites.h"

int main() {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(string_suite());
  srunner_add_suite(sr, string_suite_add());
  srunner_add_suite(sr, strerror_suite());
  srunner_add_suite(sr, sprintf_suite());

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
