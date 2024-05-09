#include "fileIO.h"

int openFile(FILE **srcFile, const char *filename, int *lines)
{
    *srcFile = fopen(filename, "r");
    if (*srcFile == NULL)
    {
        perror("File opening failed\n");
        return 0;
    }

    if (fscanf(*srcFile, "%d", lines) != 1)
    {
        fprintf(stderr, "Error reading the number of entries from the file\n");
        fclose(*srcFile);
        return 0;
    }

    return 1;
}
