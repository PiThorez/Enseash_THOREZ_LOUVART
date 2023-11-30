#include "Questions.h"

#define TAILLE 128


int main(int argc, char const *argv[]){

    //Variables
    char cmd_read[TAILLE];
    ssize_t cmd_size;
    pid_t pid;
    int status;
    
    const char *message = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.";
	write(STDIN_FILENO, message, strlen(message));
	
    while(1){
        const char *prompt = "\nenseash %";
	    write(STDIN_FILENO, prompt, strlen(prompt));    
        cmd_size = read(STDOUT_FILENO,cmd_read,TAILLE);
        cmd_read[cmd_size-1] = '\0';



        //Creation of child process and checking for errors during creation 
        //Child process is created to be sure the user can enter mutliple command without exiting the programm
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