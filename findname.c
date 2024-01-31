#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include <libgen.h>
#include <unistd.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>

#define check_error(cond, msg)  \
    do{ \
        if(!(cond)){    \
            perror(msg);    \
            exit(EXIT_FAILURE); \
        }   \
    } while(0)  \

regex_t regex;
bool delete = false, inverse = false;
int process_file(char* fpath, const struct stat* sb, int typeflag)
{
    if (typeflag == FTW_D)  return 0; //continue

    int regexret = regexec(&regex, basename(fpath), 0, NULL, 0);
    if ((regexret == 0 && inverse == false) || (regexret == REG_NOMATCH && inverse == true))
    {
        if (delete == false)    puts(fpath);
        else
        {
            printf("Remove %s? [y/n] ", fpath);
            char choice = getchar(); getchar();
            if (choice == 'y')  unlink(fpath);
        }
    }

    return 0;
}

int main(int argc, char** argv)
{
    check_error(argc > 1, "Please read README for help with using the command.");

    int location = -1;
    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0) inverse = true;
        else if (strcmp(argv[i], "-d") == 0)    delete = true;
        else if (strcmp(argv[i], "-l") == 0)
        {
            location = (i + 1);
            check_error(argc > location, "Please specify the path when using -l");
            i++;
        }
    }

    check_error(regcomp(&regex, argv[1], 0) == 0, "regcomp");

    char* path = (location == -1) ? "." : argv[location];
    
    check_error(ftw(path, process_file, 20) == 0, "ftw");

    regfree(&regex);
    return 0;
}
