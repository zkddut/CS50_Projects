#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check for 2 arguments only
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // once I check for correct argv put key into an int k
    int k = atoi(argv[1]);

    // check if the integer is non-negative
    if (k < 0)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    else
    {
        // prompt user for a code to encrypt
        printf("plaintext:  \n");
        string code = get_string();

        printf("ciphertext:  \n");
        for (int i = 0, n = strlen(code); i < n; i++)
        {
          //check if the letter is uppercase or lowercase then convert
          if islower(code[i])
            printf("%c", (((code[i] + k) - 97) % 26) + 97);
          else if isupper(code[i])
            printf("%c", (((code[i] + k) - 65) % 26) + 65);
          //if neither then just print whatever it is
          else
            printf("%c", code[i]);
          }
          printf("\n");
          return 0;
    }
}

