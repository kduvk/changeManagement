#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>

#define NUM_COINS 4

typedef struct
{
    char *name;
    int cents;
    char currency[3];
    int coinCount[NUM_COINS];
} Record;

void cleanup(Record *records, int size, FILE *srcFile);

#endif