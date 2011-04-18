#include <stdio.h>
#include <string.h>
#include <wooki.h>
#include "chewbacca.h"
#include <malloc.h> /* memory info */

void print_memsize(const int data) {
	if (data < 1048576)
		out(" (%.2f KB)\n", ((float) data) / 1024);
	else
		out(" (%.2f MB)\n", ((float) data) / 1048576);
}

void meminfo(void) {
	struct mallinfo info = mallinfo();

	out(_("%sMemory Info%s\n"), CC_BOLD, CC_RESTORE);
	out(_("\t%sTotal bytes allocated%s: %i bytes "),
		CC_BOLD, CC_RESTORE, info.arena);
	print_memsize(info.arena);
	out(_("\t%sChunks not being used%s: %i\n"),
		CC_BOLD, CC_RESTORE, info.ordblks);
	out(_("\t%sNumber of chunks allocated with mmap%s: %i\n"),
		CC_BOLD, CC_RESTORE, info.hblks);
	out(_("\t%sSize of chunks allocated with mmap%s: %i bytes"),
		CC_BOLD, CC_RESTORE, info.hblkhd);
	print_memsize(info.hblkhd);
	out(_("\t%sTotal allocated with malloc%s: %i bytes"),
		CC_BOLD, CC_RESTORE, info.uordblks);
	print_memsize(info.uordblks);
	out(_("\t%sTotal memory not in use%s: %i bytes"),
		CC_BOLD, CC_RESTORE, info.fordblks);
	print_memsize(info.fordblks);
	out(_("\t%sTop-most releasable chunk size%s: %i bytes\n"),
		CC_BOLD, CC_RESTORE, info.keepcost);
}


void show_help(char *argv[], int argc) {
	extern struct parser	parsers; 					/* from parser.c */
	char					opcodes_list[1000] = "";
	char					opc[MAX_WORD_LEN];
	size_t 					i;

	if (argc == 2) {
		/* Was received help word. Show help for word. */
		for (i=0; i<parsers.count; i++) {
			if (cmp(token(1), parsers.list[i].opcode)) {
				if (parsers.list[i].helper != NULL) {
					parsers.list[i].helper();
					return;
				} else {
					break;
				}
			}
		}
		error(_("No help for %s\n"), token(1));
		return;
	}
	/* Build the list of parsers and show. */
	for (i=0; i<parsers.count; i++) {
		strcpy(opc, parsers.list[i].opcode);
		if (parsers.list[i].helper != NULL) {
			if (i != 0)
				strcat(opcodes_list, ", ");
			strcat(opcodes_list, opc);
		}
	}
	out(_("%sWooki Interpreter Help%s\n"
			"\tWooki interpreter is a program to help in analysis of "
			"data structures, with tools for benchmarking and debug. "
			"The data structures are compiled with the interpreter, and "
			"they are connect to the interpreter throught an interface. "
			"To see all interfaces (objects), type \"print objects\"\n"
			"\tTo start using an object, first you need to create an object "
			"and then commands for the structure can be passed.\n"
			"How to use help\n"
			"\tType \"help\" and the item you want to see about, for instance:\n"
			"\t\thelp new  -- Show help information for \"new\" command.\n"),
		CC_BOLD, CC_RESTORE);
	out(_("%sOpcodes%s: %s\n"), CC_BOLD CC_BROWN, CC_RESTORE, opcodes_list);
	//out(_("Object %s%s%s opcodes: "));
}


void show_copyright(void) {
	out(_("Copyright (c) 2011 Chewbacca Software Foundation.\n"
		"All Rights Reserved.\n\n"));
	out(_("Copyright (c) 2011 Paulo Roberto Urio.\n"
		"All Rights Reserved.\n"));
}


void show_license(void) {
	out(_("This work is licensed under the Creative Commons "
		"Attribution-NonCommercial 3.0 Unported License. To view a copy of "
		"this license, visit http://creativecommons.org/licenses/by-nc/3.0/ "
		"or send a letter to Creative Commons, 171 Second Street, Suite 300, "
		"San Francisco, California, 94105, USA.\n"

		"%sYou are free%s:\n"
		"\t%sto Share%s — to copy, distribute and transmit the work\n"
		"\t%sto Remix%s — to adapt the work\n"

		"%sUnder the following conditions%s:\n"
		"\t%sAttribution%s — You must attribute the work in the manner \n"
							"\t\tspecified by the author or licensor (but \n"
							"\t\tnot in any way that suggests that they endorse \n"
							"\t\tyou or your use of the work).\n"
		"\t%sNoncommercial%s — You may not use this work for commercial purposes.\n"

		"%sWith the understanding that%s:\n"
		"\t%sWaiver%s — Any of the above conditions can be waived if you get \n"
						"\t\tpermission from the copyright holder. \n"
		"\t%sPublic Domain%s — Where the work or any of its elements is in \n"
						"\t\tthe public domain under applicable law, that \n"
						"\t\tstatus is in no way affected by the license. \n"

		"\t%sOther Rights%s — In no way are any of the following rights \n"
							"\t\taffected by the license: \n"
		"\t◉ Your fair dealing or fair use rights, or other applicable\n"
							"\t\tcopyright exceptions and limitations;\n"
		"\t◉ The author's moral rights;\n"
		"\t◉ Rights other persons may have either in the work itself or in \n"
							"\t\thow the work is used, such as publicity or \n"
							"\t\tprivacy rights.\n"
		"%sNotice%s — This is a human-readable summary of the Legal Code.\n"
							"\tCheck out the full license in the web site.\n"),
		CC_BOLD CC_BROWN, CC_RESTORE,
		CC_BOLD, CC_RESTORE, CC_BOLD, CC_RESTORE,
		CC_BOLD CC_BROWN, CC_RESTORE,
		CC_BOLD, CC_RESTORE, CC_BOLD, CC_RESTORE,
		CC_BOLD CC_BROWN, CC_RESTORE,
		CC_BOLD, CC_RESTORE, CC_BOLD, CC_RESTORE, CC_BOLD, CC_RESTORE,
		CC_BOLD CC_BROWN, CC_RESTORE
		);
}
