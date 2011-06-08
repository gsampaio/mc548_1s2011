#include <stdio.h>
#include "problem.h"
#include "station.h"

void
problem_init(Problem *p, const char *inst_name)
{
    FILE *inst = fopen(inst_name, "r");

    fscanf(inst, "%*s %d %*s %d", &p->n, &p->m);

    p->stations = station_list_init(p->m, inst);

    fclose(inst);
}

void
problem_shutdown(Problem *p)
{
    station_list_shutdown(p->stations);
}
