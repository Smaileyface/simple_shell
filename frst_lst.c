#include "shell.h"

/**
  * lst_sz - funct that checks length of lst.
  * @pt: node pointer.
  *
  * Return: list length.
 */

size_t lst_sz(const list_t *pt)
{
	size_t j;

	j = 0;
	while (pt)
	{
		pt = pt->next;
		j++;
	}
	return (j);
}

/**
  * strg_arry - Returns string array.
  * @n: 1st node.
  *
  * Return: String arrays.
  */

char **strg_arry(list_t *n)
{
	char *ch;
	char **tx;
	list_t *o = n;
	size_t a = lst_sz(n);
	size_t b;

	if (!n || !a)
		return (NULL);
	tx = malloc(sizeof(char *) * (a + 1));
	if (!tx)
		return (NULL);
	for (a = 0; o; o = o->next, a++)
	{
		ch = malloc(str_len(o->str) + 1);
		if (!ch)
		{
			for (b = 0; b < a; b++)
				free(tx[b]);
			free(tx);
			return (NULL);
		}

		ch = cpstrng(ch, o->str);
		tx[a] = ch;
	}
	tx[a] = NULL;
	return (tx);
}


/**
  * show_lst - prnts list-t elements.
  * @p: 1st node
  *
  * Return: Lst.size
  *
  */

size_t show_lst(const list_t *p)
{
	size_t j;

	j = 0;
	while (p)
	{
		prnts(num_convert(p->num, 10, 0));
		wrt_char(':');
		wrt_char(' ');
		prnts(p->str ? p->str : "(nil)");
		prnts("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
  * start_nd - start node return
  * @o: lst.head
  * @fx: String
  * @d: following chr.
  *
  * Return: The matching node || null if non.
  */
list_t *start_nd(list_t *o, char *fx, char d)
{
	char *ch = NULL;

	while (o)
	{
		ch = begins(o->str, fx);
		if (ch && ((d == -1) || (*ch == d)))
			return (o);
		o = o->next;
	}
	return (NULL);
}

/**
  * nd_indx - finds a node's index.
  * @p: lst.head ptr.
  * @o: nd ptr.
  *
  * Return: node's indx
  */
ssize_t nd_indx(list_t *p, list_t *o)
{
	size_t j;

	j = 0;
	while (p)
	{
		if (p == o)
			return (j);
		p = p->next;
		j++;
	}
	return (-1);
}
