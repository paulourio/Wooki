#include <stdlib.h>
#include <wooki.h>
#include "stack/stack_intf.h"

int main(void) {
	//set_interactive(false);
	install_stack("pilha");
	install_stack("Pilha_2");
	execute();
	return (EXIT_SUCCESS);
}
