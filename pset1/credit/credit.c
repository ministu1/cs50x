#include <cs50.h>
#include <stdio.h>

// Prototypes.
bool validate(long number);
string check_carrier(long number);

int main(void)
{
    long number;

    // Prompt user for a credit card number until a positive number is entered.
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    // Validate the number using Luhn's algorithm.
    // If the number is valid, check whether it belongs to a carrier
    // and print the result.
    string result;
    if (validate(number))
    {
        result = check_carrier(number);
    }
    else
    {
        result = "INVALID";
    }
    printf("%s\n", result);
}

// Function to validate the number using Luhn's algorithm.
bool validate(long number)
{
    int position = 0; // Helper to determine the digit's position.
    int checksum = 0; // Store the checksum.

    while (number > 0)
    {
        // If the digit is in an odd position starting from the back,
        // multiply by 2 and add the sum of the product's digits to the checksum.
        if (position % 2 == 1)
        {
            int digit = number % 10 * 2;
            // Adjust the digit to ensure a single digit.
            if (digit > 9)
            {
                digit -= 9;
            }
            checksum += digit;
        }
        // If the digit is in an even position, add it to the checksum.
        else
        {
            checksum += (number % 10);
        }
        position++;
        number /= 10;
    }
    // Return whether the checksum meets Luhn's requirement to be a multiple of 10.
    return checksum % 10 == 0;
}

// Function to check the carrier based on the starting number(s) and length.
string check_carrier(long number)
{

    // Reduce the number to its first two digits and determine its length.
    int number_length = 2; // Initialize length at 2 since the loop stops at the first two digits.
    do
    {
        number /= 10;
        number_length++;
    }
    while (number > 99);

    // Check whether the number fulfills any of the carriers' requirements
    // and return the result.
    if (number / 10 == 4 && (number_length == 13 || number_length == 16))
    {
        return "VISA";
    }
    else if ((number == 34 || number == 37) && number_length == 15)
    {
        return "AMEX";
    }
    else if ((number >= 51 && number <= 55) && number_length == 16)
    {
        return "MASTERCARD";
    }
    else
    {
        return "INVALID";
    }
}
