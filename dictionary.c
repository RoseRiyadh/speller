// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int wCounter = 0;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    unsigned int index;

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        index = hash(word);
        node *newNode = malloc(sizeof(node));
        strcpy(newNode->word, word);
        newNode->next = NULL;
        newNode->next = hashtable[index];
        hashtable[index] = newNode;
        wCounter++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wCounter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *head = hashtable[hash(word)];

    while (head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        else
        {
            head = head->next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            cursor = next;
        }
    }

    return true;
}
