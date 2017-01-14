// This is a simple demonstration of a dictionary attack on linux's DES encryption. It is assumed that the encrypted passwords
// have been compromised, and we can see the ciphertext. 

// This program takes every word in the english language, and runs it through linux crypt(), then compares to the visible,
// compromised ciphertexts

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>

string crypt();
int tolower(int c);

int main(int argc, char* argv[])
{   
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    char* dictArr[99171];

    int i = 0;
    int j;
    fp = fopen("american-english", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if(strlen(line) <= 9){
            dictArr[i] = strdup(line);
            dictArr[i][0] = tolower(dictArr[i][0]);
            i++;
        }
    }

    fclose(fp);
    if (line)
        free(line);

    printf("%i words less than or equal to 8 characters\n", i);
    
    string psswd;
    string salt = "50";
    if(argc == 2) 
        psswd = argv[1];
    else 
    {
        printf("ERROR: Please input only one command line argument\n");
        return 1;
    }
    
    for(int j = 0; j<i-1; j++)
    {
        if (!(strcmp(crypt(dictArr[j],salt), psswd)))
            printf("DECRYPTED PASSWORD FOUND AT LINE %i: %s", j, dictArr[j]);
    }
    
}
