#include <stdio.h>
#include <cs50.h>

int get_positive_int();

int main(void)
{
    int w = get_positive_int("width");
    int h = get_positive_int("height");

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
         printf("#");
        }
    printf("\n");
    }
}

// Get positive number from user
int get_positive_int(string description)
{
    int n;
    do
    {
        n = get_int("%s: ", description);
    }
    while (n < 1);
    return n;
}