#ifndef SOLUTION_H__
#define SOLUTION_H__

#include <Eina.h>
#include "station.h"

typedef struct _Solution Solution;
struct _Solution {
    double value;
    Eina_List *stations;
    Eina_List *points_to_cover;
};

Solution *solution_init(Eina_List *points);
Solution *solution_compare(Solution *s1, Solution *s2);
Station *solution_worst_station_get(Solution *solution);
void solution_station_insert(Solution *solution, Station *station);
void solution_station_remove(Solution *solution, Station *station);

#endif /* SOLUTION_H__ */
