#include "shell.h"

/**
 * main - Start
 * @argct: argument counter
 * @argvc: argument vector
 *
 * Return: (0) => success || (1) => Fail
 */
int main(int argct, char **argvc)
{
	int descr;
	info_t info[] = { INFO_INIT };

	descr = 2;
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (descr)
			: "r" (descr));
	if (argct == 2)
	{
		descr = open(argvc[1], O_RDONLY);
		if (descr == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				put_str(argvc[0]);
				put_str(": 0: Cannot open ");
				put_str(argvc[1]);
				write_c('\n');
				write_c(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = descr;
	}
	display_env(info);
	hst_read(info);
	shloop(info, argvc);
	return (EXIT_SUCCESS);
}
