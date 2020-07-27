// gcc encrypt.c -o encrypt -lcrypt

#define _XOPEN_SOURCE

#include <stdio.h>
#include <string.h>
#include <crypt.h>

void warning();

int main(int argc, char *argv[]) {
  if (argc < 3) {
    warning();
    return 1;
  }
    
  // hash argv[2] with salt argv[1]
  printf("%s\n", crypt(argv[2], argv[1]));
}

void warning() {
  printf("usage:\n\t./brute [salt] [password]\n");
}
