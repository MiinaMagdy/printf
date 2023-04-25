#include <stdarg.h>
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
 * _printf - prints formatted output to stdout
 *
 * @frmt: format string
 * @...: variable arguments list
 *
 * Return: number of characters printed
 */
int _printf(const char *frmt, ...)
{
	int cnt = 0;
	int prv_percent = 0;
	char *s, c;
	va_list ap;

	va_start(ap, frmt);
	while (*frmt)
	{
        if (prv_percent)
        {
            if (isalpha(*frmt))
            {
                switch (*frmt)
				{
				case 's':
					s = va_arg(ap, char *);
					cnt += write(1, s, strlen(s));
					break;
				case 'c':
					c = (char)va_arg(ap, int);
					cnt += write(1, &c, 1);
					break;
				}
            }
            else if (*frmt == '%')
                cnt += write(1, "%%", 1);
            prv_percent = 0;
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
