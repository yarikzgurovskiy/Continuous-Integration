#include <students.h>
#include <csv.h>
#include <students.h>
#include <check.h>

#include <stdio.h>
#include <stdlib.h>

START_TEST(freeTeacher_fieldsForTeacher_freePtr)
{
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, "OOP");
    Teacher_free(&pr);
    ck_assert_ptr_null(pr);
} 
END_TEST

START_TEST(freeStudent_fieldsForStudent_freePtr)
{
    Student * st = Student_new("Petro", "Pasko", 23, 3.5);
    Student_free(&st);
    ck_assert_ptr_null(st);
} 
END_TEST

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

START_TEST (CsvToList_EmptyString_EmptyListOfStudents)
{
  char str[] = "";
  List * studs = CsvLoad_toList(str);
  int size = 0;
  ck_assert_int_eq(size, List_count(studs));

  freeAllStudents(studs);
  List_freeAllNodes(studs);
  List_free(&studs);
}
END_TEST

START_TEST(ListToCsv_ListOfStudents_CsvString)
{
    List * studs = List_new();
    Student * s1 = Student_new("Pavlo", "Laychuk", 22, 4.3);
    Student * s2 = Student_new("Anna", "Manko", 20, 3.5);
    Student * s3 = Student_new("Maryna", "Panchuk", 18, 4.24);
    List_addLast(studs, s1);
    List_addLast(studs, s2);
    List_addLast(studs, s3);
    char str[200];
    str[0] = '\0';

    CsvLoad_fromList(str, studs);
    ck_assert_str_eq(str, "Pavlo,Laychuk,22,4.30\nAnna,Manko,20,3.50\nMaryna,Panchuk,18,4.24");

    //free memory
    freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
    ck_assert_ptr_null(studs);
}
END_TEST

START_TEST(ListToCsv_EmptyListOfStudents_EmptyString)
{
  List * studs = List_new();
  char str[200];
  str[0] = '\0';

  CsvLoad_fromList(str, studs);
  ck_assert_str_eq("", str);

  List_free(&studs);
}
END_TEST

START_TEST(AttachStudents_TeacherAndStudents_TeacherWithAttachedList)
{
  Teacher * pr = Teacher_new("Oleksiy", "Petrenko", 32, "ASD");
  List * studs = List_new();
  Student * s1 = Student_new("Pavlo", "Laychuk", 22, 4.3);
  Student * s2 = Student_new("Anna", "Manko", 20, 3.5);
  Student * s3 = Student_new("Maryna", "Panchuk", 18, 4.24);
  Student * s4 = Student_new("Vitaliy", "Troyickyi", 19, 3.1);
  List_addLast(studs, s1);
  List_addLast(studs, s2);
  List_addLast(studs, s3);
  List_addLast(studs, s4);
  Teacher_attachStudents(pr, studs);

  List * studs2 = Teacher_getLowestScore(pr, 2);

  ck_assert_ptr_eq(studs, Teacher_getStudents(pr));
  ck_assert_int_eq(2, List_count(studs2));
  freeAllStudents(studs);
  List_freeAllNodes(studs);
  List_free(&studs);
  Teacher_free(&pr);
}
END_TEST


START_TEST (getList_CsvString_StudentsFromTeacherList)
{
    char str[] = "  \
    Vasyl  ,Petrus  ,34,4.645\n\
    Mykola,Oliynyk,23,2.6\n\
    Petro, Vovchenko, 24, 3.6\n\
    Stepan  , Glyna, 45,   3.7\n\
     Inna , Sgoludko, 21, 4.7\n\
       Katya, Sydorchuk , 23, 4.23";
    List * studs  = CsvLoad_toList(str);
    Teacher * pr = Teacher_new("Petro", "Pasko", 23, "Matan");
    Teacher_attachStudents(pr, studs);
    ck_assert_int_eq(List_count(studs), 6);
    List * studs2 = Teacher_getLowestScore(pr, 3);
    
    Student * st = List_get(studs2, 0);
    ck_assert_str_eq(Student_getName(st), "Mykola");
    ck_assert_str_eq(Student_getSurname(st), "Oliynyk");
    ck_assert_int_eq(Student_getAge(st), 23);
    ck_assert_int_eq(Student_getMark(st), 2.60);

    st = List_get(studs2, 1);
    
    ck_assert_str_eq(Student_getName(st), "Petro");
    ck_assert_str_eq(Student_getSurname(st), "Vovchenko");
    ck_assert_int_eq(Student_getAge(st), 24);
    ck_assert_int_eq(Student_getMark(st), 3.60);
    
    freeAllStudents(studs);
    List_freeAllNodes(studs);
    List_free(&studs);
    freeAllStudents(studs2);
    List_freeAllNodes(studs2);
    List_free(&studs2);
    Teacher_free(&pr);
}
END_TEST

START_TEST(getList_ListOfStudentsLessThanNumber_getEmptyList)
{
  Teacher * pr = Teacher_new("Oleksiy", "Petrenko", 32, "ASD");
  List * studs = List_new();
  Student * s1 = Student_new("Pavlo", "Laychuk", 22, 4.3);
  Student * s2 = Student_new("Anna", "Manko", 20, 3.5);
  Student * s3 = Student_new("Maryna", "Panchuk", 18, 4.24);
  List_addLast(studs, s1);
  List_addLast(studs, s2);
  List_addLast(studs, s3);
  Teacher_attachStudents(pr, studs);

  List * stud2 = Teacher_getLowestScore(pr, List_count(Teacher_getStudents(pr)) + 1);

  ck_assert_ptr_null(stud2);
  //free memory
  freeAllStudents(studs);
  List_freeAllNodes(studs);
  List_free(&studs);
  Teacher_free(&pr);
}
END_TEST



Suite *test_suite() {
  Suite *s = suite_create("Students");
  TCase *tc_case = tcase_create("Case");
  
  tcase_add_test(tc_case, freeTeacher_fieldsForTeacher_freePtr);
  tcase_add_test(tc_case, freeStudent_fieldsForStudent_freePtr);

  tcase_add_test(tc_case, CsvToList_CsvString_ListOfStudentsWithCorrectSize);
  tcase_add_test(tc_case, CsvToList_EmptyString_EmptyListOfStudents);

  tcase_add_test(tc_case, ListToCsv_ListOfStudents_CsvString);
  tcase_add_test(tc_case, ListToCsv_EmptyListOfStudents_EmptyString);

  tcase_add_test(tc_case, AttachStudents_TeacherAndStudents_TeacherWithAttachedList);

  tcase_add_test(tc_case, getList_CsvString_StudentsFromTeacherList);
  tcase_add_test(tc_case, getList_ListOfStudentsLessThanNumber_getEmptyList);
  
  suite_add_tcase(s, tc_case);

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

