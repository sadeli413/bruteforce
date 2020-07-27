// gcc words.c -o words -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOTAL 94

int mod(double, double);
void printA(char* word, int size);

int main() {
	// base 94 counting where '!' is 0 and '~' is 93
	// init word as '!'
	int size = 1;
	char *word = (char*)malloc(size*sizeof(char));
	word[0] = '!' - 1;
	
	int count = 0;
	int all = 0;
	int place;
	double exp;
	
	while (1) {
		printf("%i\t%i\t", all, count);
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
		all++;
		printA(word, size);
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
	printf("\n");
}
