#include "recordIO.h"
#include "recordOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readRecords(FILE *srcFile, Record *records, int lines)
{
    for (int i = 0; i < lines; ++i)
    {
        records[i].name = (char *)malloc(256 * sizeof(char));

        
        if (fscanf(srcFile, "%s %d cents in %3s", records[i].name, &records[i].cents, records[i].currency) != 3)
        {
            fprintf(stderr, "Error reading entry %d from the file\n", i + 1);
            
        }

        
        if (records[i].cents >= 95)
        {
            fprintf(stderr, "Warning: Amount exceeds 95 cents for individual %s in entry %d\n", records[i].name, i + 1);
            exit(EXIT_FAILURE);
        }
    }
}

void writeDataAndExit(Record *records, int lines)
{
    const int US_COINS[] = {50, 25, 10, 1};
    const int AU_COINS[] = {50, 20, 10, 5};
    const int EURO_COINS[] = {20, 10, 5, 1};
    FILE *changeFile = fopen("change.csv", "w");
    if (changeFile == NULL)
    {
        perror("Error opening change.csv");
        cleanup(records, lines, NULL);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; ++i)
    {
        if (records[i].cents > 0)
        {
            const int *currentCoins;

            if (strcmp(records[i].currency, "US$") == 0)
            {
                currentCoins = US_COINS;
            }
            else if (strcmp(records[i].currency, "AU$") == 0)
            {
                currentCoins = AU_COINS;
            }
            else
            {
                currentCoins = EURO_COINS;
            }

            calculateCoins(records[i].cents, currentCoins, records[i].coinCount);

            fprintf(changeFile, "%s, the change for %d cents in %s is %d,%d,%d,%d\n",
                    records[i].name, records[i].cents, records[i].currency,
                    records[i].coinCount[0], records[i].coinCount[1], records[i].coinCount[2], records[i].coinCount[3]);
        }
    }

    fclose(changeFile);
    cleanup(records, lines, NULL);
    exit(EXIT_SUCCESS);
}

void handleEnterName(Record *records, int lines)
{
    const int US_COINS[] = {50, 25, 10, 1};
    const int AU_COINS[] = {50, 20, 10, 5};
    const int EURO_COINS[] = {20, 10, 5, 1};
    char enteredName[256];
    printf("Enter name: ");
    scanf("%s", enteredName);

    int found = 0;
    for (int i = 0; i < lines; ++i)
    {
        if (strcmp(records[i].name, enteredName) == 0)
        {
            const int *currentCoins;

            if (strcmp(records[i].currency, "US$") == 0)
            {
                currentCoins = US_COINS;
            }
            else if (strcmp(records[i].currency, "AU$") == 0)
            {
                currentCoins = AU_COINS;
            }
            else
            {
                currentCoins = EURO_COINS;
            }

            calculateCoins(records[i].cents, currentCoins, records[i].coinCount);
            printChange(records[i].name, records[i].cents, records[i].currency, records[i].coinCount, currentCoins);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Name: %s\nNot found\n", enteredName);
    }
}