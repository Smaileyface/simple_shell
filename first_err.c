#include "shell.h"
/**
  * strtoint - change string to int.
  * @tx: Str to convert.
  *
  * Return: (0) => no numb in str else (-1)
  */
int strtoint(char *tx)
{
	unsigned long int total;
	int j;

	j = 0;
	total = 0;
	if (*tx == '+')
		tx++;
	for (j = 0;  tx[j] != '\0'; j++)
	{
		if (tx[j] >= '0' && tx[j] <= '9')
		{
			total *= 10;
			total += (tx[j] - '0');
			if (total > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (total);
}
/**
  * show_error - prnts err msgs.
  * @alc: param && return info struct.
  * @tx: err type description
  *
  * Return: (0) => no numb in string/ converted else (-1) => if any  error.
  */
void show_error(info_t *alc, char *tx)
{
	put_str(alc->fname);
	put_str(": ");
	prnt_dec(alc->line_count, STDERR_FILENO);
	put_str(": ");
	put_str(alc->argv[0]);
	put_str(": ");
	put_str(tx);
}

/**
  * prnt_dec - prints decimal no
  * @i: input
  * @fl: file to write to (file descriptor).
  *
  * Return: no of printed characters
  */
int prnt_dec(int i, int fl)
{
	int (*__putchar)(char) = wrt_char;
	int j;
	int c = 0;
	unsigned int ab, now;

	if (fl == STDERR_FILENO)
		__putchar = write_c;
	if (i < 0)
	{
		ab = -i;
		__putchar('-');
		c++;
	}
	else
		ab = i;
	now = ab;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (ab / j)
		{
			__putchar('0' + now / j);
			c++;
		}
		now %= j;
	}
	__putchar('0' + now);
	c++;
	return (c);
}

/**
  * num_convert - itoa (clone)
  * @no: number parameter.
  * @b: ^base
  * @fl: arg flags
  *
  * Return: a strng
  */
char *num_convert(long int no, int b, int fl)
{
	static char *arr, bufer[50];
	char val = 0;
	unsigned long m = no;
	char *p;

	if (!(fl & CONVERT_UNSIGNED) && no < 0)
	{
		m = -no;
		val = '-';
	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &bufer[49];
	*p = '\0';
	do {
		*--p = arr[m % b];
		m /= b;
	} while (m != 0);
	if (val)
		*--p = val;
	return (p);
}
/**
 * rm_cmnt - swap  '#' for  '\0'
 * @ch: modified str
 *
 * Return: (0);
 */
void rm_cmnt(char *ch)
{
	int j;

	for (j = 0; ch[j] != '\0'; j++)
		if (ch[j] == '#' && (!j || ch[j - 1] == ' '))
		{
			ch[j] = '\0';
			break;
		}
}
