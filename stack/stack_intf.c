#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "stack_intf.h"
#include <wooki.h>

static void intf_stack_new(struct trigger_info *info) {
    info->object = stack_new();
    out(_("\tNew stack allocated at %s%p%s\n"), CC_BROWN,
        info->object, CC_RESTORE);
}

static void intf_stack_free(struct trigger_info *info) {
    stack_free(info->object, true); /// TODO: Tirar o true
    info->object = NULL;
    out(_("\tStack freed.\n"));
}

static void intf_stack_push(struct trigger_info *info) {
    int     i;

    for (i=0; i < info->list_num; i++) {
        stack_push(info->object, info->list[i]);
    }
}

static void intf_stack_pop(struct trigger_info *info) {
    void    *data;
    bool    all = (info->list_num == 1 && cmp("all", info->list[0]));

    do {
        data = stack_pop(info->object);
        if (data) {
            out(_("%d\n"), pvalue(data, int));
            free(data);
        } else if (!all)
            printf(_("\tStack is empty\n"));
    } while (all && data);
}

void install_stack(char *id) {
    void *st;

    st = new_object(id, "stack");
    opcode(st, "new", intf_stack_new, 0, 0);
    opcode(st, "free", intf_stack_free, 0, 0);
    opcode(st, "push", intf_stack_push, 1, NOLIMIT);
    opcode(st, "pop", intf_stack_pop, 0, 1);
}
