#include "save_word.h"

Solution *
solution_compare(Solution *s1, Solution *s2)
{
    if (s1->value >= s2->value)
        return s1;
    return s2;
}

Station *
station_random_get(Eina_List *stations)
{
    Station *s;
    int r = srand(time(NULL)) % eina_list_count(stations);
    s = eina_list_nth(stations, r);

    return s;
}
