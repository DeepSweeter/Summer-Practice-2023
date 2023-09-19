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
    //Shared memory if necessary


    //Instruction fetch
    procid[0] = fork();
    if(procid[0] == 0)
    {
        //Close unused pipes   
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
        for(int i = 0; i < count; ++i){
            free(instructions[i]);
        }
        free(instructions);
        close(pipes[0][1]);
        close(pipes[3][0]);
        
        exit(0);
    }
    
    //Instruction decode
    procid[1] = fork();
    if(procid[1] == 0)
    {
        //Close the unused pipes
        close(pipes[0][1]);
        close(pipes[1][0]);
        close(pipes[2][0]);
        close(pipes[2][1]);
        close(pipes[3][0]);
        close(pipes[3][1]);

        char data[40];
        char ** tokens;
        int count;
        int *decoded;
        char *instr;
        while(1){

        read(pipes[0][0], &data, sizeof(data));

        if(!strcmp(data , "break")){
            printf("Instruction decode: All instructions were executed\n");
            write(pipes[1][1], data, strlen(data)+1);
            break;
        }
        printf("Instruction Decode\n\tInstruction received: %s\n", data);

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

        exit(0);

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
            // printf("\tFields[%d] = %d\n", i, intTokens[i]);
        }

        opcode = intTokens[0];
        switch(opcode){
            case 8: //ADDI
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                printf("\tInstr\tRS\tRT\tIMM\n\t%s\t%d\t%d\t%d\n", "ADDI", rs, rt, immd);
                printf("\tResults:\n\t\tSource Register[%d] = %d\n\t\t", rs, registers[rs]);
                if(rt == 0){
                    registers[rt] = 0;
                }else{
                registers[rt]= registers[rs] + immd;
                }
                pcout = 1;
                printf("Destination Register[%d] = %d\n\t\tPCout += 1\n", rt, registers[rt]);
                break;
            case 35: //LW
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                memAddr = (registers[rs] + immd) / 4;
                printf("\tInstr\tRS\tRT\tIMM\n\t%s\t%d\t%d\t%d\n", " LW", rs, rt, immd);
                printf("\tResults:\n\t\tSource Register[%d] = %d\n\t\t",rs, registers[rs]);
                if(rt == 0){
                    registers[rt] =0;
                }else{
                registers[rt] = memory[memAddr];
                }
                pcout = 1;
                printf("Destination Register[%d] = %d\n\t\t"
                        "Source Memory[%d] = %d\n\t\t"
                        "PCout += 1\n",
                        rt, registers[rt], memAddr, memory[memAddr]);
                break;
            case 43: //SW
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                printf("\tInstr\tRS\tRT\tIMM\n\t%s\t%d\t%d\t%d\n", " SW", rs, rt, immd);
                memAddr = (registers[rs] + immd) / 4;
                memory[memAddr] = registers[rt];
                pcout = 1;
                printf("\tResults:\n\t\tSource Register[%d] = %d\n\t\t"
                "Addr Register[%d] = %d\n\t\t"
                "Destination Memory[%d] = %d\n\t\t"
                "PCout += 1\n",
                 rs, registers[rs], rt, registers[rt], memAddr, memory[memAddr]);
                break;
            case 4: //BEQ
                rs = intTokens[1];
                rt = intTokens[2];
                immd = intTokens[3];
                printf("\tInstr\tRS\tRT\tIMM\n\t%s\t%d\t%d\t%d\n", " BEQ", rs, rt, immd);
                if(registers[rs] == registers[rt]){
                    pcout = immd;
                    printf("\tResults:\n\t\t"
                    "Register[%d] = %d\n\t\t"
                    "Register[%d] = %d\n\t\t"
                    "Branch to PCout %+d\n",
                    rs, registers[rs],rd, registers[rd], pcout);
                }
                else{
                    pcout = 0;
                    printf("\tResults:\n\t\t"
                    "Register[%d] = %d\n\t\t"
                    "Register[%d] = %d\n\t\t"
                    "Branch not executed => PCOut +=1\n",
                    rs, registers[rs],rd, registers[rd]);
                }

                break;
            case 2: //Jump
                immd = intTokens[1];
                pcout = immd;
                printf("\tInstr\tIMM\n\t%s\t%d\n", "  J", immd);
                printf("\tResults:\n\t\tJump to the address %d\n", immd);
                break;
            case 0: //R-Type
                funct = intTokens[5];
                rs = intTokens[1];
                rt = intTokens[2];
                rd = intTokens[3];
                pcout = 1;

                switch(funct){
                    case 32: //ADD
                        printf("\tInstr\tRS\tRT\tRD\tFUNCT\n\t%s\t%d\t%d\t%d\t%s\n", "R-Type", rs, rt, rd, "ADD"); 
                        printf("\tResults\n\t\t"
                            "Source 1 Register[%d] = %d\n\t\t"
                            "Source 2 Register[%d] = %d\n\t\t",
                            rs, registers[rs], rt, registers[rt]);
                        registers[rd] = registers[rs] + registers[rt];
                    break;
                    case 34: //SUB
                        printf("\tInstr\tRS\tRT\tRD\tFUNCT\n\t%s\t%d\t%d\t%d\t%s\n", "R-Type", rs, rt, rd, "SUB");  
                        printf("\tResults\n\t\t"
                            "Source 1 Register[%d] = %d\n\t\t"
                            "Source 2 Register[%d] = %d\n\t\t",
                            rs, registers[rs], rt, registers[rt]);
                        registers[rd] = registers[rs] - registers[rt];

                    break;
                    case 36: //AND
                        printf("\tInstr\tRS\tRT\tRD\tFUNCT\n\t%s\t%d\t%d\t%d\t%s\n", "R-Type", rs, rt, rd, "AND");  
                        printf("\tResults\n\t\t"
                            "Source 1 Register[%d] = %d\n\t\t"
                            "Source 2 Register[%d] = %d\n\t\t",
                            rs, registers[rs], rt, registers[rt]);
                        registers[rd] = registers[rs] & registers[rt];

                    break;
                    case 37: //OR
                        printf("\tInstr\tRS\tRT\tRD\tFUNCT\n\t%s\t%d\t%d\t%d\t%s\n", "R-Type", rs, rt, rd, "OR");  
                        printf("\tResults\n\t\t"
                            "Source 1 Register[%d] = %d\n\t\t"
                            "Source 2 Register[%d] = %d\n\t\t",
                            rs, registers[rs], rt, registers[rt]);
                        registers[rd] = registers[rs] | registers[rt];

                    break;
                    case 42: //SLT
                        printf("\tInstr\tRS\tRT\tRD\tFUNCT\n\t%s\t%d\t%d\t%d\t%s\n", "R-Type", rs, rt, rd, "SLT");  
                        printf("\tResults\n\t\t"
                            "Source 1 Register[%d] = %d\n\t\t"
                            "Source 2 Register[%d] = %d\n\t\t",
                            rs, registers[rs], rt, registers[rt]);
                        registers[rd] = registers[rs] < registers[rt] ? 1:0;

                    break;
                    default:
                        break;
                }
                if(rd == 0)
                {
                    registers[rd] = 0;
                }
                printf("Destination Register[%d] = %d\n\t\t"
                    "PCOut += 1\n",
                    rd, registers[rd]); 
            break;
            default:
                break;
        }

        //Free memory
        free(intTokens);
        for(int i =0; i< count;++i)
        {
            free(tokens[i]);
        }
        free(tokens);
        
        //Write to PC
        int numbers[2] = {opcode, pcout};
        char* dataToPC;
        intToString(numbers, 2, &dataToPC);
        printf("\tData To PC: %s\n", dataToPC);
        


        write(pipes[2][1], dataToPC, strlen(dataToPC) + 1);
        //Free memory
        free(dataToPC);
        }
        close(pipes[2][1]);
        close(pipes[1][0]);
        exit(0);

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
            read(pipes[2][0], &data, 20);

            //Break condition
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
        exit(0);

    }

    //Clock sequence
    else{
        for(int i =0; i<4; ++i){
            kill(procid[i], SIGSTOP);
        }
        const int cycle = 1;
        int clock = 0;
        while(1){
            int status;
            pid_t terminated = waitpid(-1, &status, WNOHANG);

            if(terminated> 0){
                wait(NULL);
                wait(NULL);
                wait(NULL);
                wait(NULL);
                printf("\nAll processes terminated\n");
                break;
            }
            else if(terminated == 0){

            //Instruction Fetch
            sleep(cycle);
            printf("\nClock: #%d\n",clock+=cycle);
            kill(procid[0], SIGCONT);
            kill(procid[1], SIGSTOP);
            kill(procid[2], SIGSTOP);
            kill(procid[3], SIGSTOP);
            //Instruction Decode
            sleep(cycle);
            printf("\nClock: #%d\n",clock+=cycle);

            kill(procid[0], SIGSTOP);
            kill(procid[1], SIGCONT);
            kill(procid[2], SIGSTOP);
            kill(procid[3], SIGSTOP);
            //Execute
            sleep(cycle);
            printf("\nClock: #%d\n",clock+=cycle);

            kill(procid[0], SIGSTOP);
            kill(procid[1], SIGSTOP);
            kill(procid[2], SIGCONT);
            kill(procid[3], SIGSTOP);
            //Program counter
            sleep(cycle);
            printf("\nClock: #%d\n",clock+=cycle);

            kill(procid[0], SIGSTOP);
            kill(procid[1], SIGSTOP);
            kill(procid[2], SIGSTOP);
            kill(procid[3], SIGCONT);
            }
            else{
                perror("waitpid");
                exit(1);
            }


        }

        //printf("Parent\n");
        exit(EXIT_SUCCESS);

    }
    

    
}



