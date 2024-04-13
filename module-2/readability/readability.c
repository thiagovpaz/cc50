#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <cs50.h>

int main(void) {
    string text = get_string("Text: ");

    int l = 0, s = 0, w = 1, i = 0;
    int len = strlen(text);

    for(i = 0; i < len; i++ ) {
      if(text[i] == '!' || text[i] == '?' || text[i] == '.') {
        s++;
      }

      if(text[i] == ' ') {
        w++;
      }

      if(isalpha(text[i])) {
        l++;
      }
    }

    float L = (float) l / w * 100;
    float S = (float) s / w * 100;

    int indice =  round(0.0588 * L - 0.296 * S - 15.8);

    if (indice < 1) {
      printf("Before Grade 1\n");
    } else if (indice >= 1 && indice <= 15) {
      printf("Grade %i\n", indice);
    } else {
      printf("Grade 16+\n");
    }
}
