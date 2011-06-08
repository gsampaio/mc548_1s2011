#ifndef SOLUTION_H__
#define SOLUTION_H__

#include <Eina.h>
#include "station.h"

typedef struct _Solution Solution;
struct _Solution {
    double value;
    Eina_List *stations;
};

Solution *solution_compare(Solution *s1, Solution *s2);
void solution_update(Solution *solution, Eina_List *points, Eina_List *stations, Station *station);

#endif /* SOLUTION_H__ */
