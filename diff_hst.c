#include "shell.h"

/**
  * file_history - gets file. history
  * @alc: Struct parameter.
  *
  * Return: str having history file.
  */

char *file_history(info_t *alc)
{
	char *u, *path;

	path = show_envt(alc, "HOME=");
	if (!path)
		return (NULL);
	u = malloc(sizeof(char) * (str_len(path) + str_len(HIST_FILE) + 2));
	if (!u)
		return (NULL);
	u[0] = 0;
	cpstrng(u, path);
	str_concat(u, "/");
	str_concat(u, HIST_FILE);
	return (u);
}

/**
 * new_hst - touchs a file || appends to existing 1.
 * @alc: Struct parameter.
 *
 * Return: (1) -> success. || (-1).
 */

int new_hst(info_t *alc)
{
	list_t *d = NULL;
	ssize_t descr;
	char *fname = file_history(alc);

	if (!fname)
		return (-1);
	descr = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (descr == -1)
		return (-1);
	for (d = alc->history; d; d = d->next)
	{
		print_i(d->str, descr);
		write_fd('\n', descr);
	}
	write_fd(BUF_FLUSH, descr);
	close(descr);
	return (1);
}

/**
  * hst_read - function that reads history.
  * @alc: Struct parameter.
  *
  * Return: (history) => success || 0 => fail.
  */

int hst_read(info_t *alc)
{
	char *u = NULL;
	char *fname = file_history(alc);
	struct stat st;
	int j, end = 0, c = 0;
	ssize_t descr, lnrd;
	ssize_t sz = 0;

	if (!fname)
		return (0);
	descr = open(fname, O_RDONLY);
	free(fname);
	if (descr == -1)
		return (0);
	if (!fstat(descr, &st))
		sz = st.st_size;
	if (sz < 2)
		return (0);
	u = malloc(sizeof(char) * (sz + 1));
	if (!u)
		return (0);
	lnrd = read(descr, u, sz);
	u[sz] = 0;
	if (lnrd <= 0)
		return (free(u), 0);
	close(descr);
	for (j = 0; j < sz; j++)
		if (u[j] == '\n')
		{
			u[j] = 0;
			hst_lst(alc, u + end, c++);
			end = j + 1;
		}
	if (end != j)
		hst_lst(alc, u + end, c++);
	free(u);
	alc->histcount = c;
	while (alc->histcount-- >= HIST_MAX)
		rm_node(&(alc->history), 0);
	hst_num(alc);
	return (alc->histcount);
}

/**
  * hst_lst - entry add to hst list.
  * @alc: Argument Struct
  * @u: The bufer.
  * @c: Line.count.
  *
  * Return: 0.
  */

int hst_lst(info_t *alc, char *u, int c)
{
	list_t *o = NULL;

	if (alc->history)
		o = alc->history;
	end_node(&o, u, c);
	if (!alc->history)
		alc->history = o;
	return (0);
}

/**
  * hst_num - numbers hst after changes.
  * @alc: Struct args.
  *
  * Return: hst.count
  */

int hst_num(info_t *alc)
{
	int j;
	list_t *o = alc->history;

	j = 0;

	while (o)
	{
		o->num = j++;
		o = o->next;
	}
	return (alc->histcount = j);
}
