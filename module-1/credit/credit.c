#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>

int main(void) {
  bool isValid = false;

  do {
      long cardNumber = get_long("Number: ");
      char cardText[20];

      sprintf(cardText, "%ld", cardNumber);

      int length = strlen(cardText);

      int sum = 0;
      bool inverse = false;

      for (int i = length - 1; i >= 0; i--) {
          int digit = cardText[i] - '0';

          if (inverse) {
              digit *= 2;
              if (digit > 9) {
                  digit -= 9;
              }
          }

          sum += digit;

          inverse = !inverse;
      }

      isValid = sum % 10 == 0;

      if (isValid && length == 15 && cardText[0] == '3' && (cardText[1] == '4' || cardText[1] == '7')) {
        printf("AMEX\n");
      }
      else if (isValid && length >= 13 && cardText[0] == '4') {
        printf("VISA\n");
      }
      else if (isValid &&  length == 16 && cardText[0] == '5' && (cardText[1] == '1' || cardText[1] == '2'|| cardText[1] == '3'|| cardText[1] == '4'|| cardText[1] == '5')) {
        printf("MASTERCARD\n");
      }
      else {
        printf("INVALID\n");
        break;
      }
  }
  while(isValid == false);
}
