#ifndef RECORDIO_H
#define RECORDIO_H

#include "record.h"

void readRecords(FILE *srcFile, Record *records, int lines);
void writeDataAndExit(Record *records, int lines);
void handleEnterName(Record *records, int lines);

#endif 
