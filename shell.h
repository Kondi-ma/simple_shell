#ifndef _SHELL_H
#define _SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* paradise */
#define _READ_BUF_SIZE 1024
#define _WRITE_BUF_SIZE 1024
#define _BUF_FLUSH -1

/* greens */
#define _CMD_NORM    0
#define _CMD_AND     1
#define _CMD_OR      2
#define _CMD_CHAIN   3

/* achievers */
#define CONVERT_LOWERCASE    0
#define CONVERT_UNSIGNED     1

/* maisha */
#define USE_GETLINE   0
#define USE_STRTOK    0
#define HIST_MAX      4096
#define HIST_FILE     "simple_shell_hist"

extern char **environ;

/**
 * struct list - this is a singly inked list
 * @NUM: this is the number field
 * @strr: this is a string
 * #nxt: it points to the next code
 * */
typedef struct list
{
	int NUM;
	char *strr;
	struct list *nxt;
}
list_t;

/**
 * struct pseudopass - this contains pseudo-arguments for function pointer struct, thus allowing uniform prototype for function pointer struct.
 * @argu: this is a string generated from getline containing some arguments
 * @arg1: array of strings generated from argu
 * @strpath: this is a string path for the current command
 * @argC: Argument count
 * @err_count: this is the error count
 * @err_cod: this is the error code for exit
 * @countline: if on count this line of Input
 * @prname: this is the program filename
 * @envi: the linked list copy for environ
 * @environ: a custom modified copy of environ from env
 * @hst: this is the history node
 * @aka: this is the alias node
 * @changed_envi: used if the environ was changed
 * @update: this is the return status of the last executed commsnd
 * @cmd_buf: pointer address to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @hcount: this is the hist line number count
 * @yeah: the file from which to read the line input
 */
typedef struct pseudopass
{
	char *argu;
	char **arg1;
	char *strpath;
	int argC;
	int countline;
	char *prname;
	list_t *envi;
	list_t *hst;
	list_t *aka;
	char **environ;
	int changed_envi;
	int update;

	char **cmd_buf;
	int cmd_buf_type;
	int hcount;
	int yeah;
}
info_t;

#define INF_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0} \

/**
 * struct jenga - this contains a builtin str nd function
 * @com: builtin command flag
 * @f: function
 */
typedef struct jenga
{
	char *com;
	int (*f)(info_t);
}
builtin_table;

/* L.c */
int L(char **);

/* maisha.c */
int find_builtin(info_t *);
int run(info_t *, char **);
void Cmd_find(info_t *);
void Cmd_fork(info_t *);

/* sunrise.c */
int PutC(char);
int putd(char a, int d);
int putdd(char *str1, int d);
void put(char *);

/* zero.c */
int Comm(info_t b, char b);
char *sun(char b, int, int);
char *A(info_t b, char b, char b);

/* bottle.c */
int lenstr(char c);
int comstr(char c, char c);
char *starter(const char c, const char c);
char *Cat(char c, char c);

/* bottle1.c */
int Putc(char);
char *copyst(char d, char d);
void Put(char d);
char *dupl(const char d);

/* mem.c */
int flash(void **);

/* row.c */
char **Tows(char *, char *);
char **Tows1(char *, char);

/* locate.c */
void good(char **);
char *smem(char *, char, unsigned int);
void *allocRe(void *, unsigned int, unsigned int);

/* leave.c */
char *charst(char *, char);
char *copyst(char *, char *, int);
char *catst(char *, char *, int);

/* khan.c */
int ATOI(char *);
int beta(int);
int alpha(info_t *);
int denim(char, char *);

/* mjengo.c */
int a(info_t *);
int b(info_t *);
int c(info_t *);

/* mjengo1.c */
int hist(info_t *);
int aka(info_t);

/* sunrise1.c */
int prt(int, int);
void exclude_comment(char *);
void err_prt(info_t *, char *);
int err(char *);
char *num_con(long int, int, int);

/* Lineout.c */
void hand(int);
int line(info_t *, char **, size_t *);
ssize_t in(info_t *);

/* information.c */
void finfo(info_t *, int);
void sinfo(info_t *, char **);
void clinfo(info_t *);

/* window.c */
int Env(info_t *);
int sEnv(info_t *);
int list_population(info_t *);
int usEnv(info_t *);
char gEnv(info_t *, const char *);

/* gwin.c */
int senv(info_t *, char *, char *);
int usenv(info_t *, char *);
char **genv(info_t *);

/* Hist.c */
int his_read(info_t *inf);
int hist_and(info_t *inf);
int his_jenga(info_t *inf, char *biggie, int flix);
char *hist_get(info_t *inf);
int history(info_t *inf);

/* chair.c */
void fist(list_t **);
int index_del(list_t **, unsigned int);
list_t *knob(list_t **, const char *, int);
size_t pist(const list_t *);
list_t *knob_end(list_t **, const char *, int);

/* chair1.c */
char **strL(list_t *);
size_t plist(const list_t *);
list_t *knob_start(list_t *, char *, char);
ssize_t ind_knob(list_t *, list_t *);
size_t len_lst(const list_t *);

/* variab.c */
int change_aka(info_t *);
int change_name(info_t *);
int change_str(char **, char *);
int star(info_t *, char *, size_t *);
void chain_look(info_t *, char *, size_t *, size_t, size_t);

#endif
