#include "save_word.h"

Solution *
solution_compare(Solution *s1, Solution *s2)
{
    if (s1->value >= s2->value)
        return s1;
    return s2;
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
    solution = eina_list_append(station);
}

Station *
station_random_get(Eina_List *stations)
{
    Station *s;
    int r = srand(time(NULL)) % eina_list_count(stations);
    s = eina_list_nth(stations, r);

    return s;
}

Eina_List *
available_points_init(int size)
{
    Eina_List *available_points = NULL;
    int i;

    for(i = 1; i <= size; i++)
    {
        int *d = malloc(sizeof(int));
        *d = i;

        available_points = eina_list_append(available_points, d)
    }

    return available_points;
}
