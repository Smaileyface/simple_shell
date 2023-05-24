#include "shell.h"
/**
  * exit_cmd - function that exits the shell terminal.
  * @als: Potential arguments struct.
  * Maintains const func pr0t0types
  * Return: Terminal exit ie 0 if als.argv[0] not equal to 'exit'.
  */
int exit_cmd(info_t *als)
{
	int q;

	if (als->argv[1])
	{
		q = strtoint(als->argv[1]);
		if (q == -1)
		{
			als->status = 2;
			show_error(als, "new error: ");
			put_str(als->argv[1]);
			write_c('\n');
			return (1);
		}
		als->err_num = strtoint(als->argv[1]);
		return (-2);
	}
	als->err_num = -1;
	return (-2);
}

/**
  * cd_cmd - chdir.
  * @als: Arguments.
  * Return: (0).
  */
int cd_cmd(info_t *als)
{
	int n;
	char *t, *d, buffer[1024];

	t = getcwd(buffer, 1024);
	if (!t)
	{
		prnts(">> fail msg <<\n");
	}
	if (!als->argv[1])
	{
		d = show_envt(als, "HOME=");
		if (!d)
		{
			n = chdir((d = show_envt(als, "PWD=")) ? d : "/");
		}
		else
			n = chdir(d);
	}
	else if (comp_str(als->argv[1], "-") == 0)
	{
		if (!show_envt(als, "OLDPWD="))
		{
			prnts(t);
			wrt_char('\n');
			return (1);
		}
		prnts(show_envt(als, "OLDPWD=")), wrt_char('\n');
		n = chdir((d = show_envt(als, "OLDPWD=")) ? d : "/");
	}
	else
		n = chdir(als->argv[1]);
	if (n == -1)
	{
		show_error(als, "unable to cd to ");
		put_str(als->argv[1]), write_c('\n');
	}
	else
	{
		init_envt(als, "OLDPWD", show_envt(als, "PWD="));
		init_envt(als, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
  * help_cmd - changs crnt dir of process
  * @alc: Arguments.
  *
  * Return: (0).
  */
int help_cmd(info_t *alc)
{
	char **arr;

	arr = alc->argv;
	prnts("Function not implemented yet\n");
	if (0)
	{
		prnts(*arr);
	}
	return (0);
}
