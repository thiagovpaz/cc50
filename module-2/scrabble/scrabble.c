#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

char letters[26];

int findIndex(char *array, int size, int target);

int compute_score(string word);

int main(void) {
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    for (int i = 0; i < 26; ++i) {
        letters[i] = 'a' + i;
    }

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if(score1 > score2) {
        printf("Player 1 wins!\n");
    } else if(score1 < score2) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }

}

int findIndex(char *array, int size, int target) {
    int i = 0;
    while((i<size) && (array[i] != target)) i++;
    return (i<size) ? (i) : (-1);
}

int compute_score(string word) {
    int points = 0;

    for(int i = 0; i < strlen(word); i++) {
        char target = word[i];

        if(isupper(target)) {
            target = target + 32;
        }

        int index = findIndex(letters, 26, target);

        if(index != -1) {
            points += POINTS[index];
        }
    }
    return points;
}
