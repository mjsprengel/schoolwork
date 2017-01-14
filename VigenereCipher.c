// This one takes command line arguments in the form of text which you want to encrypt, as well as an encryption key
// The form of encryption here is the vigenere cipher https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher

#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main(int argc, char* argv[])
{
    string key;
// checking to see if input has any non alpha characters, using ASCII reference  
    for(int i = 0; i<strlen(argv[1]); i++)
        if (!(argv[1][i]>=97 && argv[1][i]<=122) || ((argv[1][i]>=65 && argv[1][i]<=90)))
        {
            printf("ERROR: argument must not have non-alphabetical characters\n");
            return 1;
        }
    printf("%s\n",argv[1]);       
// making sure there's only 1 command line argument
    if(argc == 2) 
        key = argv[1];
    else 
    {
        printf("ERROR: Please input only one command line argument\n");
        return 1;
    }
    
    int shift;
    int j = 0;
    string sentence = GetString();
    
// perform caesar cipher, using the current index value of the input key as a shift value

    for(int i = 0, n = strlen(sentence); i<n; i++)
    {
        //obtaining shift value based on where we are in the index of the key. Start at key[0].
        if(key[j]>=97 && key[j]<=122)
            shift = key[j]-97;
        else if((key[j]>=65 && key[j]<=90))
            shift = key[j]-65;
            
        // caesar cipher based on ASCII integer values
        if(sentence[i]>=97 && sentence[i]<=122)
        {
            if((sentence[i]-96 + shift) <= 26)
            {
                sentence[i] = ((sentence[i]-96) + shift) + 96;
                printf("%c", sentence[i]);
            }   
            else
            {
                sentence[i] = (((sentence[i]-96) + shift) % 26 ) + 96;
                printf("%c", sentence[i]);
            }
        }
        else if(sentence[i]>=65 && sentence[i]<=90)
        {
            if((sentence[i]-64 + shift) <= 26)
            {
                sentence[i] = ((sentence[i]-64) + shift) + 64;
                printf("%c", sentence[i]);
            }   
            else
            {
                sentence[i] = (((sentence[i]-64) + shift) % 26 ) + 64;
                printf("%c", sentence[i]);
            }
        }
        // decrement if it's a space or a non alphabetical character, aka wait to shift key index 
        else 
        {
            printf("%c", sentence[i]);
            j--;
        }
        // incrementing the index of the key to get new shift value
        j++;
        if(j>=strlen(argv[1]))
            j = 0;
    }
    printf("\n");
}
