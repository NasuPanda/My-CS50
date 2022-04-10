#include <stdio.h>

int main(void)
{
    int n = 50;
    // *によりポインタの宣言
    // &によりアドレスを取得
    int *p = &n;

    // Cの言語仕様にstring型は存在しないが、
    // charのポインタとして変数を宣言することで文字列として扱える。
    char *s = "HI!";

    printf("%i \n", *p);
    printf("%p \n", &s[0]);
    printf("%p \n", &s[1]);
}