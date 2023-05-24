#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/stat.h>
#include <limits.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
/* used functions. */
/* all func defined. */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/**
 * struct liststr - sngl lnkd lst
 * @num: no
 * @str: str
 * @next: next nd
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
 * struct passinfo - guements passed function,
 * @arg: str generated  passed function,
 * @argv:arr
 * @path: str dir.path
 * @argc: arg.count
 * @line_count: unkwon error
 * @err_num: unkwon error
 * unkwon error
 * @linecount_flag: unkwon error
 * @fname: f.name
 * @env: pwd
 * @environ: envt
 * custom modified copy of environ from LL env
 * @history: hst node
 * @alias: alias.node
 * @env_changed: true || false
 * @status: recall
 * @cmd_buf: adrs of ptr to cmd.
 * @cmd_buf_type: type of CMD.
 * @readfd: modified
 * @histcount: hst of lines.
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - default str
 * @type: cmd flag
 * @func: func.
 *
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

ssize_t nd_indx(list_t *p, list_t *o);
list_t *start_nd(list_t *o, char *fx, char d);
size_t show_lst(const list_t *p);
char **strg_arry(list_t *n);
size_t lst_sz(const list_t *pt);
void chain_status(info_t *alc, char *u, size_t *r, size_t j, size_t n);
int chain_test(info_t *alc, char *u, size_t *q);
int alias_change(info_t *alc);
int var_cange(info_t *alc);
int str_chd(char **mz, char *mp);
void cmd_fk(info_t *alc);
void srch_cmd(info_t *alc);
char *locte_path(info_t *alc, char *dir, char *sh);
char *char_db(char *dir, int onn, int off);
int cmd_tr(info_t *alc, char *dir);
int loophsh(char **);
int wrt_char(char a);
void prnts(char *tx);
char *duplstr(const char *tx);
char *cpstrng(char *to, char *from);
int cmd_srch(info_t *alc);
int print_i(char *tx, int descr);
int write_fd(char tx, int descr);
int free_ptr(void **add);
char *begins(const char *str, const char *ee);
void rm_cmnt(char *ch);
int strtoint(char *tx);
int line_std(info_t *alc, char **tr, size_t *n);
ssize_t input_fetch(info_t *alc);
void block_cp(__attribute__((unused))int n);
char *show_envt(info_t *alc, const char *nm);
int envt(info_t *alc);
int set_env(info_t *alc);
int rm_env(info_t *alc);
int display_env(info_t *);
int init_envt(info_t *alc, char *stri, char *v);
int envt_unset(info_t *alc, char *ch);
char **shw_envt(info_t *alc);
void show_error(info_t *alc, char *tx);
int prnt_dec(int i, int fl);
char *num_convert(long int no, int b, int fl);
int str_len(char *t);
char **split_str(char *tr, char ch);
char **splt_str(char *tr, char *ch);
int comp_str(char *t, char *t2);
char *str_concat(char *to, char *from);
int write_c(char tx);
void *real_mem(void *t, unsigned int o, unsigned int n);
void sfree(char **st);
int history(info_t *hst);
int my_alias(info_t *als);
char *mem_fill(char *t, char c, unsigned int m);
int cd_cmd(info_t *als);
int help_cmd(info_t *alc); /* @here */
int exit_cmd(info_t *als);
char *locate_char(char *str, char tx);
void info_freed(info_t *alc, int ch);
void inf_set(info_t *alc, char **ag);
void info_cl(info_t *alc);
char *concat_strng(char *frs, char *scn, int m);
char *copy_strng(char *dst, char *sr, int m);
int shell_mode(info_t *addr);
int delimeter(char ch, char *del);
int alpha_char(int);
int a_toi(char *);
void put_str(char *txt);
int shloop(info_t *alc, char **v);
int hst_num(info_t *alc);
int hst_lst(info_t *alc, char *u, int c);
int hst_read(info_t *alc);
int new_hst(info_t *alc);
char *file_history(info_t *alc);
void rls_node(list_t **p);
int rm_node(list_t **p, unsigned int x);
size_t str_show(const list_t *p);
list_t *end_node(list_t **p, const char *t, int n);
list_t *node_plus(list_t **p, const char *t, int n);
extern char **environ;
#endif
