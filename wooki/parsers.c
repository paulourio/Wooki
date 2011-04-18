#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wooki.h>
#include "chewbacca.h"

void parse_debug(char *argv[], int argc) {
	unsigned int	level;
	char			*param;

	if (argc == 2) {
		param = (char *) token(1);
		if (sscanf(param, "%u", &level) == 1)
			if (level <= NONSENSE_DEBUG) {
				rtl.debuglevel = level;
				debug(2, _("Setting debug level to %d.\n"), level);
				return;
			}
	}
	syntax_debug();
}


void parse_exit(void) {
	out(_("Bye!"));
	exit(EXIT_SUCCESS);
}


void parse_print(char *argv[], int argc) {
	if (argc == 1) {
		if (rtl.current_obj == NO_SELECTED_OBJECT) {
			out(_("There is no selected object for this operation.\n"));
			return;
		}
		print_object_info( rtl.objects.list[rtl.current_obj]->name );
	} else {
		char	*arg = (char *) token(1);

		if (cmp("objects", arg)) {
			print_object_list();
		} else if (cmp("registers", arg)) {
			print_registers();
		} else if (cmp("ewok", arg)) {
			print_ewok();
		} else {
			// if isn't a built-in object, search for the object.
			if (!print_object_info(arg))
				out(_("Object %s%s%s was not found.\n"), CC_BOLD, arg,
						CC_RESTORE);
		}
	}
}


void parse_random(char *argv[], int argc) {
	void	*from, *to;

	if (argc != 4) {
		syntax_random();
		return;
	}
	if (getvalue(token(1), &from) == false) {
		error(_("Can't read '%s' as %s\n"), token(1), typetostr());
		return;
	}
	if (getvalue(token(2), &to) == false) {
		error(_("Can't read '%s' as %s\n"), token(2), typetostr());
		return;
	}
	{
		int	*rand_base;
		int	ini = pvalue(from,int), end = pvalue(to,int);
		int delta = end - ini;

		if (ini > end) {
			error(_("Can't generate random value betweeb this range\n"));
			return;
		}
		rand_base = TALLOC(int);
		debug(2, _("Generating random (%d..%d): \n"), ini, end);
		*rand_base = (rand() % delta) + ini;
		debug(2, _("Generated random value: %d\n"), *rand_base);

		void **list = TALLOC(void *);
		*list = reference(rand_base, true);
		activate_trigger(token(3), list, 1);
		free(list);
		/// TODO: Generated random is just in int type.
	}
}


void parse_type(char *argv[], int argc) {
	if (argc != 2) {
		syntax_type();
		return;
	}
	if (settype(token(1))) {
		debug(2, _("Data type set to %s%s%s\n"), CC_BOLD, token(1), CC_RESTORE);
	} else
		error(_("Can't change type to '%s'\n"), token(1));
}


void parse_optmem(char *argv[], int argc) {
	/// TODO: When should allow change optimization setting ?
	if (argc != 2 || strlen(token(1)) != 1) {
		syntax_optmem();
		return;
	}
	rtl.optimize_memory = (token(1)[0] == '1');
	debug(1, _("Memory optimization: %s%s%s\n"), CC_BOLD,
			rtl.optimize_memory? _("activated"): _("disabled"), CC_RESTORE);
}


static int *copyint(const int value) {
	int		*tmp;

	tmp = TALLOC(int);
	*tmp = value;
	return (tmp);
}
void parse_forloop(char *argv[], int argc) {
	int		*ini, *fim, *incremento = NULL;
	char	*command;
	bool	syntax_fail;

	/* Possibilities:
		5 arguments
			for [from] to [to], [destination]
		7 arguments
			for [from] to [to] step [step], [destination]
	 */
	syntax_fail = (argc != 5 && argc != 7);
	if (!syntax_fail) {
		if (argc == 5) {
			syntax_fail = (!cmp("to", token(2))
							|| !getvalue(token(1), (void **) &ini)
							|| !getvalue(token(3), (void **) &fim));
			command = token(4);
		} else
		if (argc == 7) {
			syntax_fail = (!cmp("to", token(2))
							|| !getvalue(token(1), (void **) &ini)
							|| !getvalue(token(3), (void **) &fim)
							|| !cmp("step", token(4))
							|| !getvalue(token(5), (void **) &incremento));
			command = token(6);
		}
	}
	if (syntax_fail) {
		syntax_forloop();
		return;
	}


	{
		int delta = *fim-*ini + 1, i, val = *ini;
		void **list = MALLOC(delta, void *);

		for (i=0; val <= *fim; i++) {
			list[i] = reference(copyint(val), true);
			if (incremento != NULL) {
				val += *incremento;
			} else {
				val++;
			}
		}
		activate_trigger(command, list, i);
		free(list);
	}
}


void parse_repeat(char *argv[], int argc) {
	extern struct tokens	tokens;
	int 	*times;
	void	*backup;

	/* Possibilities:
		3 arguments
			repeat [times], [command]
	 */
	if (argc < 3) {
		syntax_repeat();
		return;
	}

	getvalue(token(1), (void **) &times);

	backup = tokens.list;
	tokens.list = tokens.list + 2 * sizeof(char *);
	tokens.count -= 2;
	while ((*times)--)
		parse_tokens();
	tokens.list = backup;
	tokens.count += 2;
}


void parse_new(char *argv[], int argc) {
	if (argc != 2) {
		syntax_new();
		return;
	}
	/// TODO: select object
	if (select_object(token(1))) {
		activate_trigger(token(0), NULL, 0);
	} else {
		error(_("Object %s%s%s not found. Type \"print objects\" "
				"to get a list of installed objects.\n"), CC_BOLD CC_BROWN,
				token(1), CC_RESTORE);
	}
}


void parse_push(char *argv[], int argc) {
	int		i, len = 0;
	void	*tmp, **data;

	if (argc == 1) {
		syntax_push();
		return;
	}
	data = MALLOC((argc - 1), void *);
	debug(3, "parse_push(%p, %d)\n", argv, argc);
	for (i=1; i<argc; i++) {
		debug(3, "  getvalue(token(%d), &tmp)\n", i);
		if (getvalue(token(i), &tmp)) {
			data[len] = tmp;
			len++;
		}
	}
	activate_trigger(token(0), data, len);
	free(data);
}


void parse_pop(char *argv[], int argc) {
	if (argc >= 2) {
		void	**list = MALLOC(argc - 1, void *);
		int		i;

		for (i=1; i<argc; i++) {
			size_t	len = strlen(token(i)) + 1;
			char	*data = MCALLOC((size_t) len);

			strcpy(data, token(i));
			list[i-1] = setreference(data, len * sizeof(char), true);
			/// TODO: Don't need to set reference in pop?
		}
		activate_trigger(token(0), list, argc - 1);
		free(list);
	} else {
		activate_trigger(token(0), NULL, 0);
	}
}


void parse_free(char *argv[], int argc) {
	if (argc == 1) {
		activate_trigger(token(0), NULL, 0);
	} else {
		char	*object_name = token(1);

		if (contains_object(object_name)) {
			char	*tmp;

			tmp = rtl.objects.list[rtl.current_obj]->name;
			select_object(object_name);
			activate_trigger(token(0), NULL, 0);
			select_object(tmp);
		} else {
			error(_("Object %s%s%s not found.\n"), CC_BOLD CC_BROWN,
					object_name, CC_RESTORE);
		}
	}
}
