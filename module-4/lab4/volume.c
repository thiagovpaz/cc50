#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t *hder = malloc(sizeof(uint8_t) * HEADER_SIZE);
    fread(hder, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(hder, sizeof(uint8_t), HEADER_SIZE, output);
    free(hder);

    int16_t samp;
    while (fread(&samp, sizeof(int16_t), 1, input)) {
        samp *= factor;
        fwrite(&samp, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
}
