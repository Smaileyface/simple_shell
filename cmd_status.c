#include "shell.h"

/**
  * shloop - shll loop.
  * @alc: Struct parameter
  * @v: - arg vector.
  *
  * Return: (0) => success || (1) => error.
  */

int shloop(info_t *alc, char **v)
{
	int b;
	ssize_t s;

	s = 0;
	b = 0;
	while (s != -1 && b != -2)
	{
		info_cl(alc);
		if (shell_mode(alc))
			prnts("$ ");
		write_c(BUF_FLUSH);
		s = input_fetch(alc);
		if (s != -1)
		{
			inf_set(alc, v);
			b = cmd_srch(alc);
			if (b == -1)
				srch_cmd(alc);
		}
		else if ((shell_mode(alc)))
			wrt_char('\n');
		info_freed(alc, 0);
	}
	new_hst(alc);
	info_freed(alc, 1);
	if (!shell_mode(alc) && alc->status)
		exit(alc->status);
	if (b == -2)
	{
		if (alc->err_num == -1)
			exit(alc->status);
		exit(alc->err_num);
	}
	return (b);
}

/**
  * cmd_srch - searches already build in cmds
  * @alc: Struct parameter
  *
  * Return: (-1) built not found 1 - found.
  *
  */

int cmd_srch(info_t *alc)
{
	int j;
	int b = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_cmd},
		{"env", envt},
		{"help", help_cmd},
		{"history", history},
		{"setenv", set_env},
		{"unsetenv", rm_env},
		{"cd", cd_cmd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (comp_str(alc->argv[0], builtintbl[j].type) == 0)
		{
			alc->line_count++;
			b = builtintbl[j].func(alc);
			break;
		}
	return (b);
}

/**
  * srch_cmd - finds cmd in path
  * @alc: Struct parameter
  *
  * Return: nothing.
  */

void srch_cmd(info_t *alc)
{
	int l, j;
	char *dir = NULL;

	alc->path = alc->argv[0];
	if (alc->linecount_flag == 1)
	{
		alc->line_count++;
		alc->linecount_flag = 0;
	}
	for (j = 0, l = 0; alc->arg[j]; j++)
		if (!delimeter(alc->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	dir = locte_path(alc, show_envt(alc, "PATH="), alc->argv[0]);
	if (dir)
	{
		alc->path = dir;
		cmd_fk(alc);
	}
	else
	{
		if ((shell_mode(alc) || show_envt(alc, "PATH=")
					|| alc->argv[0][0] == '/') && cmd_tr(alc, alc->argv[0]))
			cmd_fk(alc);
		else if (*(alc->arg) != '\n')
		{
			alc->status = 127;
			show_error(alc, "unknown command\n");
		}
	}
}

/**
  * cmd_fk - fks an executable thrd to run-the-cmd.
  * @alc: Struct parameter.
  *
  * Return: Nothing to return.
  */

void cmd_fk(info_t *alc)
{
	pid_t pd;

	pd = fork();
	if (pd == -1)
	{
		perror("Eror:");
		return;
	}
	if (pd == 0)
	{
		if (execve(alc->path, alc->argv, shw_envt(alc)) == -1)
		{
			info_freed(alc, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(alc->status));
		if (WIFEXITED(alc->status))
		{
			alc->status = WEXITSTATUS(alc->status);
			if (alc->status == 126)
				show_error(alc, "The Permission is denied\n");
		}
	}
}
