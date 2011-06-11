#include <stdio.h>
#include "problem.h"
#include "station.h"
#include "solution.h"

/*****************
 * API FUNCTIONS *
 *****************/
void
problem_init(Problem *p, const char *inst_name)
{
    FILE *inst = fopen(inst_name, "r");
    if (!inst)
    {
        printf("filename: \"%s\" is invalid!\n", inst_name);
        exit(-1);
    }

    fscanf(inst, "%*s %d %*s %d", &p->n, &p->m);

    p->stations = station_list_init(p->m, inst);
    p->solution = solution_init(p->n);

    fclose(inst);
}

void
problem_shutdown(Problem *p)
{
    station_list_shutdown(p->stations);
    solution_shutdown(p->solution);
    free(p->solution);
}
