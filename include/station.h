#ifndef STATION_H__
#define STATION_H__

#include <Eina.h>

#define MAX_SIZE    4096

typedef struct _Station Station;
struct _Station
{
    char *name;
    double value;
    double score;
    Eina_List *points;
};

Eina_List *station_list_init(int station_list_len, FILE *inst, Eina_List *points);
void station_list_shutdown(Eina_List *stations);
Eina_List *station_available_list_init(Eina_List *stations);
Station *station_random_get(Eina_List *stations);
int station_cmp(const void *d1, const void *d2);

#endif /* STATION_H__ */
