#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int sentences = 0;
    int letters = 0;
    int words = 0;

    string text = get_string("Text: ");

    for (int i = 0; i < strlen(text) + 1; i++)
    {
        //If the character is a letter, increase the letter count by one.
        if (('A' <= text[i] && text[i] <= 'Z') ^ ('a' <= text[i] && text[i] <= 'z'))
        {
            letters += 1;
        }
        //If there is a space or the text is over, increase the word count by one.
        else if ((text[i] == ' ') ^ (text[i] == '\0'))
        {
            words += 1;
        }
        //If there is an exclamation or punctuation mark, or a full stop, increase sentence count by one.
        else if ((text[i] == '!') ^ (text[i] == '.') ^ (text[i] == '?'))
        {
            sentences += 1;
        }
        //If the character is a comma or hypen or other character, it doesn't change any count.
    
    }
    
    //For testing letter and word count.
    //printf("%i\n", letters);
    //printf("%i\n", words);

    //Calculation of the index.
    float hundredwords = (float) words / 100;
    float S = (float) sentences / hundredwords;
    float L = (float) letters / hundredwords;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    //If the index is over 16 or under 1, those exceptions are dealt with.
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }

}