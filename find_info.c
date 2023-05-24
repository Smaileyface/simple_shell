#include "shell.h"

/**
  * info_cl - func that inits (info_t) struct.
  * @alc: adress to sruct.
  *
  */
void info_cl(info_t *alc)
{
	alc->arg = NULL;
	alc->argv = NULL;
	alc->path = NULL;
	alc->argc = 0;
}

/**
  * inf_set - inits info_t.struct
  * @alc: - Adress to struct.
  * @ag: - Vector argument
  *
  */
void inf_set(info_t *alc, char **ag)
{
	int j = 0;

	alc->fname = ag[0];
	if (alc->arg)
	{
		alc->argv = splt_str(alc->arg, " \t");
		if (!alc->argv)
		{
			alc->argv = malloc(sizeof(char *) * 2);
			if (alc->argv)
			{
				alc->argv[0] = duplstr(alc->arg);
				alc->argv[1] = NULL;
			}
		}
		for (j = 0; alc->argv && alc->argv[j]; j++)
			;
		alc->argc = j;
		alias_change(alc);
		var_cange(alc);
	}
}

/**
 * info_freed - info_t is freed.
 * @alc: Adress to struct.
 * @ch: all filds
 *
 * Return: nothing.
 */
void info_freed(info_t *alc, int ch)
{
	sfree(alc->argv);
	alc->argv = NULL;
	alc->path = NULL;
	if (ch)
	{
		if (!alc->cmd_buf)
			free(alc->arg);
		if (alc->env)
			rls_node(&(alc->env));
		if (alc->history)
			rls_node(&(alc->history));
		if (alc->alias)
			rls_node(&(alc->alias));
		sfree(alc->environ);
			alc->environ = NULL;
		free_ptr((void **)alc->cmd_buf);
		if (alc->readfd > 2)
			close(alc->readfd);
		wrt_char(BUF_FLUSH);
	}
}
