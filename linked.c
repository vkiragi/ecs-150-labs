#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int file_exists(const char *file)
{
    struct stat x;
    int exists = stat(file, &x);
    if (!exists)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{

    // file_x -> file x imported with stat()
    // file_xL -> file x important with lstat()

    // Checking if files exist
    if (!file_exists(argv[1]))
    {
        perror(argv[1]);
        exit(1);
    }
    if (!file_exists(argv[2]))
    {
        perror(argv[2]);
        exit(1);
    }

    int end_string1;
    int end_string2;

    char *symbolic_file1 = malloc((1000) * sizeof(char));
    char *symbolic_file2 = malloc((1000) * sizeof(char));

    struct stat file_1;
    int a;
    a = stat(argv[1], &file_1);

    struct stat file_2;
    int b;
    b = stat(argv[2], &file_2);

    struct stat file_1L;
    int x;
    x = lstat(argv[1], &file_1L);

    struct stat file_2L;
    int y;
    y = lstat(argv[2], &file_2L);

    if (x < 0 || y < 0 || a < 0 || b < 0)
    {
        perror("Failed to get file stat");
    }

    // Are files linked?
    if (file_1.st_ino == file_2.st_ino)
    {
        // if both are symlink or hard link
        if ((S_ISREG(file_1L.st_mode) && S_ISREG(file_2L.st_mode)) ||
            (S_ISLNK(file_1L.st_mode) && S_ISLNK(file_2L.st_mode)))
        {
            printf("These files are linked.\n");
        }
        // if one is symlink and other is hard link
        else if (((S_ISLNK(file_1L.st_mode) && S_ISREG(file_2L.st_mode)) ||
                  (S_ISLNK(file_2L.st_mode) && S_ISREG(file_1L.st_mode))))
        {
            end_string1 = readlink(argv[1], symbolic_file1, 100);
            symbolic_file1[end_string1] = 0;
            if (strcmp(symbolic_file1, argv[2]) == 0)
            {
                printf("%s is a symbolic link to %s\n", argv[1], argv[2]);
            }
            else
            {
                printf("These files are linked.\n");
            }
        }
    }
    else if (file_1.st_ino != file_2.st_ino)
    {
        printf("These files are not linked.\n");
    }
    else
    {
        return 0;
    }

    return 0;
}