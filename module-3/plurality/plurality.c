#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct {
    string name;
    int votes;
} candidate;

candidate candidates[MAX];

int candidate_count;

bool vote(string name);
void print_winner(void);

int main(int argc, string argv[]) {
    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i = 0; i < voter_count; i++) {
        string name = get_string("Vote: ");
        if (!vote(name)) {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

bool vote(string name) {
    bool found = false;
    for(int i = 0; i < candidate_count; i++) {
        int compare = strcmp(candidates[i].name, name);

        if(compare == 0) {
            candidates[i].votes += 1;
            found = true;
            break;
        }
    }

    return found;
}

void print_winner(void) {
    int higher = 0;
    int higher_index = 0;
    for(int i = 0; i < candidate_count; i++) {
        if(candidates[i].votes > higher) {
            higher_index = i;
            higher = candidates[i].votes;
        }
    }

    for(int i = 0; i < candidate_count; i++) {
        if(candidates[i].votes == higher) {
            printf("%s\n", candidates[i].name);
        }
    }

}

