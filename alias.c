#include "shell.h"
/**
  * history - shows a list of history, 1 cmd by line then line numbs from 0
  * @hst: Potential args used in maintaining const func prototype.
  *  Return: (0).
  */
int history(info_t *hst)
{
	show_lst(hst->history);
	return (0);
}
/**
  * alias_set - function that(sets) alias to strng
  * @als: param struct
  * @st: string ally
  *
  * Return: (0) if success (1) if error found
  */
int alias_set(info_t *als, char *st)
{
	char *chr, ch;
	int t;

	chr = locate_char(st, '=');
	if (!chr)
	{
		return (1);
	}
	ch = *chr;
	*chr = 0;
	t = rm_node(&(als->alias),
		nd_indx(als->alias, start_nd(als->alias, st, -1)));
	*chr = ch;
	return (t);
}

/**
 * _setalias - function that se.ts alias => string
 * @als: param struct
 * @chr: string.alias
 *
 * Return: (0) => success || (1) => error.
 */
int _setalias(info_t *als, char *chr)
{
	char *n;

	n = locate_char(chr, '=');
	if (!n)
	{
		return (1);
	}
	if (!*++n)
	{
		return (alias_set(als, chr));
	}
	alias_set(als, chr);
	return (end_node(&(als->alias), chr, 0) == NULL);
}

/**
 * alias_view - function which prints alias string.
 * @nd: nodes
 *
 * Return: (0) => success || (1) => error.
 */
int alias_view(list_t *nd)
{
	char *ch = NULL;
	char *nch = NULL;

	if (nd)
	{
		ch = locate_char(nd->str, '=');
		for (nch = nd->str; nch <= ch; nch++)
		{
			wrt_char(*nch);
			wrt_char('\'');
			prnts(ch + 1);
			prnts("'\n");
			return (0);
		}
	}
	return (1);
}

/**
 * my_alias - act as build in {man alias}.
 * @als: Args that maintain func pr0t0type
 *  Return: (0)
 */
int my_alias(info_t *als)
{
	char *ch = NULL;
	int j = 0;
	list_t *nd = NULL;

	if (als->argc == 1)
	{
		nd = als->alias;
		while (nd)
		{
			alias_view(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (j = 1; als->argv[j]; j++)
	{
		ch = locate_char(als->argv[j], '=');
		if (ch)
		{
			_setalias(als, als->argv[j]);
		}
		else
			alias_view(start_nd(als->alias, als->argv[j], '='));
	}

	return (0);
}
