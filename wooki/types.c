#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "chewbacca.h"

bool getvalue(char *input, void **output) {
	switch (rtl.type) {
		case INTEGER: {
			int	*data = TALLOC(int);
			debug(3, _("\tNew integer @ %p\n"), data);
			if (sscanf(input, "%i", data) == 0) {
				debug(1, _("Warning: can't read integer.\n"));
				free(data);
				return (false);
			}
			*output = data;
			break;
		}
		case INT64: {
			long long int	*data = TALLOC(long long int);
			if (sscanf(input, "%Li", data) == 0) {
				free(data);
				return (false);
			}
			*output = data;
			break;
		}
		case CHAR: {
			char	*data = TALLOC(char);
			if (sscanf(input, "%c", data) == 0) {
				free(data);
				return (false);
			}
			*output = data;
			break;
		}
		case BOOL: { /// TODO: Test boolean reading
			int		b;
			bool	*data;
			if (sscanf(input, "%1d", &b) == 0)
				return (false);
			data = TALLOC(bool);
			*data = b;
			*output = data;
			break;
		}
		case FLOAT: {
			float	*data = TALLOC(float);
			if (sscanf(input, "%f", data) == 0) {
				free(data);
				return (false);
			}
			*output = data;
			break;
		}
		case DOUBLE: {
			double	*data = TALLOC(double);
			if (sscanf(input, "%lf", data) == 0) {
				free(data);
				return (false);
			}
			*output = data;
			break;
		}
		default:
			error(_("Type not defined!\n"));
			return (false);
	}
	debug(3, _("\tRead with success: %d\n"), *(int*)*output);
	*output = reference(*output, true);
	return (true);
}


void fix_type(void) {
	rtl.fixed_type = true;
}


bool settype(char *value) {
	if (rtl.fixed_type) {
		out(_("Can't set type. It is fixed.\n"));
		return (false);
	}

	if (cmp(value, "int"))
		rtl.type = INTEGER;
	else if (cmp(value, "int64"))
		rtl.type = INT64;
	else if (cmp(value, "char"))
		rtl.type = CHAR;
	else if (cmp(value, "float"))
		rtl.type = FLOAT;
	else if (cmp(value, "double"))
		rtl.type = DOUBLE;
	else if (cmp(value, "bool"))
		rtl.type = BOOL;
	else
		return (false);
	return (true);
}


size_t getsizeof(int type) {
	switch (type) {
		case INTEGER:	return (sizeof(int));
		case INT64: 	return (sizeof(long long int));
		case CHAR: 		return (sizeof(char));
		case BOOL: 		return (sizeof(bool));
		case FLOAT:		return (sizeof(float));
		case DOUBLE:	return (sizeof(double));
		default:		return (0);
	}
}


char *typetostr(void) {
	switch (rtl.type) {
		case INTEGER:	return ("integer");
		case INT64: 	return ("int64");
		case CHAR: 		return ("char");
		case BOOL: 		return ("bool");
		case FLOAT:		return ("float");
		case DOUBLE:	return ("double");
		default:
			return (NULL);
	}
}
