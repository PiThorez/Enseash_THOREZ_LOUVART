#include "Questions.h"

#define TAILLE 128
#define TailleBuffer 512
#define ConversionNtoM 1000000

int main(int argc, char const *argv[]) {

    // Variables
    char cmd_read[TAILLE];
    ssize_t cmd_size;
    pid_t pid;
    int status;
    char Buffer[TailleBuffer];

    const char *message = "\nBienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
    write(STDOUT_FILENO, message, strlen(message));

    while (1) {

        // User input
        cmd_size = read(STDOUT_FILENO, cmd_read, TAILLE);
        cmd_read[cmd_size - 1] = '\0';

        if (strcmp(cmd_read, "exit") == 0 || cmd_size == 0) {
            const char *message_exit = "\n Bye Bye ...\n\n";
            write(STDOUT_FILENO, message_exit, strlen(message_exit));
            exit(1);
        }

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start);

        pid = fork();
        if (pid != 0) {
            wait(&status);
            clock_gettime(CLOCK_REALTIME, &end);
            if (WIFEXITED(status)) {
                // If we have an exit code
                sprintf(Buffer, "enseash [exit : %d | %ld ms] %% ", WEXITSTATUS(status), ((end.tv_nsec - start.tv_nsec) / ConversionNtoM));
                write(STDOUT_FILENO, Buffer, strlen(Buffer));
            } else if (WIFSIGNALED(status)) {
                // If we have a signal code
                sprintf(Buffer, "enseash [sig : %d | %ld ms] %% ", WTERMSIG(status), ((end.tv_nsec - start.tv_nsec) / ConversionNtoM));
                write(STDOUT_FILENO, Buffer, strlen(Buffer));
            }
        } else {
            char *commands[TAILLE];
            int command_count = 0;
            char *token = strtok(cmd_read, "|");
            while (token != NULL) {
                commands[command_count++] = token;
                token = strtok(NULL, "|");
            }

            int pipes[2];
            for (int i = 0; i < command_count - 1; ++i) {
                pipe(pipes);
                pid_t pid2 = fork();

                if (pid2 == 0) {
                    close(pipes[0]);                
                    dup2(pipes[1], STDOUT_FILENO); 
                    close(pipes[1]);               

                    char *args[TAILLE];
                    int arg_count = 0;
                    char *cmd_token = strtok(commands[i], " ");
                    while (cmd_token != NULL) {
                        args[arg_count++] = cmd_token;
                        cmd_token = strtok(NULL, " ");
                    }
                    args[arg_count] = NULL;

                    execvp(args[0], args);
                    perror("Error executing command");
                    exit(EXIT_FAILURE);
                } else {
                    wait(NULL);
                    close(pipes[1]);               
                    dup2(pipes[0], STDIN_FILENO);  
                    close(pipes[0]);                
                }
            }

            char *args[TAILLE];
            int i = 0;
            char *cmd_token = strtok(commands[command_count - 1], " ");
            while (cmd_token != NULL) {
                args[i++] = cmd_token;
                cmd_token = strtok(NULL, " ");
            }
            args[i] = NULL;

            execvp(args[0], args);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    }
}
