// gcc brute.c -o brute -lcrypt -lm
#define _XOPEN_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>

#define TOTAL 94

int mod(double, double);
void printA(char* word, int size);
void warning();

int main(int argc, char *argv[]) {
  // check input
  if (argc != 3) {
    warning();
    return 1;
  }

	// base 94 counting where '!' is 0 and '~' is 93
	// init word as '!'
	int size = 1;
	char *word = (char*)malloc(size*sizeof(char));
	word[0] = '!' - 1;
	
	int count = 0;
	int place;
	double exp;
	
	while (1) {
		for(int i = 0; i < size; i++) {
			// ones place, tens place, hundreds place, etc
			place = size - i - 1;
			// base 94 counting: every 94^place count, then increment
			exp = pow(TOTAL, place);
			if (mod(count, exp) == 0) {
				word[i]++;
				// loop back to 0:'!' when getting to 93:'~'
				if (word[i] > '~') {
					word[i] = '!';
				}
			}
		}
		count++;
    
		printA(word, size); // print the word
		printf("\t%s", crypt(word, argv[1])); // print the encrypted word with salt argv[1]
    printf("\n");
    
    // check for success, with the hash argv[2]
    if(strcmp(crypt(word, argv[1]), argv[2]) == 0) {
      return 0;
    }

		// every 94^size time, gain a new digit
		if (mod(count, pow(TOTAL, size)) == 0) {
			size++;
			word = realloc(word, size*sizeof(char));
			word[size - 1] = '!' - 1; // set to -1 because it all increments when looping back to top
			count = 0; // reset count because !!!!! is also 0
		}
	}
}

// modulus: big % small. int doesn't hold big enough number
int mod(double big, double small) {
	while (big >= small) {
		big -= small;
	}
	return big;
}

// print an array
void printA(char* word, int size) {
	for (int i = 0; i < size; i++) {
		printf("%c", word[i]);
	}
}

void warning() {
  printf("usage:\n\t./brute [salt] [hash]\n");
}
