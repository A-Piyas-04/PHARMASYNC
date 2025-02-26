#ifndef UTILITY_H
#define UTILITY_H

using namespace std;

void myStrcpy(char* destination, const char* source);
int myStrcmp(const char* str1, const char* str2);
int myStrlen(const char* str);
void padString(char* str, int width);
void intToStr(int num, char* str, int width);
void toLowerCase(char* str);
void trim(char* str);

#endif // UTILITY_H