#include <stdio.h>
#include<sys/wait.h>
#include<assert.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int numberOfLines(FILE *fp){
    int count = 0;
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    return count - 1;
}

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
    int pipes[4][2];
    pid_t procid[4];
    int current_id = 0;
    for(int i = 0; i < 4; ++i){
        if(pipe(pipes[i]) == -1){
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }


    //Instruction fetch
    procid[0] = fork();
    if(procid[0] == 0)
    {
        close(pipes[0][0]);
        close(pipes[1][0]);
        close(pipes[1][1]);
        close(pipes[2][0]);
        close(pipes[2][1]);
        close(pipes[3][1]);

        int data = 7;
        char **instructions;
        FILE *fp;
        fp = fopen("instr.txt", "r");
        if (fp == NULL)
        {
            printf("Could not open file\n");
            return 0;
        }
        int count = numberOfLines(fp);
        fclose(fp);
        fp = fopen("instr.txt", "r");
        readlines(&instructions, count, fp);
        write(pipes[0][1], instructions[0], strlen(instructions[0]) + 1);

        while(1){

            //close(pipes[0][1]);

            sleep(4);
            read(pipes[3][0], &data, sizeof(int));
            data++;

            printf("First child: %d\n", data);
        }
        
        return 0;
    }
    //Instruction decode
    procid[1] = fork();
    if(procid[1] == 0)
    {
        while(1){
        char data[40];
        close(pipes[0][1]);
        close(pipes[1][0]);
        close(pipes[2][0]);
        close(pipes[2][1]);
        close(pipes[3][0]);
        close(pipes[3][1]);
        sleep(1);

        read(pipes[0][0], &data, sizeof(data));

        //write(pipes[1][1], &data, sizeof(int));
        // close(pipes[1][1]);
        // close(pipes[0][0]);

        printf("Second child: %s\n", data);
        }
        return 0;
    }
    //Execute
    procid[2] = fork();
    if(procid[2] == 0)
    {
        while(1){
        int data;
        close(pipes[0][0]);
        close(pipes[0][1]);
        close(pipes[1][1]);
        close(pipes[2][0]);
        close(pipes[3][0]);
        close(pipes[3][1]);
        sleep(2);

        read(pipes[1][0], &data, sizeof(int));
        data++;

        write(pipes[2][1], &data, sizeof(int));
        // close(pipes[2][1]);
        // close(pipes[1][0]);

        printf("Third child: %d\n", data);
        }
        return 0;
    }

    //Program counter
    procid[3] = fork();
    if(procid[3] == 0)
    {
        while(1){
        int data;
        close(pipes[0][0]);
        close(pipes[0][1]);
        close(pipes[1][0]);
        close(pipes[1][1]);
        close(pipes[2][1]);
        close(pipes[3][0]);
        sleep(3);
        read(pipes[2][0], &data, sizeof(int));
        data++;
        

        write(pipes[3][1], &data, sizeof(int));
        // close(pipes[3][1]);
        // close(pipes[2][0]);
        printf("Fourth child: %d\n", data);
        }
        return 0;
    }

    //Clock sequence?
    else{
        printf("Parent\n");
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);

    }
    

    
}



