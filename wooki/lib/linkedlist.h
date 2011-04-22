/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Authors:    Paulo Urio (December 2010)
 *             Ygor Mutti (December 2010)
 */
#ifndef    LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

struct ln_list_node {
    void                *value;
    struct ln_list_node    *next;
};

typedef struct ln_list_node    ln_list_node;
typedef ln_list_node        *ln_list;

typedef int (*fcmpl_t)(void *, void *);

/* Function list */
void ln_list_init(ln_list *list);

bool ln_list_is_end(const ln_list *list);
bool ln_list_is_empty(const ln_list *list);
int ln_list_count(const ln_list *list);

void *ln_list_append(ln_list *list, void *value);
void *ln_list_insert_first(ln_list *list, void *value);
void ln_list_insert_sorted(ln_list *list, void *value, fcmpl_t compare);
void ln_list_concat(ln_list *a, ln_list *b);

void ln_list_del_first_node(ln_list *list);
void ln_list_del_last_node(ln_list *list);
void ln_list_clear(ln_list *list, bool free_content);
void *ln_list_back(const ln_list *list);

#endif /* LINKEDLIST_H */
