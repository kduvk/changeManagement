#include <stdio.h>
#include <stdlib.h>
#include "fileIO.h"
#include "recordIO.h"
#include "recordOperations.h"

int main()
{
    int lines = 0;

    FILE *srcFile;

    if (openFile(&srcFile, "coins.txt", &lines) == 0)
    {
        perror("Error opening the file");
        return -1;
    }

    Record *records = (Record *)malloc(lines * sizeof(Record));

    if (records == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        cleanup(records, lines, srcFile);
        return -1;
    }

    readRecords(srcFile, records, lines);

    for (int i = 0; i < lines; ++i)
    {
        int index = findRecord(records, i, records[i].name, records[i].currency);
        if (index != -1)
        {
            records[index].cents += records[i].cents;
            records[i].cents = 0;
        }
    }

    // Menu implementation
    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Enter name\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            handleEnterName(records, lines);
            break;

        case 2:
            writeDataAndExit(records, lines);
            break;
        }

    } while (choice != 2);

    cleanup(records, lines, srcFile);

    return 0;
}