#include "stack.h"
#include <wooki.h>
//static void push(const struct trigger_info *info)

static void intf_stack_new(const struct trigger_info *info) {
	info->object = stack_new();
}

static void intf_stack_free(const struct trigger_info *info) {
	stack_free(info->object, false);
}

static void intf_stack_push(const struct trigger_info *info) {
	stack_push(info->object, info->list);
}

static void intf_stack_pop(const struct trigger_info *info) {
	void *data;

	data = stack_pop(info->object, info->list);
	printf("data = %p\n", data);
}

void install_stack(char *id) {
	void *st;

	st = new_object(id);
	opcode(st, "new", intf_stack_new, 0, 0);
	opcode(st, "free", intf_stack_free, 0, 0);
	opcode(st, "push", intf_stack_push, 1, 1);
	opcode(st, "pop", intf_stack_pop, 1, 1);
}
