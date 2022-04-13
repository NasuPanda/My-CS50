// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

// bool型を使用するためにinclude
#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
// 他ファイルで使用可能な定数
#define LENGTH 45

// Prototypes
// constで渡された引数は関数内で変更できない
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

#endif // DICTIONARY_H
