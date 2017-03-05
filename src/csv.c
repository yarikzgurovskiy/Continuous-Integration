#include "list.h"
#include "students.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>


List * CsvLoad_toList(char * str){
    List * newList = List_new();
    char buffer[4][20];
    int word = 0;;
    int wordIndex = 0;
    int i = 0;;
    for(i = 0; i <= strlen(str); i++){
        char ch = str[i];
        if(isspace(ch) && ch != '\n'){
            continue;
        }else if(ch == ','){
            buffer[word][wordIndex] = '\0';
            word++;
            wordIndex = 0; 
        } else if((ch == '\n' || ch == '\0') && i != 0){
            buffer[word][wordIndex] = '\0';
            word = 0;
            wordIndex = 0;
            Student * stud = Student_newFromStringArray(buffer);
            List_addLast(newList, stud);
        } else {
            buffer[word][wordIndex] = ch;
            wordIndex++;
        }
    }
    return newList;
}

char * CsvLoad_fromList(char * str, List * self){
    sprintf(str, "%c", '\0');
    char sign[2];
    sprintf(sign, "%c", '\n');
    int len = List_count(self);
    int i = 0;;
    for(i = 0; i < len; i++){
        char buf[50];
        Student_toString(List_get(self, i), buf);
        strcat(str, buf);
        if(i == len - 1) {
            sprintf(sign, "%c" ,'\0');
            break;
        }
        strcat(str, sign);
    }
    return str;
}
