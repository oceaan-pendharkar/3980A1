//
// Created by op on 14/09/2024
//

#ifndef FILTER_H
#define FILTER_H

int filter_file(int input_fd, int output_fd, int *err, const char *filter_type);

int filter_error(const char *message);

char read_char(int file_descriptor, int *err);

int write_char(int file_descriptor, int *err, char character);

char filter(const char *filter_type, char character);

#endif    // FILTER_H
