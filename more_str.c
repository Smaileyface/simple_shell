#include "shell.h"

/**
  * str_len - rtns string length.
  * @t: The str.
  *
  * Return: length of string
  */

int str_len(char *t)
{
	int j;

	j = 0;
	if (!t)
		return (0);
	while (*t++)
		j++;
	return (j);
}

/**
  * comp_str - compares 2 strangs.
  * @t: 1st strang
  * @t2: 2nd strang
  *
  * Return: (-ve) ? t < t2 || (+ve) ? t > t2 || (0) ? t == t2
 */
int comp_str(char *t, char *t2)
{
	while (*t && *t2)
	{
		if (*t != *t2)
			return (*t - *t2);
		t++;
		t2++;
	}
	if (*t == *t2)
		return (0);
	else
		return (*t < *t2 ? -1 : 1);
}

/**
  * begins - begins with hay.stack.
  * @str: str to srch
  * @ee: sub-str to find.
  *
  * Return: nxt char addrss.
  */

char *begins(const char *str, const char *ee)
{
	while (*ee)
		if (*ee++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * str_concat - 2 strs conctes
 * @to: destination.
 * @from: source.
 *
 * Return: destntion ptr
 */
char *str_concat(char *to, char *from)
{
	char *s = to;

	while (*to)
		to++;
	while (*from)
		*to++ = *from++;
	*to = *from;
	return (s);
}
