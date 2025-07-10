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
#include <stdio.h>
#include <stdlib.h>

// Decode one UTF-8 code point, return code point and advance *i
// input: utf8 string s, current index *i
// returns Unicode code point as int
int utf8_to_codepoint(const char *s, int *i) {
    unsigned char c = s[*i];
    int codepoint = 0;
    int bytes = 0;

    if ((c & 0x80) == 0) {  // 1-byte ASCII
        codepoint = c;
        bytes = 1;
    } else if ((c & 0xE0) == 0xC0) {  // 2-byte UTF-8
        codepoint = c & 0x1F;
        bytes = 2;
    } else if ((c & 0xF0) == 0xE0) {  // 3-byte UTF-8
        codepoint = c & 0x0F;
        bytes = 3;
    } else if ((c & 0xF8) == 0xF0) {  // 4-byte UTF-8
        codepoint = c & 0x07;
        bytes = 4;
    } else {
        (*i)++;  // invalid byte, skip
        return 0xFFFD;  // replacement char
    }

    for (int j = 1; j < bytes; j++) {
        unsigned char cc = s[*i + j];
        if ((cc & 0xC0) != 0x80) {
            // Invalid continuation byte
            (*i) += j;
            return 0xFFFD;
        }
        codepoint = (codepoint << 6) | (cc & 0x3F);
    }

    *i += bytes;
    return codepoint;
}

// Check if Unicode codepoint is an animal emoji (rough ranges)
int is_animal_emoji(int cp) {
    // Examples of animal emoji ranges:
    // 🐀 U+1F400 to 🦿 U+1F9FF covers many animal emojis and others
    // Let's keep it simple and check 1F400–1F4FF and 1F900–1F9FF as animal emoji zones
    if ((cp >= 0x1F400 && cp <= 0x1F4FF) || (cp >= 0x1F900 && cp <= 0x1F9FF)) {
        return 1;
    }
    return 0;
}

void print_first_6_codepoints(const char *input) {
    printf("Substring of the first 6 code points: ");
    int i = 0, count = 0;
    while (input[i] != '\0' && count < 6) {
        int start = i;
        int cp = utf8_to_codepoint(input, &i);
        if (cp == 0xFFFD) break;  // stop on invalid utf8

        for (int j = start; j < i; j++) {
            putchar(input[j]);
        }
        count++;
    }
    printf("\n");
}

void print_animal_emojis(const char *input) {
    printf("Animal emojis: ");
    int i = 0;
    while (input[i] != '\0') {
        int start = i;
        int cp = utf8_to_codepoint(input, &i);
        if (cp == 0xFFFD) continue;

        if (is_animal_emoji(cp)) {
            for (int j = start; j < i; j++) {
                putchar(input[j]);
            }
        }
    }
    printf("\n");
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
        print_byte_as_cp(argv[1]);
	print_first_6_codepoints(argv[1]);
   	 print_animal_emojis(argv[1]);
return 0;
}

