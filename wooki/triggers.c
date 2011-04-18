/*
 * Manage user trigger
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <wooki.h>
#include "chewbacca.h"

#define	TRNOT_FOUND	(-1)

static int find_trigger(const char *name) {
	wobject_i	*obj = rtl.objects.list[rtl.current_obj];
	int			i;

	for (i=0; i<(int) obj->count; i++)
		if (cmp(name, obj->triggers[i]->opcode))
			if (obj->triggers[i]->function != NULL)
				return (i);
	return (TRNOT_FOUND);
}

void activate_trigger(const char *name, void **list, const int num) {\
	struct trigger_info		*info;
	struct user_trigger		*tr;
	wobject_i				*obj;
	int						index;

	debug(3 , _("activate_trigger(\"%s\", %p, %u)\n"), name, list, num);
	if (rtl.current_obj == NO_SELECTED_OBJECT) {
		error(_("You must select a object before use commands.\n"));
		return;
	}
	index = find_trigger(name);
	if (index == TRNOT_FOUND) {
		debug(2, _("Trigger not found.\n"));
		return;
	}
	obj = rtl.objects.list[rtl.current_obj];
	if (obj->object == NULL && !cmp("new", name)) {
		if (!rtl.safe_working)
			out(_("%s%sWarning%s: object is null!\n"), CC_BOLD,
					CC_RED, CC_RESTORE);
		else {
			error(_("%s%sError%s: operation blocked by safe_working. "
					"(object is null)\n"), CC_BOLD,
					CC_RED, CC_RESTORE);
			return;
		}
	}
	tr = obj->triggers[index];
	if (tr->minparam != NOLIMIT && num < tr->minparam) {
		debug(2, _("Skipping trigger: number of parameteres do not"
					" reach minimum allowed.\n"));
		return;
	}
	if (tr->maxparam != NOLIMIT && num > tr->maxparam) {
		debug(2, _("Skipping trigger: number of parameteres ultrapass"
					" maximum allowed.\n"));
		return;
	}
	info = TALLOC(struct trigger_info);
	assert(info != NULL);
	info->debug_level = rtl.debuglevel;
	info->item_size = getsizeof(rtl.type);
	info->list = list;
	info->list_num = (size_t) num;
	info->opcode = (char *) name;
	info->object = obj->object;


	debug(3, _("Calling user trigger..\n"));
	tr->function(info);

	if (info->object != obj->object) {
		debug(3, _("\tUpdating object pointer from %p to %p\n"),
					obj->object, info->object);
		obj->object = info->object;
	}
	free(info);
}
