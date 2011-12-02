/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Author: Paulo Roberto Urio (March 2011)
 */
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

stack stack_new(void) {
    stack    st;

    st = (stack) malloc(sizeof(struct stack));
    assert(st != NULL);
    st->top = NULL;
    return (st);
}


void stack_free(stack s, bool free_content) {
    void    *toFree;

    while (!stack_isempty(s)) {
        toFree = stack_pop(s);
        if (free_content)
            free(toFree);
    }
    free(s);
}


inline
bool stack_isempty(const stack s) {
    return (s->top? false: true);
}


inline
void *stack_top(const stack s) {
    if (stack_isempty(s))
        return (NULL);
    return (s->top->data);
}


bool stack_push(const stack s, const void *data) {
    struct st_node    *node;

    node = (st_node *) malloc(sizeof(struct st_node));
    if (node == NULL)
        return (false);
    node->data = (void *) data;
    node->next = s->top;
    s->top = node;
    return (true);
}


void *stack_pop(const stack s) {
    void    *toRet;
    st_node    *Top;

    if (stack_isempty(s))
        return (NULL);    /* underflow */
    Top = s->top;
    toRet = Top->data;
    s->top = Top->next;
    free(Top);
    return (toRet);
}
