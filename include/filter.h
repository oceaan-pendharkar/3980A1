//
// Created by op on 14/09/2024
//

#ifndef FILTER_H
#define FILTER_H

typedef char (*filter_func)(char);

int filter_file(int input_fd, int output_fd, int *err, filter_func filter);

int filter_error(const char *message);

char read_char(int file_descriptor, int *err);

int write_char(int file_descriptor, int *err, char character);

char upper_filter(char character);

char lower_filter(char character);

char null_filter(char character);

#endif    // FILTER_H
