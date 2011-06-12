#include <stdio.h>
#include "point.h"
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

    p->points = point_available_list_init(p->n);
    p->stations = station_list_init(p->m, inst, p->points);
    p->solution = solution_init(p->points);

    fclose(inst);
}

void
problem_shutdown(Problem *p)
{
    point_list_shutdown(p->points);
    station_list_shutdown(p->stations);
    free(p->solution);
}
