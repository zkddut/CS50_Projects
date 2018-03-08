#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check for 2 arguments only
    if (argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    // once I check for correct argv put key into an int k
    string k = argv[1];

    // check if the integer is non-negative
    for(int i = 0, n = strlen(k); i < n; i++) {
      if (!(isalpha(k[i]))) {
        printf("Usage: ./vigenere k\n");
        return 1;
      }
    }
        // prompt user for a code to encrypt
        printf("plaintext:  \n");
        string code = get_string();

        printf("ciphertext:  \n");
        int j = 0;
        for (int i = 0, n = strlen(code); i < n; i++)
        {
          //check if the letter is uppercase or lowercase then convert
          if islower(code[i])
            printf("%c", (((code[i] + (islower(k[j]) ? (k[j] - 97) : (k[j] -65))) - 97) % 26) + 97);
          else if isupper(code[i])
            printf("%c", (((code[i] + (islower(k[j]) ? (k[j] - 97) : (k[j] -65))) - 65) % 26) + 65);
          //if neither then just print whatever it is
          else
            printf("%c", code[i]);
          j++;
          j %= strlen(k);
        }
        printf("\n");
        return 0;
}

