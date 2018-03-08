/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include "dict.c"

Dict d;
int word_count;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    char tmp [47] ;
    strncpy(tmp, word, 47);
    for(int i = 0; tmp[i]; i++){
        tmp[i] = tolower(tmp[i]);
    }
    if (DictSearch(d, tmp) != NULL) {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open input file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 0;
    }
    d = DictCreate();
    char line [47] ;
    while (fgets(line, sizeof(line), inptr) != NULL)
    {
        line[strcspn(line, "\n")] = 0;
        DictInsert(d, line, line);
        word_count++;
        //printf("dictionary word:%s\n", line);
    }
    fclose(inptr);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    DictDestroy(d);
    return true;
}
