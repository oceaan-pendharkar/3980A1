#include "../include/args.h"
#include "../include/filter.h"
#include "../include/settings.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *const *arguments)
{
    Settings settings;
    int      check_exit;
    settings.input_file             = NULL;
    settings.output_file            = NULL;
    settings.filter_type            = NULL;
    settings.input_file_descriptor  = -2;
    settings.output_file_descriptor = -2;

    check_exit = parse_arguments(argc, arguments, &settings);
    if(check_exit == -1)
    {
        printf("Returned -1\n");
        return EXIT_FAILURE;
    }
    settings.input_file_descriptor  = open_file(settings.input_file, O_RDONLY, &settings);
    settings.output_file_descriptor = open_file(settings.output_file, O_CREAT | O_RDWR | O_TRUNC, &settings);
    if(settings.input_file_descriptor == -1 || settings.output_file_descriptor == -1)
    {
        return EXIT_FAILURE;
    }
    check_exit = filter_file(settings.input_file_descriptor, settings.output_file_descriptor, &errno, settings.filter_type);
    if(check_exit == -1)
    {
        return EXIT_FAILURE;
    }
    check_exit = close_file(settings.input_file_descriptor);
    if(check_exit == -1)
    {
        return EXIT_FAILURE;
    }
    check_exit = close_file(settings.output_file_descriptor);
    if(check_exit == -1)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
