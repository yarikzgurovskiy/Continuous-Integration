#include <students.h>
#include <csv.h>
#include <students.h>
#include <check.h>

#include <stdio.h>
#include <stdlib.h>

START_TEST (CsvToList_CsvString_ListOfStudentsWithCorrectSize)
{
    char str[] = "  \
    Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
    Petro, Vovchenko, 24, 3.6\n\
    Stepan  , Glyna, 45,   3.7\n\
     Inna , Sgoludko, 21, 4.7\n\
       Katya, Sydorchuk , 23, 4.23";
    List * studs = CsvLoad_toList(str);
    int size = 6;
    ck_assert_int_eq(List_count(studs), size);
    
    freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
}
END_TEST

START_TEST (getList_CsvString_StudentsFromTeacherList)
{
    char str[] = "  \
    Vasyl  ,Petrus  ,34,2.645\n\
    Mykola,Oliynyk,23,2.4\n\
    Petro, Vovchenko, 24, 3.6\n\
    Stepan  , Glyna, 45,   3.7\n\
     Inna , Sgoludko, 21, 4.7\n\
       Katya, Sydorchuk , 23, 4.23";
    List * studs  = CsvLoad_toList(str);
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, "Matan");
    Teacher_attachStudents(pr, studs);
    List * studs2 = Teacher_getLowestScore(pr, 2);
    Student * st = List_get(studs2, 0);
    char buffer[100];
    Student_toString(st, buffer);
    ck_assert_str_eq("Mykola,Oliynyk,23,2.40", buffer);

    st = List_get(studs2, 1);
    Student_toString(st, buffer);
    ck_assert_str_eq("Vasyl,Petrus,34,2.64", buffer);
    
    freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
    freeAllStudents(studs2);
    List_freeAllNodes(studs2);
    List_free(&studs2);
    Teacher_free(&pr);
}
END_TEST
/*
START_TEST(newTeacher_fieldsForTeacher_freePtr)
{
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, "OOP");
    Teacher_free(&pr);
    ck_assert_ptr_null(pr);
} 
END_TEST

*/

Suite *test_suite() {
  Suite *s = suite_create("Student");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, CsvToList_CsvString_ListOfStudentsWithCorrectSize);
  tcase_add_test(tc_core, getList_CsvString_StudentsFromTeacherList);
  //tcase_add_test(tc_core, fieldsForTeacher_freePtr);
  
  
  suite_add_tcase(s, tc_core);

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

