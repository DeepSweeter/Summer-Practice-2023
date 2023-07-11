#include"header.h"


int main(){
    int pipes[4][2];
    pid_t procid[4];
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

        int pc = 0;
        char **instructions;
        FILE *fp;
        fp = fopen("instr.txt", "r");
        if (fp == NULL)
        {
            printf("Could not open file\n");
            return 0;
        }
        int count = numberOfLines(fp);
        rewind(fp);
        readlines(&instructions, count, fp);
        write(pipes[0][1], instructions[pc], strlen(instructions[pc]) + 1);
        printf("Instruction fetch:\n\tInstruction address: %d\n\tInstruction: %s\n",0, instructions[0]);
        while(1){

            sleep(4);
            read(pipes[3][0], &pc, sizeof(int));
            if(pc > count-1){
                printf("Instruction fetch: All instructions were executed\n");
                char br [] = "break";
                write(pipes[0][1], br, strlen(br)+1);
                break;
            }
            printf("Instruction fetch:\n\tInstruction address: %d\n\tInstruction: %s\n",pc, instructions[pc]);

            write(pipes[0][1], instructions[pc], strlen(instructions[pc]) + 1);

            //printf("First child: %d\n", data);
        }
        close(pipes[0][1]);
        close(pipes[3][0]);
        
        return 0;
    }
    
    //Instruction decode
    procid[1] = fork();
    if(procid[1] == 0)
    {
        char data[40];
        close(pipes[0][1]);
        close(pipes[1][0]);
        close(pipes[2][0]);
        close(pipes[2][1]);
        close(pipes[3][0]);
        close(pipes[3][1]);
        char ** tokens;
        int count;
        int *decoded;
        char *instr;
        while(1){
        sleep(1);

        read(pipes[0][0], &data, sizeof(data));
        printf("Instruction Decode\n\tInstruction received: %s\n", data);

        if(!strcmp(data , "break")){
            printf("Instruction decode: All instructions were executed\n");
            write(pipes[1][1], data, strlen(data)+1);
            break;
        }

        count = split(data, &tokens);

        
        decoded = (int *)malloc(count * sizeof(int));


        for(int i = 0; i < count; i++)
        {
            decoded[i] = (int)stringToInt(tokens[i], 2);
            //printf("Instruction decode: %s - %d\n", tokens[i], decoded[i]);
        }

        intToString(decoded, count, &instr);
        printf("\tDecoded instruction: %s\n", instr);

        write(pipes[1][1], instr, strlen(instr)+1);

        //Free memory
        for(int i = 0; i < count; i++)
        {
            free(tokens[i]);
        }
        free(tokens);
        free(decoded);
        free(instr);

        }
        close(pipes[1][1]);
        close(pipes[0][0]);

        return 0;
    }

    //Execute
    procid[2] = fork();
    if(procid[2] == 0)
    {
        //Closing pipes
        close(pipes[0][0]);
        close(pipes[0][1]);
        close(pipes[1][1]);
        close(pipes[2][0]);
        close(pipes[3][0]);
        close(pipes[3][1]);

        //Processor logic
        int registers[32] = {0};
        int memory[256];
        int rs, rt, rd;
        int immd;
        int funct;
        int opcode;
        int pcout;
        int memAddr;
        //Transfer data
        char data[40];
        char **tokens;
        int count;
        int *intTokens;
        char br[6];

        while(1){
        sleep(2);

        read(pipes[1][0], &data, 40);

        strcpy(br, data);

        if(!strcmp(br , "break")){
            printf("Execute: All instructions were executed\n");
            write(pipes[2][1], br, strlen(br)+1);
            break;
        }

        printf("Execute: %s\n", data);


        count = split(data, &tokens);

        intTokens = (int *) malloc(count * sizeof(int));

        for(int i = 0; i< count; ++i){
            intTokens[i] = (int)stringToInt(tokens[i], 10);
            printf("\tTokens[%d] = %d\n", i, intTokens[i]);
        }

        opcode = intTokens[0];
        switch(opcode){
            case 8: //ADDI
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                registers[rt]= registers[rs] + immd;
                pcout = 1;
                break;
            case 35: //LW
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                memAddr = (registers[rs] + immd) / 4;
                registers[rt] = memory[memAddr];
                pcout = 1;
                break;
            case 43: //SW
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                memAddr = (registers[rs] + immd) / 4;
                memory[memAddr] = registers[rt];
                pcout = 1;
                break;
            case 4: //BEQ
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                pcout = registers[rs] == registers[rt] ? immd : 1;
                break;
            case 2: //Jump
                immd = intTokens[1];
                pcout = immd;
                break;
            case 0: //R-Type
                funct = intTokens[5];
                rs = intTokens[1];
                rt = intTokens[2];
                rd = intTokens[3];
                pcout = 1;
                switch(funct){
                    case 32: //ADD
                        registers[rd] = registers[rs] + registers[rt];
                    break;
                    case 34: //SUB
                        registers[rd] = registers[rs] - registers[rt];
                    break;
                    case 36: //AND
                        registers[rd] = registers[rs] & registers[rt];
                    break;
                    case 37: //OR
                        registers[rd] = registers[rs] | registers[rt];
                    break;
                    case 42: //SLT
                        registers[rd] = registers[rs] < registers[rt] ? 1:0;
                    break;
                    default:
                        break;
                }
            break;
            default:
                break;
        }

        free(intTokens);
        for(int i =0; i< count;++i)
        {
            free(tokens[i]);
        }
        free(tokens);
        
        int numbers[2] = {opcode, pcout};
        char* dataToPC;
        intToString(numbers, 2, &dataToPC);
        printf("\tData To PC: %s\n", dataToPC);
        


        write(pipes[2][1], dataToPC, strlen(dataToPC) + 1);

        free(dataToPC);
        }
        close(pipes[2][1]);
        close(pipes[1][0]);
        return 0;
    }

    //Program counter
    procid[3] = fork();
    if(procid[3] == 0)
    {
        //Close unused pipes
        close(pipes[0][0]);
        close(pipes[0][1]);
        close(pipes[1][0]);
        close(pipes[1][1]);
        close(pipes[2][1]);
        close(pipes[3][0]);
        int pc = 0;
        while(1){
            char data[20];
            sleep(3);
            read(pipes[2][0], &data, 20);
            if(!strcmp(data , "break")){
                printf("Program Counter: All instructions were executed\n");
                write(pipes[3][1], data, strlen(data)+1);
                break;
            }
            
            char **tokens;
            int countPar = split(data, &tokens);

            int opcode = (int)stringToInt(tokens[0], 10);
            int pcoutAdd = (int)stringToInt(tokens[1], 10);

            printf("Program counter: \n\tPC: %d\n\tOpcode: %d\n", pc, opcode);

            switch(opcode){
                case 0:
                case 8:
                case 35:
                case 43:
                    pc += pcoutAdd;
                    break;
                case 4:
                    pc += pcoutAdd + 1;
                    break;
                case 2:
                    pc = pcoutAdd;
                    break;
                default:
                    pc +=pcoutAdd;
                    break;
            }

            printf("\tNew program counter: %d\n", pc);

             write(pipes[3][1], &pc, sizeof(int));


            //Free memory
            for(int i = 0; i< countPar; ++i)
            {
                free(tokens[i]);
            }
            free(tokens);
        }
        close(pipes[3][1]);
        close(pipes[2][0]);
        return 0;
    }

    //Clock sequence?
    else{
        //printf("Parent\n");
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);

    }
    

    
}



