#include "Questions.h"

int main(int argc, char const *argv[]){
    const char *message = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash %\n";
	write(1, message, strlen(message));
	
	const char *messageRead = "\0";
	const char *command = "date";
	const char *commandExit = "exit";


    if(messageRead == "exit"){
    	write(1,"Bye bye...\n",strlen("Bye bye...\n"));
    	execlp(commandExit,commandExit,(char *)NULL);

    }

    else if(messageRead == "\0"){
    	execlp(command,command, (char *)NULL);
    }

    else{
    	write(1,"oops",strlen("oops"));
    }
    return 0;
}