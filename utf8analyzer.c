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
}


    // implement the UTF-8 analyzer here
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


