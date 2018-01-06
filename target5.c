#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(char *arg)
{
  char buf[T5BUFFER];
  snprintf(buf, sizeof buf, arg);
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      fprintf(stderr, "target4: argc != 2\n");
      exit(EXIT_FAILURE);
    }
  foo(argv[1]);

  return 0;
}
