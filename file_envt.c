#include "shell.h"
/**
  * shw_envt - returns str arr cpy e' envt
  * @alc: Args.
  *
  * Return: (0)
  */

char **shw_envt(info_t *alc)
{
	if (!alc->environ || alc->env_changed)
	{
		alc->environ = strg_arry(alc->env);
		alc->env_changed = 0;
	}
	return (alc->environ);
}
/**
  * envt_unset - rm envt var
  * @alc: Arg.
  * @ch: char val
  *
  * Return: (1) on delete || (0).
  */
int envt_unset(info_t *alc, char *ch)
{
	size_t j = 0;
	list_t *o = alc->env;
	char *q;

	if (!o || !ch)
		return (0);
	while (o)
	{
		q = begins(o->str, ch);
		if (q && *q == '=')
		{
			alc->env_changed = rm_node(&(alc->env), j);
			j = 0;
			o = alc->env;
			continue;
		}
		o = o->next;
		j++;
	}
	return (alc->env_changed);
}
/**
  * init_envt - func that inits  new.envt var || modfy existing 1.
  * @alc: Arg.
  * @stri: The string.
  * @v: new envt value
  *
  * Return: (0).
  */
int init_envt(info_t *alc, char *stri, char *v)
{
	char *ch;
	char *uf = NULL;
	list_t *o;

	if (!stri || !v)
		return (0);
	uf = malloc(str_len(stri) + str_len(v) + 2);
	if (!uf)
		return (1);
	cpstrng(uf, stri);
	str_concat(uf, "=");
	str_concat(uf, v);
	o = alc->env;
	while (o)
	{
		ch = begins(o->str, stri);
		if (ch && *ch == '=')
		{
			free(o->str);
			o->str = uf;
			alc->env_changed = 1;
			return (0);
		}
		o = o->next;
	}
	end_node(&(alc->env), uf, 0);
	free(uf);
	alc->env_changed = 1;
	return (0);
}
