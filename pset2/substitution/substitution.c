#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool validstring(string s);
int timesin(int item, string s);

int main(int argc, string arcv[])
{
    //Tests if only one word (the key) was given
    if (argc != 2)
    {
        printf("Only a single command line argument expected\n");
        return 1;
    }
    
    //Sets the key to the argment given
    string key = arcv[1];
    
    //Tests if the key is 26 letters long
    if (strlen(arcv[1]) != 26)
    {
        printf("Key must be a string of length 26\n");
        return 1;
    }
    //Tests if the key only contains valid characters
    if (validstring(key) == false)
    {
        printf("All characters in key must be valid letters\n");
        return 1;
    }
    
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    //Tests if all the letters in the alphabet appear in the key exactly once
    for (int i = 0; i < 26; i++)
    {
        if (timesin(alphabet[i], key) != 1)
        {
            printf("All letters must appear exactly once");
            return 1;
        }
    }
    
    string plaintext = get_string("plaintext: ");
    
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(plaintext); i++)
    {
        //If the character in plaintext is a valid letter
        if (('A' <= plaintext[i] && plaintext[i] <= 'Z') || ('a' <= plaintext[i] && plaintext[i] <= 'z'))
        {
            //Converts the value in the key to its numerical value in the alphabet
            int plainchar = plaintext[i];
            int keyvalue = 0;
            if (isupper(plainchar) != 0)
            {
                keyvalue = plainchar - 65;
            }
            else
            {
                keyvalue = plainchar - 97;
            }
            
            //Finds the difference between the current position of the key and where it should be
            int difference = toupper(key[keyvalue]) - toupper(plainchar);
            //Prints the new character taking that difference into account
            printf("%c", plainchar + difference);
        }
        //If not a valid letter of the alphabet then print it as normal
        else
        {
            printf("%c", plaintext[i]);
        }
        
        
    }
    printf("\n");

}

//Checks whether all characters in a string are valid
bool validstring(string s)
{
    for (int i = 0; i < 26; i++)
    {
        if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z'))
        {
            return false;
        }
    }
    return true;
}

//Finds the number of times a letter appears in a string
int timesin(int item, string s)
{
    int count = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (tolower(item) == s[i] || toupper(item) == s[i])
        {
            count += 1;
        }
    }
    return count;
}