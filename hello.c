#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //The user is asked for their name
    string name = get_string("What is your name?\n");
    //Their name is added to 'hello' and displayed using printf
    printf("hello, %s\n", name);
}