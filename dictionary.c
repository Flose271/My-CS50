// Implements a dictionary's functionality

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int total = 0;
    for (int i = 0; i < 3; i++)
    {
        char letter = *(word + (2 - i));
        letter = toupper(letter);
        letter += -65;
        total += letter * pow(26,i);
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
        }
        else
        {
            new_node->next = table[hash_value];
            table[hash_value] = new_node;
        }
        
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
