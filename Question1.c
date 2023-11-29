#include "Questions.h"

int main(int argc, char const *argv[]){
    const char *bienvenue = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash\n";
	write(STDIN_FILENO, bienvenue, strlen(bienvenue));
    return 0;
}