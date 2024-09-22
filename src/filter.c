#include "../include/filter.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char read_char(const int file_descriptor, int *err)
{
    char    buffer[2];
    ssize_t bytes_read = read(file_descriptor, buffer, 1);
    if(bytes_read == -1)
    {
        *err = errno;
        return -1;
    }
    buffer[bytes_read] = '\0';
    return buffer[0];
}

int write_char(const int file_descriptor, int *err, char character)
{
    char    buffer[2];
    ssize_t bytes_written;

    buffer[0]     = character;
    bytes_written = write(file_descriptor, buffer, 1);

    if(bytes_written == -1)
    {
        *err = errno;
        return -1;
    }
    return 0;
}

char filter(const char *filter_type, const char character)
{
    if(filter_type == NULL)
    {
        return character;
    }
    switch(*filter_type)
    {
        case('u'):
        {
            if(strcmp(filter_type, "upper") == 0)
            {
                return (char)toupper(character);
            }
            break;
        }
        case('l'):
        {
            if(strcmp(filter_type, "lower") == 0)
            {
                return (char)tolower(character);
            }
            break;
        }
        default:
            return character;
    }
    return character;
}

int filter_file(const int input_fd, const int output_fd, int *err, const char *filter_type)
{
    char character = 1;
    // cppcheck-suppress variableScope
    char filteredCharacter;
    // cppcheck-suppress variableScope
    int write;
    while((character != '\0'))
    {
        character = read_char(input_fd, err);
        if(character == -1)
        {
            return -1;
        }
        filteredCharacter = filter(filter_type, character);
        write             = write_char(output_fd, err, filteredCharacter);
        if(write == -1)
        {
            return -1;
        }
    }
    return 0;
}
