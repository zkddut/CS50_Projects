#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float changes = 0;
    int int_changes = 0;
    int coins = 0;

    printf("O hai! ");
    do {
      printf("How much change is owed?\n");
      changes = get_float();
    } while (changes < 0);

    int_changes = (int) round(changes*100);

    //printf("changes 0 %d, coin: %d\n",int_changes, coins);

    coins += (int_changes / 25);
    int_changes %= 25;

    //printf("changes 1 %d, coin: %d\n",int_changes, coins);

    coins += (int_changes / 10);
    int_changes %= 10;

    //printf("changes 2 %d, coin: %d\n",int_changes, coins);

    coins += (int_changes / 5);
    int_changes %= 5;

    //printf("changes 3 %d, coin: %d\n",int_changes, coins);

    coins += (int_changes / 1);
    int_changes %= 1;

    //printf("changes 4 %d, coin: %d\n",int_changes, coins);

    printf("%d\n",coins);
    return 0;
}

