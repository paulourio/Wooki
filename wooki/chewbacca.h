#ifndef CHEWBACCA_H_INCLUDED
#define CHEWBACCA_H_INCLUDED

#include <stdbool.h>

#include <wooki.h>

#define ENABLE_DEBUG 1

#ifdef ENABLE_DEBUG
#	define debug(level,...) \
				if (level<=rtl.debuglevel) fprintf(stderr, __VA_ARGS__)
#else
#	define debug(...)
#endif

/* Debug levels */
#define	NO_DEBUG		0
#define	BASIC_DEBUG		1
#define	EXTREME_DEBUG	2
#define NONSENSE_DEBUG	3

#define TALLOC(type)		(type *) malloc(sizeof(type))
#define CALLOC(length)		(char *) calloc(length, sizeof(char))
#define MALLOC(len,type)	(type *) malloc(((size_t) len) * sizeof(type))
#define	MCALLOC(length)		MALLOC(length, char)

#define token(index)		*(argv + ((size_t) index)*sizeof(char *))

#define MAX_PARSERS		100
#define MAX_TRIGGERS	50		/* Maximum triggers for each object */
#define	MAX_OBJECTS		40
#define MAX_WORD_LEN	15
#define MAX_TOKEN		1000

/* Initial value for line length. If getline() needs more, realloc is used. */
#define LINE_LENGTH 100
#define NOINPUT		-1
#define	NO_SELECTED_OBJECT	(-1)

#define INTEGER	1
#define INT64	2
#define CHAR	3
#define	BOOL	4
#define	FLOAT	5
#define	DOUBLE	6

#define DEFAULT_INTERACTIVE			(true);//(false)
#define DEFAULT_DEBUG				NO_DEBUG; //NONSENSE_DEBUG
#define	DEFAULT_MEM_OPTIMIZATION	(false)
#define DEFAULT_TYPE				INTEGER

struct runtime	rtl;

/* Parser */
typedef	void (*fcmd_t)(char *[], int); /* Used for parsers */

struct parser_trigger {
	char	*opcode;
	fcmd_t	function;
	fhelp_t	helper;
};

typedef struct parser_trigger	parser_tr;


struct line {
	char	*data;		/* Last read line */
	int		length;
	size_t	size;
};


struct tokens {
	char	**list;		/* List of pointers for each token */
	int		count;		/* Stored tokens count */
	size_t	size;		/* Token size in bytes */
};


struct parser {
	parser_tr	*list;
	size_t		count;
};

#include "runtime.h"

/* object.c */
bool contains_object(const char *name);
bool select_object(const char *name);
void print_object_list(void);
void parse_select_object(char *argv[], int argc);

/* info.c */
void print_memsize(const int data);
void meminfo(void);
void show_help(char *argv[], int argc);
void show_copyright(void);
void show_license(void);

/* parser.c */
void parse_tokens(void);
void register_parser(const char *name, const fcmd_t function,
					const fhelp_t fhelper);

/* parsers.c */
void parse_debug(char *argv[], int argc);
void parse_exit(void);
void parse_print(char *argv[], int argc);
void parse_random(char *argv[], int argc);
void parse_type(char *argv[], int argc);
void parse_optmem(char *argv[], int argc);
void parse_forloop(char *argv[], int argc);
void parse_repeat(char *argv[], int argc);
void parse_push(char *argv[], int argc);
void parse_pop(char *argv[], int argc);
void parse_new(char *argv[], int argc);
void parse_free(char *argv[], int argc);

/* benchmark.c */
void syntax_benchmark(void);
void help_benchmark(void);
void parse_benchmark(char *argv[], int argc);

#include "helpers.h"

/* triggers.c */
void activate_trigger(const char *name, void **list, const int num)
		__attribute__((__nonnull__(1)));
#endif /* CHEWBACCA_H_INCLUDED */
