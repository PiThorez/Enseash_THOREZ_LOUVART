#include "Questions.h"

void initialisation(void){
	const char *message = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash\n";
	write(1, message, strlen(message));
}

int main(int argc, char const *argv[]){
    initialisation();
    return 0;
}