#ifndef PROBLEM_H__
#define PROBLEM_H__

#include <Eina.h>
#include "solution.h"

typedef struct _Problem Problem;
struct _Problem
{
    int n, m;
    Eina_List *points;
    Eina_List *stations;
    Solution *solution;
};

void problem_init(Problem *p, const char *inst_name);
void problem_shutdown(Problem *p);

#endif /* PROBLEM_H__ */
