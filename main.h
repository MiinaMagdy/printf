#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int isdigit(int ch);
int isalpha(int ch);
int write_int(int d, char ch);
int percentage_handler(const char *frmt, va_list ap);
int _printf(const char *format, ...);

#endif
