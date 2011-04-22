/* This work is licensed under the Creative Commons Attribution-Noncommercial
 * 3.0 Brazil License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc/3.0/br/deed.en
 * or send a letter to Creative Commons, 171 Second Street, Suite 300,
 * San Francisco, California, 94105, USA.
 *
 * Authors:    Paulo Urio (December 2010)
 *             Ygor Mutti (December 2010)
 */
#include <linkedlist.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* TODO : Create library documentation */

static ln_list ln_list_get_last_node(const ln_list *list) {
    if (list != NULL) {
        ln_list cur = *list;

        while (!ln_list_is_end(&cur))
            cur = cur->next;
        return (cur);
    }
    return (NULL);
}


void *ln_list_back(const ln_list *list){
    ln_list node;

    return    (((node = ln_list_get_last_node(list)) != NULL)
            ? node->value
            : NULL);
}


bool ln_list_is_end(const ln_list *list) {
    return (list != NULL && (*list)->next == NULL);
}


void ln_list_init(ln_list *list){
    *list = NULL;
}


bool ln_list_is_empty(const ln_list *list) {
    return (list == NULL || (*list) == NULL);
}


int ln_list_count(const ln_list *list) {
    int    cnt = 0;

    if (list != NULL) {
        ln_list cur = *list;

        while (cur && !ln_list_is_end(&cur)) {
            cur = cur->next;
            cnt++;
        }
    }
    return (cnt);
}


void *ln_list_append(ln_list *list, void *value) {
    ln_list    temp;

    if (ln_list_is_empty(list)) { /* Empty list, set as first node */
        *list = (ln_list) malloc(sizeof(ln_list_node));
        assert(*list != NULL);
        temp = *list;
    } else { /* Set as last node */
        temp = ln_list_get_last_node(list);
        temp->next = (ln_list) malloc(sizeof(ln_list_node));
        assert(temp->next != NULL);
        temp = temp->next;
    }
    temp->value = value;
    temp->next = NULL;
    return (temp);
}


void *ln_list_insert_first(ln_list *list, void *value) {
    ln_list    temp;

    temp = (ln_list) malloc(sizeof(ln_list_node));
    assert(temp != NULL);
    temp->value = value;
    temp->next = *list;
    *list = temp;
    return (*list);
}


/// TODO: Check function for bug
void ln_list_insert_sorted(ln_list *list, void *value, fcmpl_t compare) {
    ln_list    temp, previous, newn;

    if (ln_list_is_empty(list)) {
        ln_list_append(list, value);
        return;
    }
    temp = *list;
    previous = NULL;
    while (temp) {
        if (compare(value, temp->value) > 0) {
            /* Insert before this node. */
            if (previous == NULL) {
                ln_list_insert_first(list, value);
                return;
            }
            newn = (ln_list) malloc(sizeof(ln_list_node));
            assert(newn != NULL);
            previous->next = newn;
            newn->value = value;
            newn->next = temp;
        } else
            temp = (previous = temp)->next;
    }
}


void ln_list_concat(ln_list *a, ln_list *b) {
    if (a != NULL && b != NULL) {
        ln_list    temp;

        temp = ln_list_get_last_node(a);
        (*a)->next = *b;
    }
}


void ln_list_del_first_node(ln_list *list) {
    ln_list    temp = *list;

    if (ln_list_is_empty(list))
        return;
    *list = temp->next;
    free(temp);
}


void ln_list_del_last_node(ln_list *list) {
    ln_list    cur, prev = NULL;

    if (ln_list_is_empty(list))
        return;
    cur = *list;
    while (!ln_list_is_end(&cur)) { /* Get the last two nodes */
        prev = cur;
        cur = cur->next;
    }
    free(cur);                        /* Kill last node */
    prev->next = NULL;                /* Clear any evidence */
}


void ln_list_clear(ln_list *list, bool free_content) {
    ln_list    temp;

    if (ln_list_is_empty(list))
        return;
    while (!ln_list_is_end(list)) {
        temp = *list;
        if (free_content)
            free(temp->value);
        *list = temp->next;
        free(temp);
    }
    if (free_content)
        free((*list)->value);
    free(*list);
    *list = NULL;
}
