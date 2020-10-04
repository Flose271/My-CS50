#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool validstring(string s);
int timesin(int item, string s);

int main(int argc, string arcv[])
{
    if (argc != 2)
    {
        printf("Only a single command line argument expected\n");
        return 1;
    }
    
    string key = arcv[1];
    
    if (strlen(arcv[1]) != 26)
    {
        printf("Key must be a string of length 26\n");
        return 1;
    }
    if (validstring(key) == false)
    {
        printf("All characters in key must be valid letters\n");
        return 1;
    }
    
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i = 0; i<26; i++)
    {
        if(timesin(alphabet[i],key) != 1)
        {
            printf("All letters must appear exactly once");
            return 1;
        }
    }
    
    string plaintext = get_string("plaintext: ");
    
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(plaintext); i++)
    {
        int plainchar = plaintext[i];
        int keyvalue = 0;
        if(isupper(plainchar) != 0)
        {
            keyvalue = plainchar - 65;
        }
        else
        {
            keyvalue = plainchar - 97;
        }
        
        int difference = toupper(key[keyvalue]) - toupper(plainchar);
        printf("%c", plainchar + difference);
        
    }
    printf("\n");

}

bool validstring(string s)
{
    for (int i = 0; i<26; i++)
    {
        if (!(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= 'a' && s[i] <= 'z'))
        {
            return false;
        }
    }
    return true;
}

int timesin(int item, string s)
{
    int count = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if(tolower(item) == s[i] || toupper(item) == s[i])
        {
            count += 1;
        }
    }
    return count;
}