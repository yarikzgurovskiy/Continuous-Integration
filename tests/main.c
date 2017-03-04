#include "ci.h"
#include <check.h>

#include <stdio.h>
#include <stdlib.h>

//gcc main.c ./src/*.c -I./include -lcheck
START_TEST (CsvToList_string_free)
{
    char str[] = "  Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
    Petro, Vovchenko, 24, 3.6\n\
    Stepan  , Glyna, 45,   3.7";
    List * studs = CsvToList(str);
    int size = 4;
    ck_assert_int_eq(List_count(studs), size);
    
    Student_freeAll(studs);
    List_clean(studs);
    List_free(&studs);
}
END_TEST

/*START_TEST(getList_str_StudentFromList)
{
    char str[] = "  Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
      Petro, skjflskdf, 24, 3.6\n\
      lskdjfl  , lxjjl, 45,   3.7";
    List * studs  = CsvToList(str);
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, NULL);
    Teacher_attachStudents(pr, studs);
    List * studs2 = Teacher_getLowestScore(pr, 2);
    Student * st = List_get(studs2, 0);
    char buffer[100];
    Student_toString(st, buffer);
    ck_assert_str_eq("Mykola,Oliynyk,23,2.4", buffer);
    
    Student_freeAll(studs);
    List_clean(studs);
    List_free(&studs);
    Student_freeAll(studs2);
    List_clean(studs2);
    List_free(&studs2);
    Teacher_free(&pr);
}
END_TEST*/

/*START_TEST(newTeacher_void_free)
{
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, NULL);
    Teacher_free(&pr);
    ck_assert_ptr_eq(pr, NULL);
} 
END_TEST*/



Suite *test_suite() {
  Suite *s = suite_create("Module");
  TCase *new_free = tcase_create("TestCase");

  tcase_add_test(new_free, CsvToList_string_free);
  //tcase_add_test(new_free, newTeacher_void_free);
  //tcase_add_test(new_free, getList_str_StudentFromList);
  
  
  
  
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

