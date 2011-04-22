#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#define syntax(opcode,param)    \
        {    \
            char    synhelp[100]; \
            sprintf(synhelp, "%s%s:%s %s%s%s %s%s%s\n", \
                    CC_BOLD, _("Syntax"), CC_RESTORE, CC_RED, opcode, \
                    CC_RESTORE, CC_CYAN, param, CC_RESTORE); \
            out(_("%s"), synhelp); \
        }

/* helpers.c */
void help_print(void);
void help_debug(void);
void help_random(void);
void help_type(void);
void help_optmem(void);
void help_meminfo(void);
void help_ewok(void);
void help_forloop(void);
void help_repeat(void);
void help_exit(void);
void help_push(void);
void help_new(void);
void help_sel(void);

void syntax_print(void);
void syntax_debug(void);
void syntax_random(void);
void syntax_type(void);
void syntax_optmem(void);
void syntax_meminfo(void);
void syntax_ewok(void);
void syntax_forloop(void);
void syntax_repeat(void);
void syntax_exit(void);
void syntax_push(void);
void syntax_new(void);
void syntax_sel(void);

#endif /* HELPERS_H_INCLUDED */
