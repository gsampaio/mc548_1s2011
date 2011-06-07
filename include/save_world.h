#ifndef SAVE_WORLD_H__
#define SAVE_WORLD_H__

#include <Eina.h>

#define MAX_SIZE    4096

typedef struct _Problem Problem;
struct _Problem
{
    int n, m;
    Eina_List *stations;
};

typedef struct _Station Station;
struct _Station
{
    char *name;
    double value;
    Eina_List *points;
};

#endif /* SAVE_WORLD_H__ */
