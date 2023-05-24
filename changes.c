#include "shell.h"

/**
  * chain_test - check if charbuff is delim.
  * @alc: Struct param
  * @u: Character bufr
  * @q: pwd
  *
  * Return: (1) || (0).
  */

int chain_test(info_t *alc, char *u, size_t *q)
{
	size_t g = *q;

	if (u[g] == '|' && u[g + 1] == '|')
	{
		u[g] = 0;
		g++;
		alc->cmd_buf_type = CMD_OR;
	}
	else if (u[g] == '&' && u[g + 1] == '&')
	{
		u[g] = 0;
		g++;
		alc->cmd_buf_type = CMD_AND;
	}
	else if (u[g] == ';')
	{
		u[g] = 0;
		alc->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = g;

	return (1);
}

/**
  * chain_status - chcks to chain
  * @alc: Struct parameter.
  * @u: Character.buffer
  * @r: pwd
  * @j: 0 start
  * @n: length of buf
  *
  * Return: Nothing -> void func().
  */

void chain_status(info_t *alc, char *u, size_t *r, size_t j, size_t n)
{
	size_t k = *r;

	if (alc->cmd_buf_type == CMD_AND)
	{
		if (alc->status)
		{
			u[j] = 0;
			k = n;
		}
	}
	if (alc->cmd_buf_type == CMD_OR)
	{
		if (!alc->status)
		{
			u[j] = 0;
			k = n;
		}
	}
	*r = k;
}

/**
  * alias_change - chane als in str.
  * @alc: Struct param.
  *
  * Return: (1).
  */
int alias_change(info_t *alc)
{
	char *ch;
	int j;
	list_t *o;

	for (j = 0; j < 10; j++)
	{
		o = start_nd(alc->alias, alc->argv[0], '=');
		if (!o)
			return (0);
		free(alc->argv[0]);
		ch = locate_char(o->str, '=');
		if (!ch)
			return (0);
		ch = duplstr(ch + 1);
		if (!ch)
			return (0);
		alc->argv[0] = ch;
	}
	return (1);
}

/**
  * var_cange - variables in tkn.str are changed.
  * @alc: Struct param.
  *
  * Return: (1) success || (0).
  */

int var_cange(info_t *alc)
{
	list_t *o;
	int j;

	j = 0;
	for (j = 0; alc->argv[j]; j++)
	{
		if (alc->argv[j][0] != '$' || !alc->argv[j][1])
			continue;
		if (!comp_str(alc->argv[j], "$?"))
		{
			str_chd(&(alc->argv[j]),
					duplstr(num_convert(alc->status, 10, 0)));
			continue;
		}
		if (!comp_str(alc->argv[j], "$$"))
		{
			str_chd(&(alc->argv[j]),
					duplstr(num_convert(getpid(), 10, 0)));
			continue;
		}
		o = start_nd(alc->env, &alc->argv[j][1], '=');
		if (o)
		{
			str_chd(&(alc->argv[j]),
					duplstr(locate_char(o->str, '=') + 1));
			continue;
		}
		str_chd(&alc->argv[j], duplstr(""));
	}
	return (0);
}

/**
  * str_chd - str changed.
  * @mz: replaced str.
  * @mp: incoming string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int str_chd(char **mz, char *mp)
{
	free(*mz);
	*mz = mp;
	return (1);
}
