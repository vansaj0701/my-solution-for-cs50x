#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    FILE *fWrite = NULL;

    if (file == NULL)
    {
        printf("Couldn't read file\n");
        return 1;
    }

    uint8_t buffer[SIZE];
    char fname[10];
    int fcount = 0;

    while (fread(buffer, 1, SIZE, file) == SIZE)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
            (buffer[3] == 0xE0 || buffer[3] == 0xE1))
        {
            if (fWrite != NULL)
            {
                fclose(fWrite);
            }

            sprintf(fname, "%03d.jpg", fcount);
            fWrite = fopen(fname, "w");

            if (fWrite == NULL)
            {
                fclose(file);
                printf("Couldn't create file\n");
                return 1;
            }
            fcount++;
        }
        if (fWrite != NULL)
        {
            fwrite(buffer, SIZE, 1, fWrite);
        }
    }
    if (fWrite != NULL)
    {
        fclose(fWrite);
    }
    fclose(file);
    return 0;
}
