#include "Questions.h"

#define TAILLE 128
#define TailleBuffer 512





int main(int argc, char const *argv[]){

    //Variables
    char cmd_read[TAILLE];
    ssize_t cmd_size;
    pid_t pid;
    int status;
    char Buffer[TailleBuffer];
    
    const char *message = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %";
	write(STDOUT_FILENO, message, strlen(message));

	while(1){
        //const char *prompt = "\nenseash%";
	    //write(STDOUT_FILENO, prompt, strlen(prompt));

        //User input
        cmd_size = read(STDIN_FILENO,cmd_read,TAILLE);
        cmd_read[cmd_size-1] = '\0';

        if(strcmp(cmd_read,"exit")==0 | cmd_size==0){
            const char * message_exit = "\n Bye Bye ...\n\n";
            write(STDOUT_FILENO, message_exit, strlen(message_exit));
            exit(1);
        }

        //Creation of child process and checking for errors during creation 
        //Child process is created to be sure the user can enter mutliple command without exiting the programm
        pid = fork();
        if(pid != 0){
            wait(&status);
            if(WIFEXITED(status)){                                                  //If we have an exit code :
                sprintf(Buffer,"enseash [exit : %d] %%", WEXITSTATUS(status));      //Then we go back on the initial prompt with the exit code
                write(STDIN_FILENO,Buffer,strlen(Buffer));
            } else if (WIFSIGNALED(status)){                                        //If we have a signal code :
                sprintf(Buffer,"enseash [exit : %d] %%", WEXITSTATUS(status));      //Then we go back on the initial prompt with the signal code
                write(STDIN_FILENO,Buffer,strlen(Buffer));
            }
        }

        //Executing incoming commands
        else{
            if(strcmp(cmd_read,"")==0){
                const char * message_enter = "date";
                execlp(message_enter,message_enter,(char*)NULL);
                exit(58);
            }
            else{
                execlp(cmd_read,cmd_read,(char*)NULL);
            }
            
        }

    }
}