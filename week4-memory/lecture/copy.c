#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("s: ");

    char *t = malloc(strlen(s) + 1);

    // メモリエラー(メモリ不足等)が発生するとmallocはNULLを返す
    if (t == NULL)
    {
        return 1;
    }

    strcpy(t, s);

    if (strlen(s) > 0)
    {
        s[0] = toupper(s[0]);
    }

    printf("%s\n", t);
    printf("%s\n", s);

    // ポインタを引数に取り、メモリを開放する。
    free(t);
}