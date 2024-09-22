//
// Created by op on 14/09/2024
//

#ifndef FILEIO_H
#define FILEIO_H

typedef struct
{
    // cppcheck-suppress unusedStructMember
    char *input_file;
    // cppcheck-suppress unusedStructMember
    char *output_file;
    // cppcheck-suppress unusedStructMember
    char *filter_type;
    // cppcheck-suppress unusedStructMember
    int input_file_descriptor;
    // cppcheck-suppress unusedStructMember
    int output_file_descriptor;
} Settings;

#endif    // FILEIO_H
