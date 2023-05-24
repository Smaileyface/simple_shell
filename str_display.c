#include "shell.h"

/**
  * cpstrng - cp a strng
  * @to: destination
  * @from: string src
  *
  * Return: Desination ptr.
  */

char *cpstrng(char *to, char *from)
{
	int j;

	j = 0;
	if (to == from || from == 0)
		return (to);
	while (from[j])
	{
		to[j] = from[j];
		j++;
	}
	to[j] = 0;
	return (to);
}

/**
  * duplstr - function that duplicates a string.
  * @tx: Str do dplicate.
  *
  * Return: dplc str pointer.
  */

char *duplstr(const char *tx)
{
	char *s;
	int n;

	n = 0;
	if (tx == NULL)
		return (NULL);
	while (*tx++)
		n++;
	s = malloc(sizeof(char) * (n + 1));
	if (!s)
		return (NULL);
	for (n++; n--;)
		s[n] = *--tx;
	return (s);
}

/**
  * prnts - prints a string
  * @tx: To be prnted str
  *
  * Return: Null
 */
void prnts(char *tx)
{
	int j;

	j = 0;
	if (!tx)
		return;
	while (tx[j] != '\0')
	{
		wrt_char(tx[j]);
		j++;
	}
}

/**
  * wrt_char - prnts char to stdout.
  * @a: Char to be printed
  *
  * Return: (1) => Sucess || (-1) => error.
  */
int wrt_char(char a)
{
	static char u[WRITE_BUF_SIZE];
	static int j;

	if (a == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, u, j);
		j = 0;
	}
	if (a != BUF_FLUSH)
		u[j++] = a;
	return (1);
}
