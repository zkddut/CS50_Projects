#include <stdio.h>
#include <cs50.h>

int main()
{
    int height = 0;
    int tmp;
    int i,k,j;
    do {
      printf("Enter an height: ");
      height = get_int();
    } while ((height < 0) | (height > 23));

    for(i=1; i <= height; i++) {
      tmp = height - i;
      for(j=0; j < tmp; j++){
        printf(" ");
      }
      for(k=0; k < i; k++){
        printf("#");
      }
      printf("  ");
      for(k=0; k < i; k++){
        printf("#");
      }
      printf("\n");
    }
    return 0;
}