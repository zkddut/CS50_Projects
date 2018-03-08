/* strtok example */
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int main ()
{
  string str = get_string();
  char * pch;
  //printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%c",toupper(pch[0]));
    pch = strtok (NULL, " ,.-");
  }
  printf ("\n");
  return 0;
}