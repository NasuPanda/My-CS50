#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] はiよりjを好む投票の数
int preferences[MAX][MAX];

// locked[i][j] : i > j でロックされている
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// strength of victory
typedef struct
{
    int pair;
    int strength;
}
victory_strength;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
victory_strength victory_strengths[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void create_strengths(void);
void sort_victory_desc(void);
void sort_pairs_based_on_victory(void);
bool is_cycle(int, int);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks配列の初期化
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int candidate_index = 0; candidate_index < candidate_count; candidate_index++)
    {
        if (strcmp(candidates[candidate_index], name) == 0)
        {
            // ここでインデックスを使う
            ranks[rank] = candidate_index;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // 「i」よりも順位が下(=インデックスの値が大きい)の「j」をpreferencesに記録する
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    create_strengths();
    sort_victory_desc();
    sort_pairs_based_on_victory();
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }
    return;
}

// cycleが形成されないことをチェックする。circle_startは固定, loserが変化。
bool is_cycle(int cycle_start, int loser)
{
    // ベースケース : cycleが形成された時(cycle_startとloserが一致)
    if (loser == cycle_start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i]) // loserにロックされている「i」が存在すれば
        {
                if (is_cycle(cycle_start, i)) // circle_startはそのまま、次のloserに「i」を渡す
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_loser = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_loser = true;
                break;
            }
        }

        if (is_loser)
        {
            continue;
        }
        printf("%s\n", candidates[i]);
    }
}

// - - - - - - - - - -
// ソート用
// - - - - - - - - - -
// pair と strength of victory を紐付ける
void create_strengths(void)
{
    int winner;
    int loser;
    for (int i = 0; i < pair_count; i++)
    {
        winner = pairs[i].winner;
        loser = pairs[i].loser;

        victory_strengths[i].pair = i;
        victory_strengths[i].strength = preferences[winner][loser];
    }
}

// victory_strengthsを降順にソートする(選択ソート)
void sort_victory_desc(void)
{
    // 要素の入れ替え用
    victory_strength temp_strengths[2];
    int max_pair_index;

    for (int i = 0; i < pair_count; i++)
    {
        // 比較用
        int max_strength = victory_strengths[i].strength;
        // 値の入れ替え用
        int max_index = i;

        for (int j = i+1; j < pair_count; j++)
        {
            if (victory_strengths[j].strength > max_strength)
            {
                max_strength = victory_strengths[j].strength;
                max_index = j;
            }
        }

        // 最大値=現在の値 でなければ入れ替え
        if (!(max_index == i))
        {
            temp_strengths[0] = victory_strengths[max_index];
            temp_strengths[1] = victory_strengths[i];

            victory_strengths[i] = temp_strengths[0];
            victory_strengths[max_index] = temp_strengths[1];
        }
    }
}

// strength of victory を使ってpairsをソートする
void sort_pairs_based_on_victory(void)
{
    // pairsのコピー
    pair temp_pairs[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        temp_pairs[i].winner = pairs[i].winner;
        temp_pairs[i].loser = pairs[i].loser;
    }

    // pairsのソート
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = temp_pairs[victory_strengths[i].pair];
    }
}

