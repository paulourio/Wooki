#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "chewbacca.h"
#include "runtime.h"


void print_ewok(void) {
    out("%sEwok%s\n", CC_BOLD CC_BROWN, CC_RESTORE);
    out("\t%s: %s%s%s\n", _("Memory Optimization"), CC_BOLD,
        rtl.optimize_memory? _("activated"): _("deactivated"), CC_RESTORE);
    out("\t%s: %s%s%s\n", _("Safe working"), CC_BOLD,
         rtl.safe_working? _("activated"): _("deactivated"), CC_RESTORE);
    out("\t%s: %s%s%s\n", _("Data type"), CC_BOLD, typetostr(), CC_RESTORE);
    out("\t%s: %s%d%s\n", _("Items in cache"), CC_BOLD,
        ln_list_count(&rtl.allocated_data), CC_RESTORE);
}

void print_registers(void) {
    out("\teax = %p\n\tebx = %p\n\tecx = %p\n\tedx = %p\n",
        rtl.registers.eax, NULL, NULL, NULL);
}


__attribute__((__constructor__ (102)))
static void initialization(void) {
    debug(3, _("Initializing runtime..\n"));
    rtl.objects.list = MALLOC(MAX_OBJECTS, struct wobject *);
    assert(rtl.objects.list != NULL);
    rtl.current_obj = NO_SELECTED_OBJECT;
    rtl.type = DEFAULT_TYPE;
    rtl.fixed_type = false;
    rtl.registers.eax = NULL;
    rtl.optimize_memory = DEFAULT_MEM_OPTIMIZATION;
    rtl.interactive_input  = DEFAULT_INTERACTIVE;
    rtl.safe_working = true;
    /* Objects */
    rtl.objects.count = 0;
    /* Alocated data */
    ln_list_init(&rtl.allocated_data);
}


__attribute__((__destructor__ (102)))
static void finalization(void) {
    debug(3, _("Finalizing runtime..\n"));
    ln_list_clear(&rtl.allocated_data, true);
    if (rtl.objects.count)
        while (rtl.objects.count--) {
            wobject_i    *ob = rtl.objects.list[rtl.objects.count];
            int            i = ob->count;
            if (i)
                while (i--)
                    free(rtl.objects.list[rtl.objects.count]->triggers[i]);
            free(ob);
        }
    free(rtl.objects.list);
}
