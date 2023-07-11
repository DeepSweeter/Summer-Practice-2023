#include <stdio.h>
#include<sys/wait.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

// works
int numberOfLines(FILE *fp){
    int count = 0;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    return count - 1;
}

//works
void readlines(char ***instructions, int n, FILE *fp){
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;

    *instructions = (char**)malloc(n* sizeof(char*));

    while((read = getline(&line, &len, fp)) != -1){
        if(strstr(line, "//") == NULL)
        {
            (*instructions)[i] = (char*)malloc(read* sizeof(char));
            strncpy((*instructions)[i], line, read);
            (*instructions)[i][read-1] = '\0';
            i++;
        }
    }
    if(line)
        free(line);

}

int split(char *instruction, char *** tokens){
    int i, count = 0;
    for (i=0; i < strlen(instruction); i++)
    {
        if(instruction[i] == '_'){
            count ++;
        }
    }
        // count += (instruction[i] == "_");
    count++;

    char * token = strtok(instruction, "_");
    i=0;
    *tokens = (char **) malloc(count * sizeof(char *));
    while(token != NULL){
        (*tokens)[i] = (char *) malloc(strlen(token) * sizeof(char));
        strncpy((*tokens)[i], token, strlen(token));
        (*tokens)[i][strlen(token)] = '\0';
        i++;
        token= strtok(NULL, "_");
    }

    if(token)
        free(token);

    return count;
}

long  stringToInt(char *number, int base){
    long result;
    //char *pEnd;

    result = strtol(number, NULL, base);
    if(strlen(number)>=16){
        if(result >=0x7fff){
            result = result | 0xffffffffffff0000;        
        }
    }
    return result;
}

void intToString(int* numbers, int n, char** instruction){
    char instString[50] = {'\0'};
    char interm[20];

    for(int i =0; i< n; i++)
    {
        sprintf(interm, "%d", numbers[i]);
        strcat(instString, interm);
        if(i != n-1)
            strcat(instString,"_");
    }

    (*instruction) = (char*)malloc(strlen(instString) * sizeof(char));
    (*instruction)[strlen(instString)] = '\0';
    strncpy((*instruction),instString, strlen(instString));

}


int main(){

    FILE *fp;

    char ** instructions;
    char ** tokens;
    char * decodedInstructions;
    fp = fopen("instr.txt", "r");

    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 0;
    }
    int count = numberOfLines(fp);
    rewind(fp);

    readlines(&instructions, count, fp);
   // printf("File has %d lines\n", count);
    int countTokens = split(instructions[0], &tokens);

    int numbers[]= {8, 9, 9, -3};
    //char *pEnd;
    // long  li1, li2;
    // li1 = stringToInt(number1, 2);
    // li2 = stringToInt(number2, 2);

    // printf("Numbers:\n%ld\n%ld\n", li1, li2);



    // for(int i = 0; i < countTokens; i++)
    // {
    //     printf("%s\n", tokens[i]);
    // }
    //printf("%zu\n", sizeof(tokens));

    intToString(numbers, 4, &decodedInstructions);

    printf("Decoded: %s\n", decodedInstructions);

    free(decodedInstructions);

    for(int i = 0; i < count; i++)
    {
        free(instructions[i]);
    }
    free(instructions);

    for(int i = 0; i < countTokens; i++)
    {
        free(tokens[i]);
    }
    free(tokens);

    fclose(fp);


    return 0;


    
}



