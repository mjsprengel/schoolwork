#include<stdio.h>
#include <cs50.h>
#include <math.h>

// This will take a long long as input, and run the credit card checksum to determine whethor or not the card is valid
// GetLongLong() is an input sanitization function for getting long longs in the cs50 library. 

int main(void)
{
    int digits;
    printf("Enter credit card number: ");
    long long number = GetLongLong();
    digits = floor(log10(number)) + 1; // this is a clever way to get number of digits in an input
    if((digits != 13) && (digits != 15) && (digits != 16))
    { // if the input isn't either 13, 15, or 16 digits, the card is invalid
        printf("INVALID\n");
        exit(0);
    }
    
    int cardArray[digits];
    long long divisor = pow(10, digits-1);
// converts credit card number to an array of digits with some number theory 
    for(int i = 0; i<digits; i++)
    {
        cardArray[i] = (number - number%divisor)/divisor;
        number = number%divisor;
        divisor /= 10;
    }
// need 2 arrays to do checksum algorithm, this is the first array
    int arr1[digits/2];

// initializing array based on whether even or odd number of digits
    int arrsize;
    if(digits % 2 == 0)
    {
        arrsize = digits/2;
    } else{
        arrsize = (digits/2) + 1;
    }
// second array initialized, accounting for even or odd numbered credit card
    int arr2[arrsize];

// loads every other digit of the card number into arr2, starting from the last index
    int j = arrsize-1;
    for(int i = digits-1; i>=0; i = i - 2)
        if(i>=0)
        {
            arr2[j] = cardArray[i];
            j -= 1;
        } else{
            break;
        }
    
// loads every other digit of the card number into arr1, starting from second to last index    
    j = (digits/2)-1;
    for(int i = digits-2; i>=0; i = i - 2)
        if(i>=0)
        {
            arr1[j] = cardArray[i];
            j -= 1;
        } else{
            break;
        }
    
    int sum = 0;
    for(int i = 0; i<digits/2; i++)
        if(arr1[i]*2 >= 10)
        { // here we need to add the DIGITS after multiplication by 2
            sum += (1 + (arr1[i]*2)%10);
        } else{
            sum += arr1[i]*2;  
        }
    
    for(int i = 0; i<arrsize; i++)
        sum += arr2[i];
        
// final check for card types   
    if(sum%10 != 0)
    {
        printf("INVALID\n");
        exit(0);
    }
    if(cardArray[0] == 5)
        if(cardArray[1] >=1 && cardArray[1]<=5)
        {
            printf("MASTERCARD\n");
            exit(0);
        }
    
    if((cardArray[0] == 3)&&(cardArray[1] == 4 || cardArray[1] == 7))
    {
        printf("AMEX\n");
        exit(0);
    } 
    if(cardArray[0] == 4)
    {
        printf("VISA\n");
        exit(0);
    }
    printf("INVALID\n");
    return 0; 
}
