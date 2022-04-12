#include <stdio.h>
#include <stdlib.h>

// typedef で データ構造を定義
typedef struct node
{
    int number;
    // structキーワードで定義した[node]を参照するs
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL;

    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    // 一時的な変数nに値を割り当て
    n->number = 1;
    n->next = NULL;
    // 変数listをn(作成したnode)にする
    list = n;

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;

    // for : 変数初期化、条件、変数更新の順であれば何でもOK
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i", tmp->number);
    }

    // メモリの解放
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}
