#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void) {
  float value;
    do {
      value = get_float("Exchange due: ");
    }
    while (value <= 0);

    int formatted = round(value * 100);
    int coins[] = { 25, 10, 5, 1 };
    int qtd = 0;

    int i = 0;
    while(i < 4) {
      if( (formatted - coins[i]) >= 0 ) {
        formatted = formatted - coins[i];
        qtd++;
        i--;
      }
      i++;
    }
    printf("%d\n", qtd);
}
