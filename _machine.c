#include "library.h"

int idx, length;
char cw[256];

void START (char str[]) {
    idx = 0;
    length = 0;
    while (str[strlen(str) - 1] != ';') still(str);
    str[strlen(str) - 1] = '\0'; concat(str, " ;");
    while (str[idx] == ' ') idx++;
    while (str[idx] != ' ' && str[idx] != ';') {
        cw[length] = str[idx];
        idx++; length++;
    } cw[length] = '\0';
}

void INC (char str[]) {
    length = 0;
    while (str[idx] == ' ') idx++;
    while (str[idx] != ' ' && str[idx] != ';') {
        cw[length] = str[idx];
        idx++; length++;
    } cw[length] = '\0';
}

char* READ () {
    return cw;
}

int EOP (char str[]) {
    if (str[idx] == ';') return 1;
    else return 0;
}

void RESET (char str[]) {
    length = 0;
    for (int i = 0; i < 256; i++) str[i] = '\0';
}
