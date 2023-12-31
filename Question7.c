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

        // Creation of child process and checking for errors during creation
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
            // Executing incoming commands
            char *args[TAILLE];
            int i = 0;
            char *token = strtok(cmd_read, " ");
            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            int input_fd = STDIN_FILENO;
            int output_fd = STDOUT_FILENO;

            for (int j = 0; j < i; ++j) {
                if (strcmp(args[j], "<") == 0) {
                    // Input redirection
                    args[j] = NULL; // Remove '<' from arguments
                    input_fd = open(args[j + 1], O_RDONLY);
                } else if (strcmp(args[j], ">") == 0) {
                    // Output redirection
                    args[j] = NULL; // Remove '>' from arguments
                    output_fd = open(args[j + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
                }
            }

            dup2(input_fd, STDIN_FILENO);
            dup2(output_fd, STDOUT_FILENO);

            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
        }
    }
}
