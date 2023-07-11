#ifndef HEADER_H_
#define HEADER_H_
#include <stdio.h>
#include<sys/wait.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>


int numberOfLines(FILE *fp);
void readlines(char ***instructions, int n, FILE *fp);
void intToString(int* numbers, int n, char** instruction);
int split(char *instruction, char *** tokens);
long  stringToInt(char *number, int base);

#endif