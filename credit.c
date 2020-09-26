#include <stdio.h>
#include <cs50.h>
//Imported this so I could use 'pow'.
#include <math.h>

//A function that finds the length of a number
int length(long n);
//A function that finds a certain digit of a number
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
            //If 2*digit is under 10, we can just add it to the sum.
            if(2*digit<10)
            {
                sum += 2*digit;
            }
            //If it's over 10, we need to add the digits individually as so.
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

    //Prints the sum, for debugging.
    //printf("%i",sum);
    
    //If the sum doesn't end in a zero then it is invalid
    if(sum%10 != 0)
    {
        printf("INVALID\n");
    }
    //If the number is 15 digits long, first digit 3 and second digit 4 or 7
    else if(length(n) == 15 && digitof(n,15) == 3 && (digitof(n,14) == 4 || digitof(n,14) == 7))
    {
        printf("AMEX\n");
    }
    //If the number is 16 digits long, first digit 5 and second digit between 1 and 5
    else if(length(n) == 16 && digitof(n,16) == 5 && 0<digitof(n,15) && digitof(n,15)<6)
    {
        printf("MASTERCARD\n");
    }
    //If the number is 13 digits or 16 digits long and starts with a 4
    else if((length(n) == 13 && digitof(n,13) == 4) || (length(n) == 16 && digitof(n,16) == 4))
    {
        printf("VISA\n");
    }
    //If none of these are satisfied, it must be invalid.
    else
    {
        printf("INVALID\n");
    }

}

int length(long n)
{
    int i = 0;
    //sp10 and bp10 are small power 10, big power 10
    long sp10;
    long bp10;
    do
    {
        sp10 = pow(10,i);
        i++;
        bp10 = pow(10,i);
    }
    //This repeats until both n/sp10 != 0 and n/bp10 == 0, which then we know it is of length i.
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