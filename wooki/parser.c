#include <assert.h>
#include <string.h>
#include "chewbacca.h"

extern struct tokens	tokens;

struct parser	parsers;

void parse_tokens(void) {
	size_t	i;
	bool	ok = false;

	for (i=0; i<parsers.count; i++)
		if (cmp(*tokens.list, parsers.list[i].opcode)) {
			debug(4, _("Calling parser @ %s%p%s\n"), CC_RED,
					parsers.list[i].function, CC_RESTORE);
			((fcmd_t) *parsers.list[i].function)(tokens.list, tokens.count);
			ok = true;
		}
	if (!ok)
		out(_("Opcode %s%s%s is not defined.\n"), CC_BOLD CC_CYAN,
			*tokens.list, CC_RESTORE);
}


void register_parser(const char *name, const fcmd_t function,
					const fhelp_t fhelper) {
	if (parsers.count + 1 == MAX_PARSERS) {
		debug(1, _("Can't register parser for '%s'. No space left."), name);
		return;
	}
	parsers.list[parsers.count].opcode = (char *) name;
	parsers.list[parsers.count].function = function;
	parsers.list[parsers.count].helper = fhelper;
	debug(3, _("Parser registered:\n\tOP Code: %s%s%s\n\tFunction: %s%p%s\n"),
			CC_BROWN, parsers.list[parsers.count].opcode, CC_RESTORE,
			CC_BLUE, parsers.list[parsers.count].function, CC_RESTORE);
	parsers.count++;
}


__attribute__((__constructor__ (103)))
static void initialize_parser(void) {
	debug(3, _("Initializing parser..\n"));
	parsers.list = MALLOC(MAX_PARSERS, struct parser_trigger);
	assert(parsers.list != NULL);
	register_parser("help", show_help, (fhelp_t) show_help);
	register_parser("copyright", (fcmd_t) show_copyright, NULL);
	register_parser("license", (fcmd_t)  show_license, NULL);

	register_parser("debug", parse_debug, help_debug);
	register_parser("type", parse_type, help_type);
	register_parser("exit", (fcmd_t) parse_exit, help_exit);

	register_parser("optmem", parse_optmem, help_optmem);
	register_parser("meminfo", (fcmd_t) meminfo, help_meminfo);
	register_parser("ewok", (fcmd_t) garbage_collector_naive, help_ewok);
	register_parser("bm", parse_benchmark, help_benchmark);

	register_parser("print", parse_print, help_print);

	register_parser("rnd", parse_random, help_random);
	register_parser("for", parse_forloop, help_forloop);
	register_parser("repeat", parse_repeat, help_repeat);

	register_parser("new", parse_new, help_new);
	register_parser("free", parse_free, NULL);
	register_parser("sel", parse_select_object, help_sel);

	register_parser("push", parse_push, help_push);
	register_parser("pop", parse_pop, NULL);
}


__attribute__((__destructor__ (103)))
static void finalize_parser(void) {
	debug(3, _("Finalizing parser..\n"));
	free(parsers.list);
}

#undef token
