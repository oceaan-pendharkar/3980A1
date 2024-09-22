#include "../include/args.h"
#include "../include/settings.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int usage(const char *message, const char *fileName)
{
    if(message)
    {
        fprintf(stderr, "%s", message);
    }
    fprintf(stderr, "Usage: %s [-i <input file name>] [-o <output file name>] [-f <filter>]\n", fileName);
    fprintf(stderr, "filter options: upper, lower, or null/empty\n");
    return -1;
}

int parse_arguments(int argc, char *const *arguments, Settings *settings)
{
    const char *arg1 = "-i";
    const char *arg2 = "-o";
    // cppcheck-suppress variableScope
    const char *upper = "upper";
    // cppcheck-suppress variableScope
    const char *lower = "lower";
    if((arguments[1] != (void *)0 && strcmp(arguments[1], arg1) == 0) && (arguments[3] != (void *)0 && strcmp(arguments[3], arg2) == 0))
    {
        int opt;
        while((opt = getopt(argc, arguments, "i:o:f:")) != -1)
        {
            switch(opt)
            {
                case 'i':
                    if(strstr(optarg, ".txt") != NULL)
                    {
                        settings->input_file = optarg;
                    }
                    else
                    {
                        return usage("Your input and output files must be .txt files\n", arguments[0]);
                    }
                    break;
                case 'o':
                    if(strstr(optarg, ".txt") != NULL)
                    {
                        settings->output_file = optarg;
                    }
                    else
                    {
                        return usage("Your input and output files must be .txt files\n", arguments[0]);
                    }
                    break;
                case 'f':
                    if((optarg != (void *)0 && strcmp(optarg, upper) == 0) || (optarg != (void *)0 && strcmp(optarg, lower) == 0))
                    {
                        settings->filter_type = optarg;
                    }
                    else
                    {
                        return usage("Your filter value can only be 'upper' or 'lower'.\n", arguments[0]);
                    }
                    break;
                default:
                    return usage(NULL, arguments[0]);
            }
        }
    }
    else
    {
        return usage("You must provide an input file and output file.\n", arguments[0]);
    }
    return 0;
}

int open_file(const char *fileName, int flags, Settings *settings)
{
    int fd;
    fd = open(fileName, flags | O_CLOEXEC, S_IRUSR | S_IWUSR);
    if(fd == -1)
    {
        if(flags == O_RDONLY)
        {
            perror("open_file input file");
        }
        else
        {
            perror("open_file output file");
        }
    }
    if(flags == (O_CREAT | O_RDONLY))
    {
        settings->input_file_descriptor = fd;
    }
    else
    {
        settings->output_file_descriptor = fd;
    }
    return fd;
}

int close_file(const int file_descriptor)
{
    if(close(file_descriptor) < 0)
    {
        perror("close_file");
        return -1;
    }
    return 0;
}
