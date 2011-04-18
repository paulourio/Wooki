#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "chewbacca.h"
#include "runtime.h"


/* Reference a pointer
 * Parameters
 *		data:	Pointer do data to be referenced.
 *		can_free: on memory optimization, if true, the memory of data
 8				  is freed if a reference to same already exists.
 * Result
 *		pointer:	Pointer to data referenced.
 * NOTE
 *		If memory optimization is activated, same memory content will be
 *	searched in the cache (allocated_data), and if a pointer to same content
 *  is found, the pointer to it will be returned.
 */
void *setreference(void *data, size_t data_size, bool can_free) {
	struct data_reference	*ref;

	if (rtl.optimize_memory) {
		ln_list	node;

		node = rtl.allocated_data;
		while (node) { /// TODO: Optimization not tested.
			ref = node->value;
			if (ref->size == data_size
				&& memcmp(ref->ptr, data, data_size) == 0) {
				struct data_reference	*temp;
				/* Found same memory content. Return reference */
				debug(3, _("Found reference of %p @ %p!\n"), data, node->value);
				temp = ((struct data_reference *) node->value);
				//temp->count++;
				if (can_free) {
					//debug(3, _("Freeing data @ %p\n"), data);
					free(data);
				}
				return (temp->ptr);
			}
			node = node->next;
		}
		/* If optimize memory and data wasn't found, append data. */
		debug(3, _("No reference was found. Creating:\n"));
	}
	/* Create new reference */
	ref = TALLOC(struct data_reference);
	assert(ref != NULL);
	ref->ptr = data;
	ref->size = data_size;
	ln_list_insert_first(&rtl.allocated_data, ref);
	debug(3, _f("\tReference: %s%p (int %i)\n"), CC_BLUE, data, pvalue(data, int));
	return (data);
}

/* Get data size from RTL */
void *reference(void *data, bool can_free) {
	return (setreference(data, getsizeof(rtl.type), can_free));
}


void garbage_collector_naive(void) {
	ln_list_clear(&rtl.allocated_data, true);
}


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
			wobject_i	*ob = rtl.objects.list[rtl.objects.count];
			int			i = ob->count;
			if (i)
				while (i--)
					free(rtl.objects.list[rtl.objects.count]->triggers[i]);
			free(ob);
		}
	free(rtl.objects.list);
}
