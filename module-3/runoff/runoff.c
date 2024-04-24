#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct {
  string name;
  int votes;
  bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

bool vote(int voter, int rank, string name);

void tabulate(void);

bool print_winner(void);

int find_min(void);

bool is_tie(int min);

void eliminate(int min);

int main(int argc, string argv[]) {
  if (argc < 2) {
    printf("Usage: runoff [candidate ...]\n");
    return 1;
  }

  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES) {
    printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }

  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
    candidates[i].eliminated = false;
  }

  voter_count = get_int("Number of voters: ");
  if (voter_count > MAX_VOTERS) {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }

  for (int i = 0; i < voter_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      string name = get_string("Rank %i: ", j + 1);

      if (!vote(i, j, name)) {
        printf("Invalid vote.\n");
        return 4;
      }
    }

    printf("\n");
  }

  while (true) {
    tabulate();

    if (print_winner()) {
      break;
    }

    int min = find_min();
    bool tie = is_tie(min);

    if (tie) {
      for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated) {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }

    eliminate(min);

    for (int i = 0; i < candidate_count; i++) {
      candidates[i].votes = 0;
    }
  }
    return 0;
}

bool vote(int voter, int rank, string name) {
  for(int i = 0; i < candidate_count; i++) {
    int compare = strcmp(candidates[i].name, name);
    if(compare == 0) {
      preferences[voter][rank] = i;
      printf("%d\n", i);
      return true;
    }
  }
  return false;
}

void tabulate(void) {
  for(int i = 0; i < voter_count; i++ ) {
    int top_1 = preferences[i][0];
    if (!candidates[top_1].eliminated) {
      candidates[top_1].votes++;
    } else {
      for(int j = 1; j < candidate_count; j++) {
        top_1 = preferences[i][j];
        if(!candidates[top_1].eliminated) {
          candidates[top_1].votes++;
          break;
        }
      }
    }
  }
}

bool print_winner(void) {
  int win = voter_count / 2;

  for(int i = 0; i < candidate_count; i++ ) {
    if(candidates[i].votes > win) {
      printf("%s\n", candidates[i].name);
      return true;
    }
  }
  return false;
}

int find_min(void) {
  int min = voter_count;
  for(int i = 0; i < candidate_count; i++ ) {
    if(!candidates[i].eliminated && candidates[i].votes < min) {
      min = candidates[i].votes;
    }
  }
  return min;
}

bool is_tie(int min) {
  int max_votes = 0;
  int min_votes = 0;
  for (int i = 0; i < candidate_count; i++) {
    if (!candidates[i].eliminated) {
      max_votes = candidates[i].votes > max_votes ? candidates[i].votes : max_votes;
    }
    if(!candidates[i].eliminated && candidates[i].votes == min) {
      min_votes++;
    }
  }
  return max_votes == min && min_votes >   1;
}

void eliminate(int min) {
  for(int i = 0; i < candidate_count; i++ ) {
    if(candidates[i].votes == min) {
      candidates[i].eliminated = true;
    }
  }
}
