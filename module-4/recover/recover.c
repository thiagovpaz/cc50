#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    char filename[8];
    int counter = 0;
    FILE *img = NULL;

    while (fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(file);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 1;
            }

            fwrite(buffer, sizeof(BYTE), 512, img);
            counter++;
        }
        else if (counter > 0)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    fclose(file);
    if (img != NULL)
    {
        fclose(img);
    }

    return 0;
}

