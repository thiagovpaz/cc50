#include <stdio.h>
#include <cs50.h>

int
main (void) {

  int years = 0;

  int start_population;
  do {
      start_population = get_int("Start size: ");
  } while(start_population < 9);

  int end_population;
  do {
      end_population = get_int("End size: ");
  } while(end_population < start_population);

  int current_population = start_population;

  while(current_population < end_population) {
    current_population = current_population + (current_population / 3) - (current_population / 4);
    years++;
  }
  printf("Years: %i\n", years);
}
