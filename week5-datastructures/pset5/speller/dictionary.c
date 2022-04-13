// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Number of words
unsigned int word_count;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
// 辞書にある単語に対してのみtrueを返す。(fooがあってもfoo'sにはtrueを返さない)
bool check(const char *word)
{
    int hash_value = hash(word);

    node *dict = table[hash_value];

    while (dict != NULL)
    {
        if (strcasecmp(word, dict->word) == 0)
        {
            return true;
        }
        dict = dict->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // aとの相対位置
    int hash = tolower(word[0] - 'a');
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // tempporal memory allocation
    char word[LENGTH + 1];

    // Until EOF (End Of File)
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        // Assign word to node->word
        strcpy(n->word, word);
        // Get hash value
        int hash_value = hash(word);

        // Assign n->next to latest value
        n->next = table[hash_value];
        if (hash_value < 0)
        {
            printf("minus value: %s", word);
        }
        // Updata latest value
        table[hash_value] = n;

        word_count++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];

        while (n != NULL)
        {
            // Prevent memory leak
            node *next = n->next;

            free(n);

            n = next;
        }

        if (i == N - 1 && n == NULL)
        {
            return true;
        }
    }
    return false;
}
