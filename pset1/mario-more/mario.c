#include <cs50.h>
#include <stdio.h>

void build_pyramid(int height);

int main(void)
{
    // prompt user for integer between 1 and 8 inclusive to determine the height
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // print the pyramid with set height
    build_pyramid(height);
}

void build_pyramid(int height)
{
    for (int i = 1; i <= height; i++)
    {
        // print left gap
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // print left blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // print middle gap
        printf("  ");

        // print right blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // move to next line of blocks
        printf("\n");
    }
}
