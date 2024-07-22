#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Prototypes.
int analyze_text(string text);
void print_result(int index);

int main(void)
{
    // Prompt user for a text and call functions
    // to calculate and print the result.
    string text = get_string("Text: ");
    int index = analyze_text(text);
    print_result(index);
}

// Function to determine the Coleman-Liau index the input text.
int analyze_text(string text)
{
    float letters = 0, words = 0, sentences = 0;
    int i = 0;
    int length = strlen(text);

    // Loop over the text to determine how many letters, words and sentences
    // it consists out of.
    while (i < length)
    {
        if (isalpha(text[i]))
            letters++;
        if (text[i] == ' ')
            words++;
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            sentences++;
        i++;
    }

    // Include the last word of the text.
    words++;

    // Account for user input of singular words and missing punctuation at the end of the text.
    if (isalpha(text[length - 1]) || (text[length - 1] == '"' && isalpha(text[length - 2])))
        sentences++;

    // Using the the Coleman-Liau index to determine the grade level of the text
    // where L is the average number of letters per 100 words in the text,
    // and S is the average number of sentences per 100 words in the text.
    float L = 100 * (letters / words);
    float S = 100 * (sentences / words);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

// Print the result.
void print_result(int index)
{
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
}
