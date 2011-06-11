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
solution_update(Solution *solution, Eina_List *points, Eina_List *stations, Station *station)
{
    Eina_List *l1;
    int *d1;

    EINA_LIST_FOREACH(station->points, l1, d1)
    {
        Eina_List *l2, *l2_next;
        int *d2;
        EINA_LIST_FOREACH_SAFE(points, l2, l2_next, d2)
        {
            if (*d1 == *d2)
            {
                /*FIXME: retirar esse check depois de testar*/
                if (d1 == d2)
                    printf("Fuuuudeu\n");
                points = eina_list_remove(points, d2);
                free(d2);
            }
        }
    }

    stations = eina_list_remove(stations, station);
    solution->stations = eina_list_append(solution->stations, station);
}
