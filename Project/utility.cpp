#include "utility.h"
#include <iostream>

using namespace std;

void myStrcpy(char* destination, const char* source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

int myStrcmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        char c1 = str1[i];
        char c2 = str2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
        if (c1 != c2) {
            return c1 - c2;
        }
        i++;
    }
    char c1 = str1[i];
    char c2 = str2[i];
    if (c1 >= 'A' && c1 <= 'Z') c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z') c2 += 32;
    return c1 - c2;
}

int myStrlen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void padString(char* str, int width) {
    int len = myStrlen(str);
    for (int i = len; i < width; i++) {
        str[i] = ' ';
    }
    str[width] = '\0';
}

void intToStr(int num, char* str, int width) {
    int i = 0, temp = num;
    char tempStr[50];
    
    do {
        tempStr[i++] = (temp % 10) + '0';
        temp /= 10;
    } while (temp > 0);
    
    int j = 0;
    while (i > 0) {
        str[j++] = tempStr[--i];
    }
    
    while (j < width) {
        str[j++] = ' ';
    }
    str[j] = '\0';
}

void toLowerCase(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

void trim(char* str) {
    int start = 0, end = myStrlen(str) - 1;
    while (str[start] == ' ') {
        start++;
    }
    while (end >= start && str[end] == ' ') {
        end--;
    }
    int i = 0;
    while (start <= end) {
        str[i++] = str[start++];
    }
    str[i] = '\0'; 
}

void setTextColorRed() {
    cout << "\033[31m";
}

void setTextColorDarkYellow() {
    cout << "\033[33m";
}

void setTextColorCyan() {
    cout << "\033[96m";
}

void setTextColorLightViolet() {
    cout << "\033[95m";
}

void setTextColorLightGreen() {
    cout << "\033[92m";
}

void resetTextColor() {
    cout << "\033[0m";
}