## `sort_pairs`

下のようにすると、各勝敗ペアの「勝利の強度」を見ることが出来る。
コレを利用してソートする。

```c
void sort_pairs(void)
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i回目", i+1);
        printf("\n");
        winner = pairs[i].winner;
        loser = pairs[i].loser;
        printf("winner %i, loser %i", winner, loser);
        printf("\n");
        printf("strength: %i", preferences[winner][loser]);
        printf("\n");
    }
}

// 1回目
// winner 0, loser 1
// strength: 2
// 2回目
// winner 0, loser 2
// strength: 3
// 3回目
// winner 1, loser 2
// strength: 2
```