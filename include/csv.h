#ifndef CSV_H
#define CSV_H
#include "list.h"

List * CsvLoad_toList(char * str);
char * CsvLoad_fromList(char * str, List * self);

#endif //CSV_H