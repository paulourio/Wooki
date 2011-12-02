#ifndef WOOKI_H_INCLUDED
#define WOOKI_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#include <libintl.h>
#include <locale.h>
#define _(String)       gettext(String)
#define _f(String)      _(CC_RESTORE String CC_RESTORE)
/* Note: strings with _f() won't be able to internationalize. */

#define    out(...)     fprintf(stdout, __VA_ARGS__)
#define error(...)      fprintf(stderr, __VA_ARGS__)

#define CONSOLE_COLORS

#ifdef CONSOLE_COLORS
#    define    CC_BLACK    "\033[30m"
#    define    CC_RED      "\033[31m"
#    define    CC_GREEN    "\033[32m"
#    define    CC_BROWN    "\033[33m"
#    define    CC_BLUE     "\033[34m"
#    define    CC_MAGENTA  "\033[35m"
#    define    CC_CYAN     "\033[36m"
#    define    CC_WHITE    "\033[37m"
#    define    CC_BOLD     "\033[1m"
#    define    CC_RESTORE  "\033[0m"
#else
#    define    CC_BLACK    ""
#    define    CC_RED      ""
#    define    CC_GREEN    ""
#    define    CC_BROWN    ""
#    define    CC_BLUE     ""
#    define    CC_MAGENTA  ""
#    define    CC_CYAN     ""
#    define    CC_WHITE    ""
#    define    CC_BOLD     ""
#    define    CC_RESTORE  ""
#endif

/* For user-triggers */
#define list_arg(index)     *(info->list + index*sizeof(void *))

#define cmp(base,str)       (strcmp(base, str) == 0)

#define pvalue(name,type)   (* (type *) name)

typedef void (*fhelp_t)(void); /* Type for helper functions */

struct trigger_info {
    char            *opcode;        /* opcode string */
    void            *object;        /* Pointer to the user data structure. */
    void            **list;         /* List of parameters */
    int             list_num;       /* Number of elements in the list */
    size_t          item_size;      /* Size of each item in the list */
    unsigned int    debug_level;    /* Copy of rtl.debuglevel */
};

typedef void (*ftrigger_t)(struct trigger_info *);


/* core.c */
void execute(void);
void set_interactive(const bool activate);

/* wobject.c */
void *new_object(const char *name, const char *classname)
            __attribute__((__nonnull__(1,2)))
            __attribute__((__warn_unused_result__));
void opcode(const void *object, const char *name, const ftrigger_t function,
            const int min, const int max)
            __attribute__((__nonnull__ (1, 2, 3)));

/* No limit for minimum and maximum number of parameters */
#define    NOLIMIT        (-1)

/* types.c */
bool getvalue(char *input, void **output) __attribute__((__nonnull__ (1)));
bool settype(char *value) __attribute__((__nonnull__));
void fix_type(void);
size_t getsizeof(int type) __attribute__((__warn_unused_result__));
char *typetostr(void) __attribute__((__warn_unused_result__));

#endif /* WOOKI_H_INCLUDED */
