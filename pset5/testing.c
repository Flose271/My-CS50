#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

unsigned int hash(const char *word);

int main(void)
{
    char *myword = malloc(4*sizeof(char));
    myword[0] = 'T';
    myword[1] = 'H';
    myword[2] = '\0';
    printf("%i", hash(myword));
}

unsigned int hash(const char *word)
{
    int total = 0;
    for (int i = 0; i < 3; i++)
    {
        char letter = *(word + i);
        if (letter == '\0')
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