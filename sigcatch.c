#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// initialize array of signals from Prof. Bishop SIGNAMES file
const char *signals[32] =
    {
        "Signal 0", /*  signal 0 -- meaningless */
        "SIGHUP",   /* 1 */
        "SIGINT",
        "SIGQUIT",
        "SIGILL",
        "SIGTRAP",
        "SIGABRT",
        "SIGEMT",
        "SIGFPE",
        "SIGKILL",
        "SIGBUS", /* 10 */
        "SIGSEGV",
        "SIGSYS",
        "SIGPIPE",
        "SIGALRM",
        "SIGTERM",
        "SIGUSR1",
        "SIGUSR2",
        "SIGCHLD",
        "SIGCONT",
        "SIGTSTP", /* 20 */
        "SIGTTIN",
        "SIGTTOU",
        "SIGSTOP",
        "SIGXCPU",
        "SIGXFSZ",
        "SIGVTALRM",
        "SIGPROF",
        "SIGWINCH",
        "SIGPOLL",
        "SIGUSR1", /* 30 */
        "SIGUSR2",
};

/* signal handler */
void signal_switch(int signum, siginfo_t *siginfo, void *arg)
{

    time_t signal_time;
    time(&signal_time);

    char *time_string = asctime(localtime(&signal_time));
    time_string[strcspn(time_string, "\n")] = 0;

    printf("%s Received signal %d (%s)\n", time_string, signum, signals[signum]);

    /*
    Example format for output:
    Fri Sep 19 23:34:19 2022 Received signal 1 (SIGHUP)
    */
}

int main()
{
    /*set up signals to be caught by signal_switch()*/
    struct sigaction sig;
    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = signal_switch;

    sigaction(SIGHUP, &sig, 0);
    sigaction(SIGINT, &sig, 0);
    sigaction(SIGQUIT, &sig, 0);
    sigaction(SIGILL, &sig, 0);
    sigaction(SIGTRAP, &sig, 0);
    sigaction(SIGABRT, &sig, 0);
    sigaction(SIGEMT, &sig, 0);
    sigaction(SIGFPE, &sig, 0);
    sigaction(SIGKILL, &sig, 0);
    sigaction(SIGBUS, &sig, 0);
    sigaction(SIGSEGV, &sig, 0);
    sigaction(SIGSYS, &sig, 0);
    sigaction(SIGPIPE, &sig, 0);
    sigaction(SIGALRM, &sig, 0);
    sigaction(SIGTERM, &sig, 0);
    sigaction(SIGUSR1, &sig, 0);
    sigaction(SIGUSR2, &sig, 0);
    sigaction(SIGCHLD, &sig, 0);
    sigaction(SIGCONT, &sig, 0);
    sigaction(SIGTSTP, &sig, 0);
    sigaction(SIGTTIN, &sig, 0);
    sigaction(SIGTTOU, &sig, 0);
    sigaction(SIGSTOP, &sig, 0);
    sigaction(SIGXCPU, &sig, 0);
    sigaction(SIGXFSZ, &sig, 0);
    sigaction(SIGVTALRM, &sig, 0);
    sigaction(SIGPROF, &sig, 0);
    sigaction(SIGWINCH, &sig, 0);

    /* Keep looping and printing the pid*/
    while (1)
    {
        printf("%d : Waiting for signal \n", getpid());
        sleep(1);
    }

    return 0;
}