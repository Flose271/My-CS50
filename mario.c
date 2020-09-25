#include <stdio.h>
#include <cs50.h>

void air(int n);

void blocks(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while(n<1);
    for (int i=0; i<n; i++)
    {
        //Number of 'air' before and after the blocks
        int air_value = n - i - 1;
        //Number of 'blocks' on each side
        int blocks_value = i + 1;
        
        //Prints the air before the blocks
        air(air_value);
        //Prints the blocks
        blocks(blocks_value);
        //Prints the gap between the blocks
        printf("  ");
        //Repeats for the other side
        blocks(blocks_value);
        air(air_value);
        //New line
        printf("\n");
    }
}

void air(int n)
{
    for (int i=0; i<n; i++)
    {
        printf(" ");
    }
}

void blocks(int n)
{
    for (int i=0; i<n; i++)
    {
        printf("#");
    }
}