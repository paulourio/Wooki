
/* Tokenizer a line before call parsers */

#include <stdbool.h>
#include "chewbacca.h"

typedef struct {
    char    *str;    /* String data */
    size_t    length;    /* length of the string */
    int        type;    /* Token type */
    /* Conversions */
    char    *aschar;
    int        *asint;
    float    *asfloat;
//    int64_t    *asint64;
    double    *asdouble;
} token_info;

typedef struct {
    token_info    *start;
    size_t        count;
} token_list;

#define is_potential_identifier_start(c) (\
              (c >= 'a' && c <= 'z')\
               || (c >= 'A' && c <= 'Z')\
               || c == '_'\
               || (c >= 128))

#define is_potential_identifier_char(c) (\
              (c >= 'a' && c <= 'z')\
               || (c >= 'A' && c <= 'Z')\
               || (c >= '0' && c <= '9')\
               || c == '_'\
               || (c >= 128))

/*static int gettokentype(const char *tok) {
    //if (tok[0] == '%')//
    return 0;//remove this
}*/
