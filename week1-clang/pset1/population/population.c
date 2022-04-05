#include <cs50.h>
#include <stdio.h>

int get_start_size();
int get_end_size();
int calculate_years();

int main(void)
{
    // Get start and end sizes
    int start_size = get_start_size();
    int end_size = get_end_size(start_size);

    // Get and print number of years
    int years = calculate_years(start_size, end_size);
    printf("Years: %i\n", years);
}

// Get start size (9 or more)
int get_start_size()
{
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);
    return n;
}

// Get end size (startsize or more)
int get_end_size(int start_size)
{
    int n;
    do
    {
        n = get_int("End size: ");
    }
    while (n < start_size);
    return n;
}

// Calculate number of years until we reach threshold
int calculate_years(int start_size, int end_size)
{
    int years = 0;
    do
    {
        int births = start_size / 3;
        int deaths = start_size / 4;
        start_size = start_size + births - deaths;
        years++;
    }
    while (start_size < end_size);
    return years;
}