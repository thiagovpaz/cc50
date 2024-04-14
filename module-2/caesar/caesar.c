#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int isNumeric(const char *str) {
  while (*str) {
    if (!isdigit(*str)) {
      return 0;
    }
    str++;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Error\n");
    return 1;
  }

  if(!isNumeric(argv[1])) {
    printf("Usage: ./caesar key\n");
    return 1;
  }

  int key = atoi(argv[1]);

  string plaintext = get_string("plaintext: ");
  char ciphertext[100] = "";

  char upper_letters[26];
  for (int i = 0; i < 26; ++i) {
    upper_letters[i] = 'A' + i;
  }

  char lower_letters[26];
  for (int i = 0; i < 26; ++i) {
    lower_letters[i] = 'a' + i;
  }

  for (int i = 0; i < strlen(plaintext); i++) {
    if(isalpha(plaintext[i]) && isupper(plaintext[i])) {
      int index = plaintext[i] - 'A';
      index = (index + key) % 26;

      strncat(ciphertext, &upper_letters[index], 1);
      continue;
    }

    if(isalpha(plaintext[i]) && islower(plaintext[i])) {
      int index = plaintext[i] - 'a';
      index = (index + key) % 26;

      strncat(ciphertext, &lower_letters[index], 1);
      continue;
    }

    strncat(ciphertext, &plaintext[i], 1);

  }

  printf("ciphertext: %s\n", ciphertext);

  return 0;
}
