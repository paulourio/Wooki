#ifndef EWOK_H_INCLUDED
#define EWOK_H_INCLUDED

void ewok_init(void);

void *reference(const void *data, const size_t size);

void *inc_reference(register void *ewok_reference) __attribute__((__nonnull__));
void *dec_reference(register void *ewok_reference) __attribute__((__nonnull__));

#endif /* EWOK_H_INCLUDED */
