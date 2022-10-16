#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
#include <ctype.h>

const int QUANTA = 5;
int job_count = 0;

// job struct============================================
typedef struct job
{
    char name[10];
    int run_time;
    float block_prob;
    int time_to_run;
    int runtime_left;
    struct job *prev;
    struct job *next;

} job;
//=======================================================

// cpu struct============================================
typedef struct
{
    int time_busy;
    int time_idle;
    double utilization;
    int dispatches;
    double throughput;

} CPU;

// constructor function to make a new job struct============================================
job *new_job(char name[],
             int run_time,
             float block_prob,
             int time_to_run,
             int runtime_left,
             struct job *prev,
             struct job *next)
{
    job *j = malloc(sizeof(job));
    strcpy(j->name, name);
    j->run_time = run_time;
    j->block_prob = block_prob;
    j->time_to_run = time_to_run;
    j->runtime_left = runtime_left;
    j->prev = prev;
    j->next = next;

    return j;
}
//========================================================================================
void process_count(char *file_name)
{
    FILE *fp;
    int count = 0;
    char c;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror(file_name);
    }

    // Counting the amount of lines in the file to initialize the array
    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n') // Increment count if this character is newline
            count++;
    }
    fclose(fp);
    job_count = count;
}

// input parsing================================================================
void parse_input(char *argv[], struct job jobs[job_count])
{
    // printf("job count: %d\n", job_count);
    ////////////////
    FILE *fp;
    char *str = (char *)malloc(100 * sizeof(char));
    char *error_str = (char *)malloc(100 * sizeof(char));

    fp = fopen(argv[2], "r");

    // parse each line into three-part line object
    for (int i = 0; i < job_count + 1; i++)
    {
        char *f_line = fgets(str, 200, fp);
        // printf("fgets: %s\n", f_line);
        char **line = (char **)calloc(3, sizeof(char *));
        for (int l = 0; l < 3; l++)
        {
            line[l] = (char *)calloc(30, sizeof(char));
        }

        // Separate line into 3 chunks
        int line_chunks = 0;
        for (int k = 0; k < strlen(str); k++)
        {
            // Check if too many inputs given
            if (isgraph(str[k]))
            {
                // Check if line is malformed, with too many inputs
                if (line_chunks > 2)
                {
                    snprintf(error_str, 100, "%s %s%s%d%s", "Malformed line", argv[2], "(", (i + 1), ")");
                    perror(error_str);
                    exit(1);
                }
                strncat(line[line_chunks], &str[k], 1);
            }
            // Increment the input on only the first whitespace after an entry
            if (k > 0 && isgraph(str[k - 1]) && !(isgraph(str[k])))
            {
                line_chunks++;
            }
        }

        // Check if too little inputs
        if (line_chunks < 2)
        {
            snprintf(error_str,
                     100,
                     "%s %s%s%d%s",
                     "Malformed line",
                     argv[2],
                     "(", (i + 1), ")");
            perror(error_str);
            exit(1);
        }

        // Check process name len
        if (strlen(line[0]) > 10)
        {
            snprintf(error_str,
                     100,
                     "%s %s%s%d%s",
                     "name more than 10 chars",
                     argv[2],
                     "(", (i + 1), ")");
            printf("name: %s", line[0]);
            perror(error_str);
            exit(1);
        }

        // Check runtime is positive
        if (atoi(line[1]) < 1)
        {
            snprintf(error_str,
                     100,
                     "%s %s%s%d%s",
                     "Malformed line",
                     argv[2],
                     "(", (i + 1), ")");

            fprintf(stderr, "%s\n", error_str);
            // perror(error_str);

            exit(1);
        }

        // Check 0 < probability < 1
        if (atoi(line[2]) > 1 || atoi(line[2]) < 0)
        {
            snprintf(error_str,
                     100,
                     "%s %s%s%d%s",
                     "probability < 0 or > 1",
                     argv[2],
                     "(", (i + 1), ")");
            perror(error_str);
            exit(1);
        }

        jobs[i] = *new_job(line[0], atoi(line[1]), atof(line[2]), 0, atoi(line[1]), NULL, NULL);
        // printf("job added: %s\n", jobs[i].name);
    }
    fclose(fp);

    // struct job * f;
    // f = head;

    // int job_num = 1;
    // while (f->next != NULL){
    // 	f= f->next;
    // 	printf("%d: %s %d %f \n", job_num, f->name, f->run_time, f->block_prob);
    // 	job_num++;
    // }
}
//============================================================================

int main(int argc, char *argv[])
{
    // initializing cpu i/o linked list
    

    // running the simulation

    // error checking
    if (argc < 3)
    {
        perror("Not enough arguments.");
        exit(1);
    }

    if ((strcmp(argv[1], "-f") == 0) || (strcmp(argv[1], "-r") == 0))
    {
        // record which algorithm to use for ready queue, from original input
        char *modeSelected;
        modeSelected = argv[1];
    }
    else
    {
        fprintf(stderr, "Usage: %s [-r | -f] file\n", argv[0]);
        // perror("Invalid flag entered");
        exit(1);
    }

    if (argc == 3)
    {

        // define jobs array
        process_count(argv[2]);

        struct job *jobs = malloc(job_count * sizeof(job)); // Leave space for a name to be allocated
        parse_input(argv, jobs);
    }

    // seed random num generator
    srandom(12345);

    // WHILE LOOP - each iteration is a tick
    //  each tick runs the ready queue once and the io queue once

    /* header line */
    printf("Processes:\n\n");
    printf("   name     CPU time  when done  cpu disp  i/o disp  i/o time\n");
    /* for process information */
    printf("%-10s %6d     %6d    %6d    %6d    %6d\n", "program1", 25, 75, 5, 10, 50);

    /* print clock time at end */
    printf("\nSystem:\n");
    printf("The wall clock time at which the simulation finished: %d\n", 75);

    /* print cpu statistics */
    printf("\nCPU:\n");
    printf("Total time spent busy: %d\n", 25);
    printf("Total time spent idle: %d\n", 50);
    printf("CPU utilization: %.2f\n", 0.31);
    printf("Number of dispatches: %d\n", 5);
    printf("Overall throughput: %.2f\n", 0.01);

    /* print i/o statistics */
    printf("\nI/O device:\n");
    printf("Total time spent busy: %d\n", 50);
    printf("Total time spent idle: %d\n", 25);
    printf("I/O utilization: %.2f\n", 0.66666);
    printf("Number of dispatches: %d\n", 10);
    printf("Overall throughput: %.2f\n", 0.05);

    exit(0);

    //============================================================================
}
