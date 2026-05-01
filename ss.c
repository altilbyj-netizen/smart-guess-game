#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to save score
void saveScore(char name[], int score) {
    FILE *file = fopen("scores.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", name, score);
        fclose(file);
    }
}

// Function to show leaderboard
void showScores() {
    FILE *file = fopen("scores.txt", "r");
    char name[50];
    int score;

    printf("\n\033[1;34m=== Leaderboard ===\033[0m\n");

    if (file == NULL) {
        printf("No scores yet.\n");
        return;
    }

    while (fscanf(file, "%s %d", name, &score) != EOF) {
        printf("\033[1;33m%s\033[0m - \033[1;32m%d\033[0m\n", name, score);
    }

    fclose(file);
}

int main() {
    int level, max, number, guess;
    int attempts = 0;
    int score;
    char player[50];

    srand(time(0));

    // Welcome Screen
    printf("\033[1;36m============================\n");
    printf("   SMART GUESS GAME\n");
    printf("============================\033[0m\n");

    printf("\nEnter your name: ");
    scanf("%s", player);

    // Level selection
    printf("\nChoose Level:\n");
    printf("\033[1;32m1. Easy (1-50)\033[0m\n");
    printf("\033[1;33m2. Medium (1-100)\033[0m\n");
    printf("\033[1;31m3. Hard (1-500)\033[0m\n");
    printf("Choice: ");
    scanf("%d", &level);

    if (level == 1) max = 50;
    else if (level == 2) max = 100;
    else max = 500;

    number = rand() % max + 1;

    printf("\nGuess the number from 1 to %d:\n", max);

    while (1) {
        scanf("%d", &guess);
        attempts++;

        int diff = abs(number - guess);

        if (guess > number) {
            printf("\033[1;31mToo High! ⬇️\033[0m\n");
        } else if (guess < number) {
            printf("\033[1;31mToo Low! ⬆️\033[0m\n");
        } else {
            printf("\033[1;32m🎉 Correct! You Win!\033[0m\n");
            break;
        }

        // Smart hints
        if (diff <= 5) {
            printf("\033[1;35m🔥 Very Close!\033[0m\n");
        } else if (diff <= 15) {
            printf("\033[1;34m🙂 Close\033[0m\n");
        } else {
            printf("\033[1;36m❄️ Far\033[0m\n");
        }
    }

    // Score calculation
    score = 100 - (attempts * 10);
    if (score < 0) score = 0;

    printf("\nAttempts: %d\n", attempts);
    printf("\033[1;32mYour Score: %d\033[0m\n", score);

    saveScore(player, score);

    showScores();

    return 0;
}
