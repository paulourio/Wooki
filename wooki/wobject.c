#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wooki.h>
#include "chewbacca.h"

/* Register a user-defined trigger */
void opcode(const void *object, const char *name, const ftrigger_t function,
            const int min, const int max) {
    wobject_i             *obj = (wobject_i *) object;
    struct user_trigger    *trg;

    if (obj->count + 1 == MAX_TRIGGERS) {
        debug(1, _("Can't register trigger for '%s'. No space left."), name);
        return;
    }
    trg = TALLOC(struct user_trigger);
    trg->opcode = (char *) name;
    trg->function = function;
    trg->minparam = min;
    trg->maxparam = max;
    obj->triggers[obj->count++] = trg;
    debug(3, _("Trigger registered (for object %s%s%s)\n\tOP Code: %s%s%s\n"
                "\tFunction: %s%p%s\n"), CC_BROWN, obj->name, CC_RESTORE,
        CC_BROWN, trg->opcode, CC_RESTORE, CC_BLUE, trg->function, CC_RESTORE);
}

static void say_object_not_found(const char *name) {
    error(_("Object %s%s%s not found.\n"), CC_BOLD CC_BROWN, name, CC_RESTORE);
}

static int    find_object(const char *name) {
    int    i;

    for (i=0; i<rtl.objects.count; i++)
        if (cmp(rtl.objects.list[i]->name, name))
            return (i);
    return (-1);
}


bool contains_object(const char *name) {
    return (find_object(name) != -1);
}


bool select_object(const char *name) {
    int    search;

    search = find_object(name);
    if (search != -1) {
        debug(3, _("Object found!\n"));
        rtl.current_obj = search;
    }
    return (search != -1);
}


void parse_select_object(char *argv[], int argc) {
    if (argc != 2) {
        syntax_sel();
        return;
    }
    if (!select_object(token(1))) {
        say_object_not_found(token(1));
    }
}


static int cmpobj(const void *a, const void *b) {
    return (strcmp(pvalue(a, wobject_i *)->class_name,
                    pvalue(b, wobject_i *)->class_name));
}

void print_object_list(void) {
    wobject_i    *    *list_copy;
    char            *current_class = NULL;
    int                i;

    out(_("There are %d objects. The list bellow show each object\n"
        "separated by class name.\n"), rtl.objects.count);
    list_copy = MALLOC(rtl.objects.count, wobject_i *);
    memcpy(list_copy, rtl.objects.list,
            ((size_t) rtl.objects.count) * sizeof(wobject_i *));
    qsort(list_copy, (size_t) rtl.objects.count, sizeof(wobject_i *), cmpobj);
    for (i=0; i < rtl.objects.count; i++) {
        if (current_class == NULL
            || !cmp(current_class, list_copy[i]->class_name)) {
            current_class = list_copy[i]->class_name;
            out(_("%sClass %s%s%s\n"), CC_BOLD CC_GREEN,
                CC_MAGENTA, current_class, CC_RESTORE);
        }
        out("\t%s\n", list_copy[i]->name);
    }
    free(list_copy);
}


bool print_object_info(const char *name) {
    wobject_i    *obj;
    int            i, index = find_object(name);

    if (index == -1) {
        say_object_not_found(name);
        return (false);
    }
    obj = rtl.objects.list[index];
    out("%s%s%s\n"
        "\t%s%s%s = %s (%s)\n"
        "\t%s%s%s = %s\n"
        "\t%s%s%s = %d\n",
        CC_BOLD CC_GREEN, _("Object information"), CC_RESTORE,
        CC_BOLD, _("Name"), CC_RESTORE, obj->name,
             obj->object != NULL? _("currently created")
                                : _("not created"),
        CC_BOLD, _("Class name"), CC_RESTORE, obj->class_name,
        CC_BOLD, _("Triggers"), CC_RESTORE, obj->count);
    // Print triggers
    for (i=0; i<obj->count; i++) {
        int    min = obj->triggers[i]->minparam;
        int max = obj->triggers[i]->maxparam;

        out("\t\t%s%s%s: ", CC_BOLD CC_BROWN, obj->triggers[i]->opcode, CC_RESTORE);
        if (min == max) {
            if (min == 0)
                out(_("takes no paramaters\n"));
            else if (min != NOLIMIT)
                out(_("takes %d parameters\n"), min);
            else
                out(_("no restriction for parameters count\n"));
        } else
        if ((min == NOLIMIT || min == 0) && max != NOLIMIT)
            out(_("takes up to %d %s\n"), max,
                max == 1? _("parameter"): _("parameters"));
        else if (max == NOLIMIT && min != NOLIMIT)
            out(_("takes at least %d %s\n"), min,
                    min == 1? _("parameter"): _("parameters"));
        else
            out(_("accepts from %d until %d parameters\n"), min, max);
    }
    return (true);
}


/* Return the pointer to the object struct */
void *new_object(const char *name, const char *classname) {
    wobject_i    *obj;

    if (contains_object(name) || (rtl.objects.count + 1) == MAX_OBJECTS) {
        /// FIXME: If max objects reached, will show the name message.
        error(_("Can't register object '%s'. It already exists.\n"), name);
        return (NULL);
    }
    obj = TALLOC(struct wobject);
    obj->name = (char *) name;
    obj->class_name = (char *) classname;
    obj->count = 0;
    obj->triggers = MALLOC(MAX_TRIGGERS, struct user_trigger *);
    rtl.objects.list[rtl.objects.count++] = obj;
    debug(2, _("New object: %s%s%s %s@%s %s%p%s\n"), CC_BROWN, name,
                CC_RESTORE,  CC_BOLD,CC_RESTORE,  CC_BLUE, obj, CC_RESTORE);
    return (obj);
}
