#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Note
// アルファベット判定(lettersのカウント)
// https://manual.cs50.io/3/isalpha
// スペース判定(wordsのカウント)
// https://manual.cs50.io/3/isspace

// Prototype
int count_letters();
int get_coleman_liau_index();

int main(void)
{
    // Get text
    string text = get_string("Text: ");

    // Get letters count
    int letters = count_letters(text);

    // Initialize counts(word starts at 1)
    int words = 1;
    int sentences = 0;

    // Count number of words and sentences
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Calculate Coleman-Liau index
    int index = get_coleman_liau_index(letters, words, sentences);

    // Output results
    if (index >= 16)
    {
        printf("Grade 16+");
    }
    else if (index <= 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", index);
    }
}

// Count number of letters
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}


// Calculate readabillity index based of Coleman-Liau
int get_coleman_liau_index(letters, words, sentences)
{
    // 100語当たりの平均字数
    float l = letters / (float)words * 100;
    // 100語当たりの平均文数
    float s = sentences / (float)words * 100;

    float index = 0.0588 * l - 0.296 * s - 15.8;
    return round(index);
}