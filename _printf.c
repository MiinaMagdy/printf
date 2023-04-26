#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

/**
 * isalpha - checks whether a character is an alphabet
 *
 * @ch: character to check
 *
 * Return: 1 if @ch is an alphabet, 0 otherwise
 */
int isalpha(int ch)
{
	if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
		return (1);
	return (0);
}

/**
 * isdigit - checks whether a character is a digit
 *
 * @ch: character to check
 *
 * Return: 1 if @ch is a digit, 0 otherwise
 */
int isdigit(int ch)
{
	if ('0' <= ch && ch <= '9')
		return (1);
	return (0);
}

/**
 * write_int - write integer
 *
 * @d: the integer
 *
 * Return: the cnt of chars printed
 */
int write_int(int d, char ch)
{
	char c[30];
	char sf[3];
	sf[0] = '%', sf[1] = ch, sf[2] = '\0';
	sprintf(c, sf, d);
	return (write(1, c, strlen(c)));
}

/**
 * percentage_handler - handles if the prviouse is percentage char
 *
 * @frmt: the formated string
 * @ap: variable list
 *
 * Return: the cnt of chars printed
 */
int percentage_handler(const char *frmt, va_list ap)
{
	char *s, c;
	int cnt = 0, d;

	if (isalpha(*frmt))
	{
		switch (*frmt)
		{
			case 's':
				s = va_arg(ap, char *);
				if (s == NULL)
					s = "(null)";
				cnt += write(1, s, strlen(s));
				break;
			case 'c':
				c = (char)va_arg(ap, int);
				cnt += write(1, &c, 1);
				break;
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
			case 'b':
				d = va_arg(ap, int);
				cnt += write_int(d, *frmt);
				break;
			default:
				cnt += write(1, "%%", 1), cnt += write(1, frmt, 1);
		}
	}
	else if (*frmt == '%')
		cnt += write(1, "%%", 1);
	else
		cnt += write(1, "%%", 1), cnt += write(1, frmt, 1);
	return (cnt);
}

/**
 * _printf - prints formatted output to stdout
 *
 * @frmt: format string
 * @...: variable arguments list
 *
 * Return: number of characters printed
 */
int _printf(const char *frmt, ...)
{
	va_list ap;
	int cnt = 0, prv_percent = 0;

	if (frmt == NULL)
		return (-1);
	va_start(ap, frmt);
	while (frmt && *frmt)
	{
		if (prv_percent)
		{
			if (*frmt != ' ')
			{
				cnt += percentage_handler(frmt, ap);
				prv_percent = 0;
			}
		}
		else
		{
			if (*frmt == '%')
				prv_percent = 1;
			else
				cnt += write(1, frmt, 1);
		}
		frmt++;
	}
	va_end(ap);
	return (cnt);
}
