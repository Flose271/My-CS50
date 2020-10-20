// Implements a dictionary's functionality

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_value = hash(word);
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int total = 0;
    for (int i = 0; i < 3; i++)
    {
        char letter = *(word + i);
        if(letter == '\0')
        {
            break;
        }
        letter = toupper(letter);
        letter += -65;
        total += letter * pow(26, 2 - i);
    }
    return total;
    //return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            free(new_node);
            return false;
        }

        strcpy(new_node->word, word);

        int hash_value = hash(new_node->word);

        node *firstnode = table[hash_value];

        if(firstnode == NULL)
        {
            table[hash_value] = new_node;
            word_count += 1;
        }
        else
        {
            new_node->next = table[hash_value];
            table[hash_value] = new_node;
            word_count += 1;
        }

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int bucket = 0; bucket < N; bucket++)
    {
        node *firstnode = table[bucket];
        
        if(firstnode != NULL)
        {
            node *cursor = firstnode;
            node *tmp = NULL;
            while(cursor != NULL)
            {
                tmp = cursor;
                free(cursor);
                cursor = tmp->next;
            }
        }
        
        free(firstnode);
    }
    return true;
}
