#include "recordOperations.h"
#include <stdlib.h>
#include <string.h>


void cleanup(Record *records, int size, FILE *srcFile)
{
    for (int i = 0; i < size; ++i)
    {
        free(records[i].name);
    }

    free(records);
    fclose(srcFile);
}

int findRecord(Record *records, int size, const char *name, const char *currency)
{
    for (int i = 0; i < size; ++i)
    {
        if (strcmp(records[i].name, name) == 0 && (strlen(currency) == 0 || strcmp(records[i].currency, currency) == 0))
        {
            return i;
        }
    }
    return -1;
}

void calculateCoins(int amount, const int *coins, int *coinCount)
{
    for (int i = 0; i < NUM_COINS; i++)
    {
        coinCount[i] = amount / coins[i];
        amount %= coins[i];
    }
}

void printChange(const char *name, int cents, const char *currency, const int *coinCount, const int *coins)
{
    if (cents > 0)
    {
        printf("\nCustomer:\n%s %d cents in %s\n", name, cents, currency);
        printf("Change:\n");
        for (int j = 0; j < NUM_COINS; ++j)
        {
            if (coinCount[j] > 0)
            {
                printf("%d coins: %d\n", coins[j], coinCount[j]);
            }
        }
    }
}
