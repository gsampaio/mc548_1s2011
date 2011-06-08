#include <stdio.h>
#include <stdlib.h>
#include "problem.h"
#include "solution.h"
#include "station.h"

static void
_usage(void)
{
    printf("Usage:\n"
           "./saveWord inst\n");
}

static void
_verify_problem(Problem *p)
{
    int *d1, *d2;
    Eina_List *n1, *n2;

    printf("N %d\n", p->n);
    printf("M %d\n", p->m);

    EINA_LIST_FOREACH(p->stations, n1, d1)
    {
        Station *s = (Station *)d1;
        printf("%s %.10f ", s->name, s->value);
        EINA_LIST_FOREACH(s->points, n2, d2)
            printf("%d ", *d2);
        printf("\n");
    }
}

static void
_print_solution(Solution *s) {
    /*TODO: testar*/
    int size;
    Eina_List * node;
    Station *station;

    size = eina_list_count(s->stations);
    printf("Valor: %lf\n", s->value);
    printf("Total: %d", size);

    EINA_LIST_FOREACH(s->stations, node, station)
        printf("%s\n", station->name);
}

int main(int argc, char *argv[])
{
    unsigned char r = 0;
    Problem p;

    if (argc != 2)
    {
        _usage();
        r = -1;
        goto _err;
    }

    if (!eina_init())
    {
        r = -2;
        goto _err;
    }

    problem_init(&p, argv[1]);

    problem_shutdown(&p);

    eina_shutdown();

_err:
    return r;
}
