#include <stdio.h>
#include<sys/wait.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

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


int main(){

    FILE *fp;
    FILE *fp2;
    char ** instructions;
    fp = fopen("instr.txt", "r");
    fp2 = fopen("instr.txt", "r");

    if (fp == NULL)
    {
        printf("Could not open file\n");
        return 0;
    }
    int count = numberOfLines(fp);
    fclose(fp);
    fp = fopen("instr.txt", "r");

    readlines(&instructions, count, fp);
    printf("File has %d lines\n", count);

    for(int i = 0; i < count; i++)
    {
        printf("%s\n", instructions[i]);
    }

    for(int i = 0; i < count; i++)
    {
        free(instructions[i]);
    }
    free(instructions);

    fclose(fp);
    fclose(fp2);


    return 0;


    
}



