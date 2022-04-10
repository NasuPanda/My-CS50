#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("%i, %i", x, y);
    swap(&x, &y);
    printf("\n after swap \n");
    printf("%i, %i", x, y);
}

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}