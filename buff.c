#include "shell.h"

/**
  * buff_cmds - some bufer commands
  * @alc: Struct param
  * @u: Buffer adress.
  * @n: Len.var address
  *
  * Return: no of read bytes.
  */
ssize_t buff_cmds(info_t *alc, char **u, size_t *n)
{
	ssize_t i;
	size_t p;

	i = 0;
	p = 0;
	if (!*n)
	{
		free(*u);
		*u = NULL;
		signal(SIGINT, block_cp);
#if USE_GETLINE
		i = getline(u, &p, stdin);
#else
		i = line_std(alc, u, &p);
#endif
		if (i > 0)
		{
			if ((*u)[i - 1] == '\n')
			{
				(*u)[i - 1] = '\0';
				i--;
			}
			alc->linecount_flag = 1;
			rm_cmnt(*u);
			hst_lst(alc, *u, alc->histcount++);
			{
				*n = i;
				alc->cmd_buf = u;
			}
		}
	}
	return (i);
}

/**
  * input_fetch - gets a line.
  * @alc: Struct parameter
  *
  * Return: no of read -bytes
  */
ssize_t input_fetch(info_t *alc)
{
	static size_t a, b, c;
	static char *u;
	ssize_t s;
	char **fp = &(alc->arg), *x;

	s = 0;
	wrt_char(BUF_FLUSH);
	s = buff_cmds(alc, &u, &c);
	if (s == -1)
		return (-1);
	if (c)
	{
		b = a;
		x = u + a;
		chain_status(alc, u, &b, a, c);
		while (b < c)
		{
			if (chain_test(alc, u, &b))
				break;
			b++;
		}
		a = b + 1;
		if (a >= c)
		{
			a = c = 0;
			alc->cmd_buf_type = CMD_NORM;
		}
		*fp = x;
		return (str_len(x));
	}
	*fp = u;
	return (s);
}

/**
  * buff_read - func that reads a buffer.
  * @alc: Struct parameter.
  * @u: the bufer.
  * @j: the ->sze.
  *
  * Return: 00.
  */
ssize_t buff_read(info_t *alc, char *u, size_t *j)
{
	ssize_t s;

	s = 0;
	if (*j)
		return (0);
	s = read(alc->readfd, u, READ_BUF_SIZE);
	if (s >= 0)
		*j = s;
	return (s);
}
/**
  * line_std - func that gets the nxt input lne from STDIN.
  * @alc: Struct param.
  * @tr: Pointer adress to buffer.
  * @n: buff size.
  *
  * Return: t
  */
int line_std(info_t *alc, char **tr, size_t *n)
{
	static size_t en, j;
	static char u[READ_BUF_SIZE];
	size_t l;
	ssize_t a, b;
	char *p = NULL, *np = NULL, *d;

	a = 0;
	b = 0;
	p = *tr;
	if (p && n)
		b = *n;
	if (j == en)
		j = en = 0;
	a = buff_read(alc, u, &en);
	if (a == -1 || (a == 0 && en == 0))
		return (-1);

	d = locate_char(u + j, '\n');
	l = d ? 1 + (unsigned int)(d - u) : en;
	np = real_mem(p, b, b ? b + l : l + 1);
	if (!np)
		return (p ? free(p), -1 : -1);
	if (b)
		concat_strng(np, u + j, l - j);
	else
		copy_strng(np, u + j, l - j + 1);
	b += l - j;
	j = l;
	p = np;
	if (n)
		*n = b;
	*tr = p;
	return (b);
}

/**
  * block_cp - blocks the ctrl-c
  * @n: signal No.
  *
  * Return: Nothing.
 */
void block_cp(__attribute__((unused))int n)
{
	prnts("\n");
	prnts("$ ");
	wrt_char(BUF_FLUSH);
}
