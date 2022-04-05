#include <cs50.h>
#include <stdio.h>

int get_height();

int main(void)
{
    // Get a height
    int height = get_height(8);

    // print blocks
    for(int h=1; h<=height; h++)
    {
        for(int w=1; w<=height; w++)
        {
            if((height-h) < w)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// Get height (0 to 8)
int get_height(int max)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n > max || n < 1);
    return n;
}