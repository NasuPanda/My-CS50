#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string user_name = get_string("What's your name?: ");
    printf("hello, %s", user_name);
}