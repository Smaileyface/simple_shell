#include "shell.h"

/**
  * copy_strng - func that cp given strng.
  *@dst: Destintion of cp'd string
  *@sr: Where.from
  *@m: no of char to be cp'd
  *
  *Return: (conctentd str)
  */
char *copy_strng(char *dst, char *sr, int m)
{
	int j, k;
	char *ch = dst;

	j = 0;
	while (sr[j] != '\0' && j < m - 1)
	{
		dst[j] = sr[j];
		j++;
	}
	if (j < m)
	{
		k = j;
		while (k < m)
		{
			dst[k] = '\0';
			k++;
		}
	}
	return (ch);
}

/**
  * concat_strng - func that cocatenates 2 strngs
  * @frs: 1st str
  * @scn: 2nd str
  * @m: no of bytes to be.used
  *
  * Return: conct'ed str
  */
char *concat_strng(char *frs, char *scn, int m)
{
	int a = 0;
	int b = 0;
	char *ch = frs;

	while (frs[a] != '\0')
		a++;
	while (scn[b] != '\0' && b < m)
	{
		frs[a] = scn[b];
		a++;
		b++;
	}
	if (b < m)
		frs[a] = '\0';
	return (ch);
}

/**
  * locate_char - Finds a char in a str
  * @str: e' str
  * @tx: char being searched.
  *
  * Return: pntr to mem area.
  */
char *locate_char(char *str, char tx)
{
	do {
		if (*str == tx)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
