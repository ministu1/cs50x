#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Prototypes.
int check_key(string key);
void cipher(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check that exactly 1 extra argument is provided. Otherwise exit.
    if (argc == 2)
    {
        // Exit the function if the key is invalid.
        if (check_key(argv[1]))
        {
            return 1;
        }

        // Prompt the user for the plaintext they wish to cipher.
        string plaintext = get_string("plaintext: ");

        // Cipher the text and print it.
        cipher(plaintext, argv[1]);

        return 0;
    }
    else
    {
        printf("-- usage: ./substitution key\n");
        return 1;
    }
}

// Function to check whether the provided key is valid.
int check_key(string key)
{
    int length = strlen(key);

    // Print instructions if "help" is passed as argument.
    if (strcmp(key, "help") == 0)
    {
        printf("-- usage: ./substitution key\n");
        printf("-- your key needs to contain all 26 alphabetic characters\n");
        printf("-- your key can't contain any duplicates\n");
        return 1;
    }

    // Check the length of the key.
    if (length != 26)
    {
        printf("-- KEY INVALID: your key needs to contain all 26 alphabetic "
               "characters\n");
        return 1;
    }

    // Check for non-alphabetic characters.
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("-- KEY INVALID: Your key can only contain alphabetic characters\n");
            return 1;
        }

        // Check for duplicates.
        for (int j = i + 1; j < length; j++)
        {

            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("-- KEY INVALID: Your key can't contain any duplicates\n");
                return 1;
            }
        }
    }
    return 0;
}

// Function to cipher the text with provided key and print it.
void cipher(string plaintext, string key)
{
    int key_length = strlen(key);
    int text_length = strlen(plaintext);
    char cipher[26];

    // Populate the array used to cipher the text.
    for (int i = 0; i < key_length; i++)
    {
        cipher[i] = key[i];
    }

    printf("ciphertext: ");

    // Cipher and print.
    for (int i = 0; i < text_length; i++)
    {
        char old = plaintext[i];
        char new_char;

        if (isalpha(old)) // Cipher the character if it is alphabetic.
        {
            int index = toupper(old) - 'A'; // Find the index of the character in the cipher array.

            // Cipher the character while preserving the case.
            if (islower(old))
            {
                new_char = tolower(cipher[index]);
            }
            else
            {
                new_char = toupper(cipher[index]);
            }
        }
        else
        {
            new_char = old; // Pass non-alphabetic characters as is.
        }

        printf("%c", new_char); // Print the result.
    }
    printf("\n");
}
