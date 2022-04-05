#include <cs50.h>
#include <stdio.h>

// Prototype
void meow(void);

int main(void)
{
    int i = get_positive_int();
    meow(3);
}

// Say meow
void meow(int n)
{
    for(i = 0; i < n; i++){
    printf("meow\n");
    }
}

int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Positive Integer");
    }
    while (n < 1);
    return n;
}