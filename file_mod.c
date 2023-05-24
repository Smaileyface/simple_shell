#include "shell.h"

/**
  * cmd_tr - finds if file chmod is permited.
  * @alc: Struct info.
  * @dir: path to file.
  *
  * Return: (1) => true || (0) => False.
  */

int cmd_tr(info_t *alc, char *dir)
{
	struct stat st;

	(void)alc;
	if (!dir || stat(dir, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
  * char_db - duplicates chars
  * @dir: path
  * @onn: Start
  * @off: Stop
  *
  * Return: new bufer ptr.
  */
char *char_db(char *dir, int onn, int off)
{
	int j, l;
	static char buf[1024];

	j = 0;
	l = 0;
	for (l = 0, j = onn; j < off; j++)
		if (dir[j] != ':')
			buf[l++] = dir[j];
	buf[l] = 0;
	return (buf);
}

/**
  * locte_path - locates path  str.
  * @alc: Struct parameter.
  * @dir: /path/..
  * @sh: command to be found.
  *
  * Return: cmd path || NULL.
  */
char *locte_path(info_t *alc, char *dir, char *sh)
{
	char *loc;
	int j, cp;

	j = 0;
	cp = 0;
	if (!dir)
		return (NULL);
	if ((str_len(sh) > 2) && begins(sh, "./"))
	{
		if (cmd_tr(alc, sh))
			return (sh);
	}
	while (1)
	{
		if (!dir[j] || dir[j] == ':')
		{
			loc = char_db(dir, cp, j);
			if (!*loc)
				str_concat(loc, sh);
			else
			{
				str_concat(loc, "/");
				str_concat(loc, sh);
			}
			if (cmd_tr(alc, loc))
				return (loc);
			if (!dir[j])
				break;
			cp = j;
		}
		j++;
	}
	return (NULL);
}
