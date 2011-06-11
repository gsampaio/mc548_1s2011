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

Solution *solution_init(int points);
void solution_shutdown(Solution *solution);
Solution *solution_compare(Solution *s1, Solution *s2);
void solution_update(Solution *solution, Station *old, Station *new);
Station *solution_worst_station_get(Solution *solution);
void solution_station_insert(Solution *solution, Station *station);

#endif /* SOLUTION_H__ */
