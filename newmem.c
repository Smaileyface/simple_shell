#include "shell.h"

/**
  * mem_fill - with const byte.
  * @t: mem area ptr.
  * @c: to be filled byte.
  * @m: no of bytes to be filled.
  *
  * Return: ptr to mem area.
  */

char *mem_fill(char *t, char c, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		t[j] = c;
	return (t);
}

/**
  * sfree - str of str is freed.
  * @st: str
  *
  * Return: Nothing.
  */
void sfree(char **st)
{
	char **chr = st;

	if (!st)
		return;
	while (*st)
		free(*st++);
	free(chr);
}

/**
  * real_mem - realocates mem.
  * @t: ptr to prev malloc.bloc
  * @o: prev block byt sz
  * @n: new block byte size.
  *
  * Return: ptr to mem.
  */
void *real_mem(void *t, unsigned int o, unsigned int n)
{
	char *q;

	if (!t)
		return (malloc(n));
	if (!n)
		return (free(t), NULL);
	if (n == o)
		return (t);
	q = malloc(n);
	if (!q)
		return (NULL);

	o = o < n ? o : n;
	while (o--)
		q[o] = ((char *)t)[o];
	free(t);
	return (q);
}
