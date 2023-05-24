#include "shell.h"
/**
  * put_str - func that prnts input str
  * @txt: Strg to prnt
  *
  * Return: (0)
  */
void put_str(char *txt)
{
	int j = 0;

	if (!txt)
		return;
	while (txt[j] != '\0')
	{
		write_c(txt[j]);
		j++;
	}
}

/**
  * write_c - func that wrts 'c' to std-err
  * @tx: Char to print
  *
  * Return: (1) => Sucess || (-1) => Fail.
  */
int write_c(char tx)
{
	static int j;
	static char bf[WRITE_BUF_SIZE];

	if (tx == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, bf, j);
		j = 0;
	}
	if (tx != BUF_FLUSH)
		bf[j++] = tx;
	return (1);
}

/**
  * write_fd - prnt 'c' to given fd
  * @tx: The char to be  printed
  * @descr: Fil descr to write to
  *
  * Return: (1) => success || (-1) Fail.
  */
int write_fd(char tx, int descr)
{
	static int j;
	static char bf[WRITE_BUF_SIZE];

	if (tx == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(descr, bf, j);
		j = 0;
	}
	if (tx != BUF_FLUSH)
		bf[j++] = tx;
	return (1);
}

/**
  * print_i - wites an inpt strng
  * @tx: Printed string.
  * @descr: Fille.Descriptor to be written on
  *
  * Return: (char numbers).
  */
int print_i(char *tx, int descr)
{
	int j = 0;

	if (!tx)
		return (0);
	while (*tx)
	{
		j += write_fd(*tx++, descr);
	}
	return (j);
}
