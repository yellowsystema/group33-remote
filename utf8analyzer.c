#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

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
	int index = 0; 
	while (str[index] != 0){
		if (str[index] >= 'a' && str[index] <= 'z'){
			printf("%c", str[index] - 32);
		} else {
			printf("%c", str[index]);
		}
		index++;
	}
}

int get_bytes_length (char *str){
    int len = 0;
    while (str[len] != 0){
        len += 1;
    }
    return len;
}

int num_codepoints (char *str){
    int num = 0;
    for (int i = 0; str[i] != 0; i++){
        unsigned char byte = str[i];
        if ((byte & 0xC0) != 0x80){
            num += 1;
        }
    }
    return num;
}

