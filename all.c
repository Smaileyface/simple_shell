#include "shell.h"

/**
  * node_plus - Func that adds a node to a list.
  * @p: ptr addrs.
  * @t: node string field.
  * @n: hst index.
  *
  * Return: lst size.
 */

list_t *node_plus(list_t **p, const char *t, int n)
{
	list_t *nh;

	if (!p)
		return (NULL);
	nh = malloc(sizeof(list_t));
	if (!nh)
		return (NULL);
	mem_fill((void *)nh, 0, sizeof(list_t));
	nh->num = n;
	if (t)
	{
		nh->str = duplstr(t);
		if (!nh->str)
		{
			free(nh);
			return (NULL);
		}
	}
	nh->next = *p;
	*p = nh;
	return (nh);
}

/**
  * end_node - new node added @ the end.
  * @p: ptr addrss.
  * @t: node field.
  * @n: index of the node.
  *
  * Return: lst size.
  */

list_t *end_node(list_t **p, const char *t, int n)
{
	list_t *nn;
	list_t *o;

	if (!p)
		return (NULL);
	o = *p;
	nn = malloc(sizeof(list_t));
	if (!nn)
		return (NULL);
	mem_fill((void *)nn, 0, sizeof(list_t));
	nn->num = n;
	if (t)
	{
		nn->str = duplstr(t);
		if (!nn->str)
		{
			free(nn);
			return (NULL);
		}
	}
	if (o)
	{
		while (o->next)
			o = o->next;
		o->next = nn;
	}
	else
		*p = nn;
	return (nn);
}

/**
  * str_show - prints the strg of list_t lnkd lst.
  * @p: 1st node ptr
  *
  * Return: lst.sz
  */

size_t str_show(const list_t *p)
{
	size_t j;

	j = 0;
	while (p)
	{
		prnts(p->str ? p->str : "(nil)");
		prnts("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
  * rm_node - rm node @given indx.
  * @p: 1st node.
  * @x: node to remove.
  *
  * Return: (1) => rmvd || (0) => fail.
  */
int rm_node(list_t **p, unsigned int x)
{
	unsigned int j;
	list_t *o;
	list_t *po;

	j = 0;
	if (!p || !*p)
		return (0);
	if (!x)
	{
		o = *p;
		*p = (*p)->next;
		free(o->str);
		free(o);
		return (1);
	}
	o = *p;
	while (o)
	{
		if (j == x)
		{
			po->next = o->next;
			free(o->str);
			free(o);
			return (1);
		}
		j++;
		po = o;
		o = o->next;
	}
	return (0);
}

/**
  * rls_node - frees all list nodes
  * @p: head ptr.
  *
  * Return: Nothing.
  */
void rls_node(list_t **p)
{
	list_t *o, *nn, *hd;

	if (!p || !*p)
		return;
	hd = *p;
	o = hd;
	while (o)
	{
		nn = o->next;
		free(o->str);
		free(o);
		o = nn;
	}
	*p = NULL;
}
