#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int hasDuplicates(const char *str) {
    int charSet[26] = {0};

    for (int i = 0; i < strlen(str); i++) {
      char currentChar = tolower(str[i]);

      if (isalpha(currentChar)) {
        if (charSet[currentChar - 'a'] == 1) {
          return 1;
        }
        charSet[currentChar - 'a'] = 1;
      }
    }

    return 0;
}

int isAlphaNumeric(const char *str) {
  while (*str) {
    if (!isalpha(*str)) {
      return 0;
    }
    str++;
  }
  return 1;
}

int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Uso: ./substitution substitution key\n");
    return 1;
  }

  if(strlen(argv[1]) != 26) {
    printf("A chave deve conter 26 caracteres.\n");
    return 1;
  }

  if(!isAlphaNumeric(argv[1])) {
    printf("Error.\n");
    return 1;
  }

  if (hasDuplicates(argv[1])) {
    printf("Keyword must contain only unique characters.\n");
    return 1;
  }

  char *key = argv[1];

  string plaintext = get_string("plaintext: ");
  char ciphertext[100] = "";

   for (int i = 0; i < strlen(plaintext); i++) {
     if(isalpha(plaintext[i]) && isupper(plaintext[i])) {
      int index = plaintext[i] - 'A';

      char str[2];
      sprintf(str, "%c", toupper(key[index]));

      strncat(ciphertext, str, 1);
      continue;
    }

    if(isalpha(plaintext[i]) && islower(plaintext[i])) {
      int index = plaintext[i] - 'a';

      char str[2];
      sprintf(str, "%c", tolower(key[index]));

      strncat(ciphertext, str, 1);
      continue;
    }

     strncat(ciphertext, &plaintext[i], 1);
   }

   printf("ciphertext: %s\n", ciphertext);


  return 0;
}
