//
// Created by op on 14/09/2024.
//

#ifndef ARGS_H
#define ARGS_H
#include "../include/settings.h"

int parse_arguments(int argc, char *const *arguments, Settings *settings);

int usage(const char *message, const char *fileName);

int open_file(const char *fileName, int flags, Settings *settings);

int close_file(int file_descriptor);

#endif    // ARGS_H
