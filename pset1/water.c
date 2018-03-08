#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int minutes;
    int bottle;
    printf("Minutes: ");
    minutes = get_int();
    bottle = minutes * 12;
    printf("Bottles: %d\n", bottle);
}

