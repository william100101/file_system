#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "wrapper.h"

#define MAX_NUMBER_INPUT 2048
#define MAX_NUMBER_ARGS 64

/*

The feature that I chose to implement was linux's change directory command cd.
To use this feature do "cd" and then in one arguement after with no spaces provide a path that does not begin with "/"

An example of its use could be doing "cd .." to take you one directory back.
Another could be if your in the csci315 folder, doing "cd Labs/Lab9" to get the Lab9 folder.

*/

int main(int argc, char *argv[]) {

    //pretty much globals
    char input[MAX_NUMBER_INPUT];
    char input_copy[MAX_NUMBER_INPUT]; // check
    //char *args[MAX_NUMBER_ARGS];
    int enter_count = 0;
    
    

    while(1){
        
        printf("ishell>");
        //read input
        fgets(input, MAX_NUMBER_INPUT, stdin);
        input[strlen(input) - 1] = '\0';

        strcpy(input_copy, input);

        //problem 4 stuff
        if(strlen(input) == 0){
            enter_count++;
        }
        else{
            enter_count = 0;
        }
        if(enter_count == 2){
            execlp("ls", "ls", (char *)NULL);
        }

        //for semicolon handling
        char *command_1 = strtok(input_copy, ";");
        char *command_2 = strtok(NULL, ";");

        if (command_1 != NULL){ //command 1
            char *args_first_half[MAX_NUMBER_ARGS];

            args_first_half[0] = strtok(command_1, " ");//command
            args_first_half[1] = strtok(NULL, " "); //command
            args_first_half[2] = strtok(NULL, " "); //command
            args_first_half[3] = strtok(NULL, " "); //command
            args_first_half[4] = strtok(NULL, " "); //command
            args_first_half[5] = strtok(NULL, " "); //command
            args_first_half[6] = strtok(NULL, " "); //command
            args_first_half[7] = strtok(NULL, " "); //command
            args_first_half[8] = strtok(NULL, " "); //command        

            //FORKING HERE
            int pid;
            int exec_ret;
            
            if((pid = Fork()) == 0){//child
                //problem 5, implementation of cd
                if(strcmp(args_first_half[0], "cd") == 0){
                    chdir(args_first_half[1]);
                }
                else{//base case
                    //exec_ret = execlp(args[0], args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], (char *)NULL);

                    if((exec_ret = execlp(args_first_half[0], args_first_half[0], args_first_half[1], args_first_half[2], args_first_half[3], args_first_half[4], args_first_half[5], args_first_half[6], args_first_half[7], args_first_half[8], (char *)NULL)) == -1){
                            printf("[ishell: program terminated abnormally]\n");
                    }
                    else{
                            //printf("[ishell: program terminated successfully]");
                            
                    }
                }
            }
            else{//parent
                int stat;
                wait(&stat);
                
                printf("[ishell: program terminated successfully]\n");
            }

        }

        if(command_2 != NULL){
            char *args_second_half[MAX_NUMBER_ARGS];

            args_second_half[0] = strtok(command_2, " ");//command
            args_second_half[1] = strtok(NULL, " "); //command
            args_second_half[2] = strtok(NULL, " "); //command
            args_second_half[3] = strtok(NULL, " "); //command
            args_second_half[4] = strtok(NULL, " "); //command
            args_second_half[5] = strtok(NULL, " "); //command
            args_second_half[6] = strtok(NULL, " "); //command
            args_second_half[7] = strtok(NULL, " "); //command
            args_second_half[8] = strtok(NULL, " "); //command        

            //FORKING HERE
            int pid;
            int exec_ret;
            
            if((pid = Fork()) == 0){//child
                //problem 5, implementation of cd
                if(strcmp(args_second_half[0], "cd") == 0){
                    chdir(args_second_half[1]);
                }
                else{//base case
                    //exec_ret = execlp(args[0], args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], (char *)NULL);

                    if((exec_ret = execlp(args_second_half[0], args_second_half[0], args_second_half[1], args_second_half[2], args_second_half[3], args_second_half[4], args_second_half[5], args_second_half[6], args_second_half[7], args_second_half[8], (char *)NULL)) == -1){
                            printf("[ishell: program terminated abnormally]\n");
                    }
                    else{
                            printf("[ishell: program terminated successfully]");
                            
                    }
                }
            }
            else{//parent
                int stat;
                wait(&stat);

                printf("[ishell: program terminated successfully]\n");
            }


        }


        //clear input
        for (int i = 0; i < sizeof(input); i++){
            input[i] = '\0';
            input_copy[i] = '\0';
        }

        
    }

}