#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  char random_character;

  /* Generate random character from the ASCII table 
   * Range is max = 126 and min = 32 */
  random_character = rand() % (126 + 1 - 32) + 32;

  return random_character;

}

char *inputString()
{
  int i;
  char random_string[6]; memset(random_string, '\0', sizeof(random_string));

  /* Generate random string using the pool characters */
  char pool[] = "reset";

  for(i = 0; i < sizeof(random_string); i++)
  {
	  random_string[i] = pool[rand() % (sizeof(pool) - 1)];
  }

  random_string[sizeof(random_string) - 1] = '\0';

  return random_string;

}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
