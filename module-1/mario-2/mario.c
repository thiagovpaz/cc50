#include <stdio.h>
#include <cs50.h>

int main(void) {
  int height;

  do {
    height = get_int("Height:");
  }
  while(height < 1 || height > 8);

  for (int i = 1; i <= height; i++) {
    for (int j = 1; j <= height; j++) {
      if (i > height - j) {
			  printf ("#");
			}
		  else {
			  printf (" ");
			}
    }
    printf ("  ");

    for (int j = 1; j <= i; j++) {
      printf ("#");
    }

    printf ("\n");
  }
}
