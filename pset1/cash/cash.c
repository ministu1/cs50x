#include <cs50.h>
#include <stdio.h>

int get_change(int change);

int main(void)
{
    // prompt user for a positive integer
    int change;

    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    // get and print the result with given change
    int result = get_change(change);
    printf("%i\n", result);
}

// get minimum amount of coins needed with given change
int get_change(int change)
{
    int coins = 0;
    int quarters = 25;
    int dimes = 10;
    int nickels = 5;
    int pennies = 1;

    coins += change / quarters;
    change %= quarters;

    coins += change / dimes;
    change %= dimes;

    coins += change / nickels;
    change %= nickels;

    coins += change / pennies;

    return coins;
}
