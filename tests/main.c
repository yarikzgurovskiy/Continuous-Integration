#include "ci.h"
#include <check.h>

#include <stdio.h>
#include <stdlib.h>

START_TEST (CsvToList_string_free)
{
    char str[] = "  \
    Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
    Petro, Vovchenko, 24, 3.6\n\
    Stepan  , Glyna, 45,   3.7\n\
     Inna , Sgoludko, 21, 4.7\n\
       Katya, Sydorchuk , 23, 4.23";
    List * studs = CsvToList(str);
    int size = 6;
    ck_assert_int_eq(List_count(studs), size);
    
    List_freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
}
END_TEST

START_TEST(getList_str_StudentFromList)
{
    char str[] = "  \
    Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
    Petro, Vovchenko, 24, 3.6\n\
    Stepan  , Glyna, 45,   3.7\n\
     Inna , Sgoludko, 21, 4.7\n\
       Katya, Sydorchuk , 23, 4.23";
    List * studs  = CsvToList(str);
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, NULL);
    Teacher_attachStudents(pr, studs);
    List * studs2 = Teacher_getLowestScore(pr, 2);
    Student * st = List_get(studs2, 0);
    char buffer[100];
    Student_toString(st, buffer);
    ck_assert_str_eq("Mykola,Oliynyk,23,2.4", buffer);
    
    List_freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
    List_freeAllStudents(studs2);
    List_freeAllNodes(studs2);
    List_free(&studs2);
    Teacher_free(&pr);
}
END_TEST

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

