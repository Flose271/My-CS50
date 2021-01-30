#include <cs50.h>
#include <stdio.h>

void swap(int a, int b);

int main(void)
{
    int a = 1;
    int b = 2;
    printf("%i", a);
    printf("%i", b);
    
    //swap(a,b);
    
    int temp = a;
    a = b;
    b = temp;
    
    printf("%i", a);
    printf("%i", b);
}

void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}