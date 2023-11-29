#include "Questions.h"

#define TAILLE 128



char cmd_read[TAILLE];
ssize_t cmd_size;
pid_t pid;
int status;


int main(int argc, char const *argv[]){
    
	while(1){
        const char *message = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %\n";
	    write(STDOUT_FILENO, message, strlen(message));
        cmd_size = read(STDIN_FILENO,cmd_read,TAILLE);
        cmd_read[cmd_size-1] = '\0';

        if(strcmp(cmd_read,"exit")==0){
            const char * message_exit = "\n Bye Bye ...\n\n";
            write(STDOUT_FILENO, message_exit, strlen(message_exit));
            exit(1);
        }

        pid = fork();
        if(pid != 0){
            wait(&status);
        }
        else{
            if(strcmp(cmd_read,"")==0){
                const char * message_enter = "date";
                execlp(message_enter,message_enter,(char*)NULL);
            }
            else{
                execlp(cmd_read,cmd_read,(char*)NULL);
            }
            
        }

    }
}