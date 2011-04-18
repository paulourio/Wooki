#ifndef RUNTIME_INCLUDE
#define RUNTIME_INCLUDE

#include <stdlib.h>
#include <stdbool.h>
#include "lib/linkedlist.h"

/* Included by chewbacca.h */

struct user_trigger {
	char		*opcode;		/* Opcode name */
	ftrigger_t	function;		/* Pointer to the trigger */
	int			minparam;		/* Minimum required parameters count */
	int			maxparam;		/* Maximum allowed parameters */
};


/* Wooki Object */
struct wobject {
	char				*name;
	char				*class_name;
	void				*object;		/* Pointer to the user data structure */
	struct user_trigger	**triggers;
	int					count;
};

typedef struct wobject	wobject_i;


struct wobject_list {
	wobject_i	**list;
	int			count;
};

typedef	struct wobject_list		wobjects_t;


struct registers {
	void	*eax;
	//void	*ebx;
	//void	*ecx;
	//void	*edx;
};


struct data_reference {
	void	*ptr;	/* Pointer to allocated data */
	size_t	size;	/* Size of data */
	//size_t	ref_count; /* Not used. reference count for garbage collector */
};

struct runtime {
	wobjects_t			objects;		/* List of objects */
	signed int			current_obj;	/* Index of current wobject_i */
	int					type;			/* Type for data values */
	bool				fixed_type;		/* Stores if the type can be changed */
	struct registers	registers;
	ln_list				allocated_data;
	bool				optimize_memory;	/* See reference() */
	unsigned int		debuglevel;
	bool				interactive_input;
	bool				safe_working;	/* Don't call triggers when object	*/
										/* has null value 					*/
};


void print_ewok(void);
void print_registers(void);
bool print_object_info(const char *name) __attribute__((__nonnull__));

#endif /* RUNTIME_INCLUDE */
