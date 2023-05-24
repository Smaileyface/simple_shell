#include "shell.h"
/**
  * shell_mode - checks if shell is interactive mode return (true)
  * @addr: The struct address.
  *
  * Return: if interactive mode (1) else return (0)
  */
int shell_mode(info_t *addr)
{
	return (isatty(STDIN_FILENO) && addr->readfd <= 2);
}
/**
  * delimeter - finds if character is a delimeter
  * @ch: char to be checked
  * @del: the delimeter string
  * Return: 1 if true return (1) else (0).
  */
int delimeter(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}
/**
  * alpha_char - checks for alphabetic character
  * @ch: The character to input
  *
  * Return: Return (1) if character is alphabetic else return (0).
  */
int alpha_char(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}
/**
  * a_toi - Function that converts a string to an integer value.
  * @st: String to be converted to an int.
  *
  * Return: return 0if there is no numb in the string. Else convert to number
  */
int a_toi(char *st)
{
	int j;
	int sgn = 1;
	int flg = 0, outpt;
	unsigned int total = 0;

	for (j = 0; st[j] != '\0' && flg != 2; j++)
	{
		if (st[j] == '-')
			sgn *= -1;
		if (st[j] >= '0' && st[j] <= '9')
		{
			flg = 1;
			total *= 10;
			total += (st[j] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}
	if (sgn == -1)
		outpt = -total;
	else
		outpt = total;
	return (outpt);
}
