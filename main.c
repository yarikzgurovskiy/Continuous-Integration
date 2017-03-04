#include "ci.h"
#include <check.h>

#include <stdio.h>
#include <stdlib.h>

//gcc main.c ./src/*.c -I./include -lcheck
START_TEST (CsvToList_string_free)
{
    char str[] = "  Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
      Petro, skjflskdf, 24, 3.6\n\
      lskdjfl  , lxjjl, 45,   3.7";
    List * studs = CsvToList(str);
    int size = 4;
    ck_assert_int_eq(List_count(studs), size);
    
    Student_freeAll(studs);
    List_clean(studs);
    List_free(&studs);
}
END_TEST



Suite *test_suite() {
  Suite *s = suite_create("Module");
  TCase *new_free = tcase_create("TestCase");

  tcase_add_test(new_free, CsvToList_string_free);
  
  
  suite_add_tcase(s, new_free);

  return s;
}

int main(void) {
  Suite *s = test_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);  // important for debugging!

  srunner_run_all(sr, CK_VERBOSE);

  int num_tests_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return num_tests_failed;
}

