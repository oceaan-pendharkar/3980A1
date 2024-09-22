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

char upper_filter(char character)
{
    return (char)toupper(character);
}

char lower_filter(char character)
{
    return (char)tolower(character);
}

char null_filter(char character)
{
    return character;
}

int filter_file(const int input_fd, const int output_fd, int *err, filter_func filter)
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
        filteredCharacter = filter(character);
        write             = write_char(output_fd, err, filteredCharacter);
        if(write == -1)
        {
            return -1;
        }
    }
    return 0;
}
