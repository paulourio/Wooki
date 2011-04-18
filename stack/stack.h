/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#ifndef STACK_H_INCLUDE
#define STACK_H_INCLUDE

#include <stdbool.h>

struct st_node {
	void			*data;
	struct st_node	*next;
};

typedef	struct st_node	st_node;

struct stack {
	st_node	*top;
};

typedef	struct stack *	stack;

stack stack_new(void);
void stack_free(const stack s, const bool free_content);

extern bool stack_isempty(const stack s) __attribute__((__always_inline__));
extern void *stack_top(const stack s) __attribute__((__always_inline__));

bool stack_push(const stack s, const void *data);
void *stack_pop(const stack s) __attribute__((__warn_unused_result__));

#endif /* STACK_H_INCLUDE */
