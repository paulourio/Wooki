
/* Ewok - Garbage Collector */
/*
    The intent is to make a list of reference counting data. When a new data
    is going to be used, reference() is called to check if there is a
    reference counting, if there is, increment, otherwise, create new reference.

    Example of memory map (integer numbers):

    Values:     | 1 | 4 | 2 | 3 | 9 | 2 |
    References: | 1 | 0 | 0 | 1 | 3 | 1 |

    When the garbage collector is executed, all garbage (zero references) will
    be removed from list.

    Result:     | 1 | 3 | 9 | 3 |
    References: | 1 | 1 | 3 | 1 |

    In addition, there are three levels of optimization:
        0 = No optmization
                Advantage: faster execution
                Disadvantage: lot of replicated data, therefore, a lot of memory.
        1 = Basic
                Advantage: no duplication data
                Disadvantage: slow algorithm to find references
        2 = Improved
                Advantage: sorted memory, fast location of references
                Disadvantage: very slow to new references
*/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../chewbacca.h"

typedef struct ewok_info {
    void    *data;              /* Pointer to data */
    size_t  size;               /* Size of data pointed */
    int     count;              /* Reference count */

    struct ewok_info   *next;   /* Pointer to next data info */
} ewok_info;

typedef struct {
    ewok_info   *front;
    int         count;          /* Reference count (list item count) */
} ewok_mem;

static ewok_mem     memory;


/* Insert a node in the front of the list */
__attribute__((__nonnull__(1)))
__attribute__((__warn_unused_result__))
static ewok_info *
new_reference(const void *data, const size_t size) {
    ewok_info   *node;

    node = TALLOC(ewok_info);
    assert(node != NULL);
    if (node == NULL)
        return (NULL);
    node->data = (void *) data;
    node->size = (size_t) size;
    node->count = 1;
    memory.front = (node->next = memory.front);
    memory.count++;
    return (node);
}


/* Increment reference count */
inline void *inc_reference(register void *ewok_reference) {
    ((ewok_info *) ewok_reference)->count++;
    return (ewok_reference);
}


/* Decremente reference count if count still not zero */
inline void *dec_reference(register void *ewok_reference) {
    ewok_info   *info = ((ewok_info *) ewok_reference);

    if (info->count != 0)
        info->count--;
    return (ewok_reference);
}


/* Remove from memory list itens with count that are equal to zero */
static void remove_garbage(void) {
    ewok_info   *prev = NULL, *current = memory.front;

    while (current) {
        if (current->count == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                /* When previous is null, means the front must be updated. */
                memory.front = current->next;
            }
            free(current->data);
            free(current);
            memory.count--;
            current = prev? prev->next: memory.front;
        } else {
            current = (prev = current)->next;
        }
    }
}


static void clear_memory(void) {
    ewok_info   *current = memory.front, *next;

    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    ewok_init();
}

/*
 * Register a reference for a given data pointer.
 * WITH MEMORY OPTIMIZATION
 *      Search for an existence node with same data content. If there is, return
 *      pointer to it, otherwise, create new reference to data.
 * NO OPTIMIZATION
 *      Create new reference and return its pointer.
 */
void *reference(const void *data, const size_t size) {
    struct ewok_info    *ref;
return (data);
    if (rtl.optimize_memory) {
        ref = memory.front;
        while (ref != NULL) {
            if (ref->size == size
                && memcmp(ref->data, data, size) == 0) {
                /* Found same memory content. Return reference */
                debug(3, _("Found reference of %p @ %p!\n"), data, ref->data);
                ref->count++;
                return (ref);
            }
            ref = ref->next;
        }
        /* If optimize memory and data wasn't found, append data. */
        debug(3, _("No reference was found. Creating:\n"));
    }
    return (new_reference(data, size));
}


void ewok_init(void) {
    memory.front = NULL;
    memory.count = 0;
}
