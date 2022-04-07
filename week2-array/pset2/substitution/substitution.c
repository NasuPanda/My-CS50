#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Prototype
string validates_key();
string convert_cipher();

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // Displays correct usage
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    string key_validation = validates_key(key);

    if (strcmp(key_validation, "valid") != 0)
    {
        // if receives invalid key
        printf("%s\n", key_validation);
        return 1;
    }

    // Gets and converts text
    string text = get_string("plaintext:  ");
    text = convert_cipher(text, key);

    // Print out cipher text
    printf("ciphertext: %s\n", text);
    return 0;
}

// key validation (length, non-repeated, alphabetic)
string validates_key(string key)
{
    int n = strlen(key);

    // validates length
    if (n != 26)
    {
        return "Key must contain 26 characters.";
    }

    // validates not repeated, and alphabetic
    for (int i=0; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            return "Key must only contain alphabetic characters.";
        }
        else
        {
            for (int j = i + 1; j < n; j++)
            {
                if (key[i] == key[j])
                {
                    return "Key must not contain repeated characters.";
                }
            }
        }
    }
    return "valid";
}

// Convert plaintext to ciphertext
string convert_cipher(string text, string key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            // キー文字列から'a'を引くと、キーのインデックスを取得できる。
            text[i] = key[text[i] - 'a'];
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] = toupper(key[text[i] - 'A']);
        }
    }

    return text;
}