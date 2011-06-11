#include <stdio.h> /*FIXME: remover ao remover o printf */
#include "point.h"
#include "solution.h"

/*****************
 * API FUNCTIONS *
 *****************/
Solution *
solution_init(int points)
{
    Solution *s = malloc(sizeof(Solution));
    s->value = 0;
    s->stations = NULL;
    s->points_to_cover = point_available_list_init(points);

    return s;
}

Solution *
solution_compare(Solution *s1, Solution *s2)
{
    if (s1->value >= s2->value)
        return s1;
    return s2;
}

Station *
solution_worst_station_get(Solution *solution)
{
    Eina_List *l, *l_next;
    Station *worst, *d;

    EINA_LIST_FOREACH_SAFE(solution->stations, l, l_next, d)
    {
        if (l_next)
        {
            Station *d_next;
            if (d->score > d_next->score)
                worst = d;
            else if (d->score < d_next->score)
                worst = d_next;
            else
            {
                if (eina_list_count(d->points) >=
                        eina_list_count(d_next->points))
                    worst = d_next;
                else
                    worst = d;
            }
        }
        else
            if (worst->score < d->score)
                worst = d;
    }
    return worst;
}

void
solution_update(Solution *solution, Station *old, Station *new)
{
    solution->stations = eina_list_remove(solution->stations, old);
    solution->value -= old->value;

    solution->stations = eina_list_append(solution->stations, new);
    solution->value += new->value;
}
