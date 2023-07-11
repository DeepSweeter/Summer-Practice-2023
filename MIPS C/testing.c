#include"header.h"


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
    char data [40]={ "8_8_8_1"};
   // printf("File has %d lines\n", count);
    int countTokens = split(data, &tokens);
    int *intTokens;
    intTokens = (int *) malloc(countTokens * sizeof(int));

    for(int i = 0; i< countTokens; ++i){
        intTokens[i] = (int)stringToInt(tokens[i], 10);
        printf("\tTokens[%d] = %d\n", i, intTokens[i]);
    }

    free(intTokens);


    
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

    //intToString(numbers, 4, &decodedInstructions);

    //printf("Decoded: %s\n", decodedInstructions);

    //free(decodedInstructions);

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



