#include <stdio.h>
#include <cs50.h>
#include <math.h>

int length(long n);
int digitof(long n, int d);

int main(void)
{
    long n;
    do
    {
        n = get_long("Credit Card Number: ");
    }
    while (n < 1);

    //The length of the credit card number is assigned to len.
    int len = length(n);
    //This will keep track of the sum of credit card numbers.
    int sum = 0;

    for(int i = 1; i<len+1; i++)
    {
        //Get the ith digit from the back 
        int digit = digitof(n, i);
        //If i is even, we double the digit and add it to the sum.
        if(i%2 == 0)
        {
            if(2*digit<10)
            {
                sum += 2*digit;
            }
            else
            {
                sum += 1;
                sum += (2*digit)%10;
            }
            
        }
        //If i is an odd, we add the digit to the sum
        else
        {
            sum += digit;
        }
    }

    //printf("%i",sum);
    
    if(sum%10 != 0)
    {
        printf("INVALID\n");
    }
    else if(length(n) == 15 && digitof(n,15) == 3 && (digitof(n,14) == 4 || digitof(n,14) == 7))
    {
        printf("AMEX\n");
    }
    else if(length(n) == 16 && digitof(n,16) == 5 && 0<digitof(n,15) && digitof(n,15)<6)
    {
        printf("MASTERCARD\n");
    }
    else if((length(n) == 13 && digitof(n,13) == 4) || (length(n) == 16 && digitof(n,16) == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

int length(long n)
{
    int i = 0;
    long sp10;
    long bp10;
    do
    {
        sp10 = pow(10,i);
        i++;
        bp10 = pow(10,i);
    }
    while(n/sp10 == 0 || n/bp10 != 0);
    return i;
}

int digitof(long n, int d)
{
    //Let cutnumber be the last d digits of n.
    long power = pow(10,d);
    long cutnumber = n%power;
    //Then the first digit of cutnumber is found.
    //This gives us our 'dth' digit.
    int digit = cutnumber/pow(10,d-1);
    return digit;
}