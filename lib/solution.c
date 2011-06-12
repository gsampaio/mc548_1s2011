#include <stdio.h> /*FIXME: remover ao remover o printf */
#include "point.h"
#include "solution.h"

/**********************
 * INTERNAL FUNCTIONS *
 **********************/
static int
_station_cmp(const void *d1, const void *d2)
{
    Station *s1 = (Station *)d1;
    Station *s2 = (Station *)d2;

    if (s1->score < s2->score)
        return -1;
    else
        return 1;
}

/*****************
 * API FUNCTIONS *
 *****************/
Solution *
solution_init(Eina_List *points)
{
    Solution *s = malloc(sizeof(Solution));
    s->value = 0;
    s->stations = NULL;
    s->points_to_cover = eina_list_clone(points);

    return s;
}

Solution *
solution_compare(Solution *s1, Solution *s2)
{
    if (s1->value >= s2->value)
        return s1;
    return s2;
}

void
solution_update(Solution *solution, Station *old, Station *new)
{
    solution->stations = eina_list_remove(solution->stations, old);
    solution->value -= old->value;

    solution->stations =
        eina_list_sorted_insert(solution->stations, _station_cmp, new);
    solution->value += new->value;
}

void
solution_station_insert(Solution *solution, Station *station)
{
    solution->value += station->value;
    solution->stations =
        eina_list_sorted_insert(solution->stations, _station_cmp, station);
}
