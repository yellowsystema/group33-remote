#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

int byte_at_codepoint(char input[], size_t length) {
	if (length == 0) {
		return 0;
	}
	
	unsigned char c = input[0];
	int num_bytes = 0;

	if (c < 128) {
		num_bytes = 1;
	} else if (( c & 0xE0) == 0xC0) {
		num_bytes = 2;
	} else if ((c & 0xF0) == 0xE0) {
		num_bytes = 3;
	} else if ((c & 0xF8) == 0xF0) {
		num_bytes = 4;
	} else {
		return -1;
	}

	if (length < num_bytes) {
		return -1;
	}

	for (int i = 1; i < num_bytes; i++) {
		if ((input[i] & 0xC0) != 0x80) {
			return -1;
		}
	}
	return num_bytes;
}

int print_byte_as_cp(char str[]) {
	int len = strlen(str);
	bool is_first = true;
	printf("Bytes per codepoint:");
	for (int i = 0; i < len; ) {
		int char_len = byte_at_codepoint(&str[i], len - i);
		if (len <= 0) {
			if (len < 0) {
				return 1;
			}
				break;
		}
		if (!is_first) {
			printf(" ");
		}
		is_first = false;
		printf("%d", char_len);
		i += char_len;
	}
		printf("\n");
		return 0;
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
	return print_byte_as_cp(argv[1]);

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
