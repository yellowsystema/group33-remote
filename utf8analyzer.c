#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

bool is_valid_ascii(unsigned char *str) {
	int index = 0;
	while (str[index] != 0){
		if (str[index] > 127){
			return false;
	     	}
		index++;
	}
	return true;
}

void lowercase_to_uppercase_ascii(unsigned char *str){
	int intdex = 0;
	while(str[index] != 0){
		if (str[index] >= 'a' && str[index] <= 'z'){
			printf("%c", str[index] - 32);
		} else {
			printf("%c", str[index]);											}
		index++;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
	       	fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
		return 1;
	}
	
	unsigned char *input = (unsigned char *)argv[1];
	
	printf("Valid ASCII: %s\n", is_valid_ascii(input) ? "Yes" : "No");
       	printf("Uppercase string: ");
	lowercase_to_uppercase_ascii(input);
	printf("\n");
}
