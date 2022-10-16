#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

void child_sighandler(int signal_number)
{
    printf("Received %d", signal_number);
}

int main(int argc, char *argv[])
{
    char *environment[] = {NULL};

    if (!(access(argv[2], F_OK) == 0))
    {
        perror("execve");
        exit(0);
    }

    int seconds = atoi(argv[1]);

    // separate command and args for child
    char *temp_arg[argc];

    for (int i = 2; i < argc; i++)
    {
        temp_arg[i - 2] = argv[i];
    }

    // start fork here
    pid_t pid = fork();

    // error if not enough arguments
    if (argc <= 2)
    {
        perror("Command error\n");
        exit(1);
    }

    // error if seconds is negative
    if (seconds < 0)
    {
        perror("'seconds' argument can't be negative\n");
        exit(1);
    }

    // error if forking fails
    if (pid < 0)
    {
        printf("Error while forking");
    }
    // child process
    else if (pid == 0)
    {
        // register signal handler

        signal(SIGCHLD, child_sighandler);

        // run child command
        printf("Running from child \n");
        printf("arg 0 : %s\n", temp_arg[0]);
        printf("arg 1 : %s\n", temp_arg[1]);

        execve(temp_arg[0], temp_arg, environment);

        exit(0);
    }
    // parent process
    else
    {
        int ret;

        sleep(seconds);

        ret = kill(pid, SIGTERM);
        if (ret == -1)
        {
            perror("kill");
        }

        exit(0);
    }
}