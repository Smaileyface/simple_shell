#include "shell.h"
/**
  * envt - shows current environment @
  * @alc: Arguments
  *
  * Return: (0)
  */
int envt(info_t *alc)
{
	str_show(alc->env);
	return (0);
}
/**
  * show_envt - function that gets environment variable
  * @alc: Arguments
  * @nm: name
  *
  * Return: envt variable
  */
char *show_envt(info_t *alc, const char *nm)
{
	list_t *nd = alc->env;
	char *tx;

	while (nd)
	{
		tx = begins(nd->str, nm);
		if (tx && *tx)
		{
			return (tx);
		}
		nd = nd->next;
	}
	return (NULL);
}

/**
 * set_env - init new env or modify already existing one.
 * @alc: Args
 *
 * Return: (0).
 */
int set_env(info_t *alc)
{
	if (alc->argc != 3)
	{
		put_str("Wrong no of args\n");
		return (1);
	}
	if (init_envt(alc, alc->argv[1], alc->argv[2]))
		return (0);
	return (1);
}
/**
  * rm_env - rm env vars
  * @alc: Args.
  *
  * Return: (0).
  */
int rm_env(info_t *alc)
{
	int j;

	if (alc->argc == 1)
	{
		put_str("add more args\n");
		return (1);
	}
	for (j = 1; j <= alc->argc; j++)
		envt_unset(alc, alc->argv[j]);
	return (0);
}
/**
  * display_env - display envr lnkd list
  * @alc: Args..
  *
  * Return: (0)
  */
int display_env(info_t *alc)
{
	size_t j;
	list_t *nd;

	nd = NULL;
	for (j = 0; environ[j]; j++)
		end_node(&nd, environ[j], 0);
	alc->env = nd;
	return (0);
}
