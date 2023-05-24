#include "shell.h"

/**
  * splt_str - String is splited into words.
  * @tr: str input
  * @ch: delim str
  *
  * Return: ptr to arr of strngs.
  */

char **splt_str(char *tr, char *ch)
{
	char **t;
	int a, b, c, n;
	int wds = 0;

	if (tr == NULL || tr[0] == 0)
		return (NULL);
	if (!ch)
		ch = " ";
	for (a = 0; tr[a] != '\0'; a++)
		if (!delimeter(tr[a], ch) && (delimeter(tr[a + 1], ch) || !tr[a + 1]))
			wds++;

	if (wds == 0)
		return (NULL);
	t = malloc((1 + wds) * sizeof(char *));
	if (!t)
		return (NULL);
	for (a = 0, b = 0; b < wds; b++)
	{
		while (delimeter(tr[a], ch))
			a++;
		c = 0;
		while (!delimeter(tr[a + c], ch) && tr[a + c])
			c++;
		t[b] = malloc((c + 1) * sizeof(char));
		if (!t[b])
		{
			for (c = 0; c < b; c++)
				free(t[c]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			t[b][n] = tr[a++];
		t[b][n] = 0;
	}
	t[b] = NULL;
	return (t);
}

/**
  * split_str - Strng split => words
  *
  * @tr: String input.
  * @ch: Delim.
  *
  * Return: Ptr to string.
  */
char **split_str(char *tr, char ch)
{
	char **t;
	int a, b, c, n;
	int wds = 0;

	if (tr == NULL || tr[0] == 0)
		return (NULL);
	for (a = 0; tr[a] != '\0'; a++)
		if ((tr[a] != ch && tr[a + 1] == ch) ||
				    (tr[a] != ch && !tr[a + 1]) || tr[a + 1] == ch)
			wds++;
	if (wds == 0)
		return (NULL);
	t = malloc((1 + wds) * sizeof(char *));
	if (!t)
		return (NULL);
	for (a = 0, b = 0; b < wds; b++)
	{
		while (tr[a] == ch && tr[a] != ch)
			a++;
		c = 0;
		while (tr[a + c] != ch && tr[a + c] && tr[a + c] != ch)
			c++;
		t[b] = malloc((c + 1) * sizeof(char));
		if (!t[b])
		{
			for (c = 0; c < b; c++)
				free(t[c]);
			free(t);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			t[b][n] = tr[a++];
		t[b][n] = 0;
	}
	t[b] = NULL;
	return (t);
}
