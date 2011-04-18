#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <time.h> /// TODO : random seed here?
#include <wooki.h>
#include "chewbacca.h"

char *	__name__ = "Wooki";
int		__big_version__ = 0;
int		__small_version__ = 1;

struct line		line;
struct tokens	tokens;


static void process_line(void) {
	char	*rules = " ,:()\n";
	char	*tok;

	//debug(3, _("Splitting line into tokens.\n"));
	tokens.count = (int) (tokens.size = 0);
	tok = strtok(line.data, rules);
	while (tok != NULL) {
		if (tokens.count > MAX_TOKEN) {
			error(_("TokenOverflow: The line has reached the limit.\n"));
			debug(1, _("Ignoring line (too big)\n"));
			return; /* Action: ignore line, step to next */
		}
		if (strlen(tok) > MAX_WORD_LEN) {
			error(_("Token '%s' is bigger than allowed. Skipping.\n"), tok);
			return;
		}
		*(tokens.list + tokens.size) = tok;
		tokens.count++;
		tokens.size += sizeof(char *);
		tok = strtok(NULL, rules); 	/* Next token */
	}
	//debug(3, _("Token count: %d\n"), tokens.count);
	if (tokens.count == 0)
		return;
	parse_tokens();
}


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
static bool readline(void) {
	if (rtl.interactive_input) {
		out(">> ");
	}
	line.length = (size_t) getline(&line.data, &line.size, stdin);
	if (line.length == NOINPUT) {
		debug(1, _("\nEOF Received\n"));
		return (false);
	}
	if (line.length > 1)
		process_line();
	return (true);
}
#pragma GCC diagnostic pop


/*	Function to be called to start processing data. */
void execute(void) {
	out(_("%s %d.%d\n"
			"Type \"help\", \"copyright\" or \"license\" for more "
			"information.\n"), __name__, __big_version__, __small_version__);
	while (readline());
}


/*	Set Interactive
 *		When actived, the input will interact with user, printing ">> "
 *	whenever a line is going to be read.
 */
void set_interactive(const bool activate) {
	rtl.interactive_input = activate;
}


__attribute__((__constructor__ (101)))
static void initialize_runtime(void) {
	setlocale(LC_ALL, "pt_BR.UTF-8");
	bindtextdomain("wooki", "wooki/locale");
	textdomain("wooki");

	rtl.debuglevel = DEFAULT_DEBUG;
	debug(1, _("Debug level: %s%s%s\n"), CC_BOLD,
				rtl.debuglevel == 0? _("disabled")
				: rtl.debuglevel == 1? _("basic")
				: rtl.debuglevel == 2? _("extreme")
				: _("non-sense!"), CC_RESTORE);
	debug(2, _("Initializing core..\n"));
	line.size = LINE_LENGTH;
	line.data = MCALLOC(line.size);
	assert(line.data != NULL);
	tokens.list = MALLOC(MAX_TOKEN, char *);
	assert(tokens.list != NULL);

	srand((unsigned int) time(NULL));
}


__attribute__((__destructor__ (101)))
static void finalize_runtime(void) {
	debug(2, _("Finalizing core..\n"));
	free(line.data);
	free(tokens.list);
}
