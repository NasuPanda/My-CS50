#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    // FILE: C言語のデータ型、ファイルを指す
    // fopen: 第1引数にファイル名、第2引数にファイルを開くモードを渡す。
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        return 1;
    }

    char *name = get_string("name: ");
    char *number = get_string("number: ");

    fprintf(file, "%s,%s\n", name, number);

    fclose(file);
}