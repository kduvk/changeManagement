#ifndef RECORDOPERATIONS_H
#define RECORDOPERATIONS_H

#include "record.h"

int findRecord(Record *records, int size, const char *name, const char *currency);

void calculateCoins(int amount, const int *coins, int *coinCount);

void printChange(const char *name, int cents, const char *currency, const int *coinCount, const int *coins);

#endif