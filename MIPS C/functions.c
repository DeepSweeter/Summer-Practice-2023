#include"header.h"

//Return the number of lines in a file without the first one because is the start address
int numberOfLines(FILE *fp){
    int count = 0;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    return count - 1;
}

//Reads all the lines in a file and writes in an array of char*
//Because we want to modify the parameter instructions we pass it as "char ***"
// The parameter n is the number of lines in the file
//Remember to dealocate instructions after using it
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
// numbers -> an arrays of the numbers we want to put in a string
// n -> the number of elements
// instruction -> a char array to write the result
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

// Splits the instruction by '_' and it puts in an array of strings
// tokens can be seen as a list of strings that remain after split
int split(char *instruction, char *** tokens){
    int i, count = 0;
    for (i=0; i < strlen(instruction); i++)
    {
        if(instruction[i] == '_'){
            count ++;
        }
    }
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

// Converts a string to an Int,
// base is the base that is written in the string
// Works for base = 2 (didn't try with other bases because it's not necessary for the scope of this program)
long  stringToInt(char *number, int base){
    long result;

    result = strtol(number, NULL, base);
    if(strlen(number)>=16){
        if(result >=0x7fff){
            result = result | 0xffffffffffff0000;        
        }
    }
    return result;
}