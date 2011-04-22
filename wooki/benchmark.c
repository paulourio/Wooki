#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <malloc.h>
#include "chewbacca.h"

#define    MAX_BENCHMARKS    (10)
#define NOT_FOUND        (-1)

struct benchmark_data {
    char        name[MAX_WORD_LEN];
    int         allocated;
    clock_t     clock;
    time_t      time;
};

struct benchmark {
    struct benchmark_data   **list;    /* Benchmark list */
    int                     count;
} bm;


static int find_benchmark(const char *name) {
    int i;

    for (i=0; i<bm.count; i++)
        if (bm.list[i]->name != NULL)
            if (cmp(name, bm.list[i]->name))
                return (i);
    return (NOT_FOUND);
}


static void benchmark_save(const char *name) {
    struct mallinfo info;
    int             i;

    i = find_benchmark(name);
    if (i == NOT_FOUND) {
        if (bm.count == MAX_BENCHMARKS) {
            error(_("Reached maximum of benchmarks\n"));
            return;
        }
        i = bm.count++;
        {
            struct benchmark_data    *nbm;

            nbm = TALLOC(struct benchmark_data);
            bm.list[i] = nbm;
            strcpy(bm.list[i]->name, name);
        }
    }
    info = mallinfo();
    bm.list[i]->clock = clock();
    bm.list[i]->allocated = info.uordblks;
    bm.list[i]->time = time(NULL);
}


static void benchmark_compare(const char *a, const char *b) {
    int bma = find_benchmark(a);
    int bmb = find_benchmark(b);
    int data = bm.list[bmb]->allocated - bm.list[bma]->allocated;

    out(_("Clock: %d\n"), (int)(bm.list[bmb]->clock - bm.list[bma]->clock));
    out(_("Time: %lf\n"), difftime(bm.list[bmb]->time, bm.list[bma]->time));
    out(_("Memory: %i bytes"), data);
    print_memsize(data);
}


static void benchmark_clear(void) {
    //memset(bm.list, 0, MAX_BENCHMARKS * sizeof(struct benchmark_data));
    bm.count = 0;
}

void syntax_benchmark(void) { syntax("bm", "[operation] ([value])"); }

void help_benchmark(void) {
    out(_("Benchmark Tool\n"));
}

void parse_benchmark(char *argv[], int argc) {
    if (argc == 1) {
        syntax_benchmark();
        return;
    }
    {
        char    *cmd = token(1);

        if (cmp("save", cmd)) {
            if (argc != 3) {
                out(_("Missing name for benchmark. (ex: bm save bma)\n"));
                syntax_benchmark();
                return;
            }
            benchmark_save(token(2));
        } else
        if (cmp("compare", cmd)) {
            if (argc != 4) {
                out(_("Missing name for benchmark. (ex: bm compare a b)\n"));
                syntax_benchmark();
                return;
            }
            benchmark_compare(token(2), token(3));
        } else
        if (cmp("clear", cmd)) {
            benchmark_clear();
        } else {
            out("huh?\n");
        }
    }
}


__attribute__((__constructor__ (103)))
static void construct_benchmark(void) {
    bm.list = MALLOC(MAX_BENCHMARKS, struct benchmark_data *);
    assert(bm.list != NULL);
    benchmark_clear();
}

__attribute__((__destructor__ (103)))
static void destruct_benchmark(void) {
    free(bm.list);
}
