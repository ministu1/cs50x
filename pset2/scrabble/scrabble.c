#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototype
int get_score(string word);
int get_winner(int scores[]);

// Array with letter values for Scrabble in the alphabet's order.
const int VALUES[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Set the amount of players.
// Hard coded to '2' so check50 doesn't throw errors.
const int PLAYERS = 2;

int main(void)
{

    int player[PLAYERS];
    string words[PLAYERS];
    int scores[PLAYERS];

    // Store the players number.
    // Prompt user(s) for input of their words and store them.
    // Get the score for each of the entered words.
    for (int i = 0; i < PLAYERS; i++)
    {
        player[i] = i + 1;
        words[i] = get_string("Player %i: ", i + 1);
        scores[i] = get_score(words[i]);
    }

    // Get the winner.
    int winner = get_winner(scores);

    // Print the result.
    if (winner == 99)
        printf("Tie!\n");
    else
        printf("Player %i wins!\n", winner + 1);
}

// Function to determine the scores.
int get_score(string word)
{
    int score = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // Convert each lowercase letter to uppercase.
        char letter = toupper(word[i]);
        // Exclude everything but uppercase letters and get the score for each letter.
        if (isupper(letter))
            score += VALUES[letter - 'A'];
    }
    return score;
}

// Function to determine the highest score.
int get_winner(int scores[])
{
    int max = scores[0];
    int winner = 0;
    int winner_index = 0;

    // In the array of scores find the index with the highest score.
    // If the highest score exists at least twice, return 99 (Tie).
    for (int i = 1; i < PLAYERS; i++)
    {

        if (scores[i] == scores[winner_index])
            winner = 99;
        else if (scores[i] > scores[winner_index])
        {
            max = scores[i];
            winner = i;
            winner_index = i;
        }
    }
    return winner;
}
