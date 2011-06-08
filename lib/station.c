#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "point.h"
#include "station.h"

/**********************
 * INTERNAL FUNCTIONS *
 **********************/
void
_station_init(Station *s, const char *line)
{
    unsigned int i = 0, begin = 0, counter = 0;

    while (counter < 2)
    {
        if (line[i] == ' ')
        {
            int len = i - begin;
            char buffer[len + 1];
            strncpy(buffer, &line[begin], len);
            buffer[len] = '\0';

            switch (counter)
            {
                case 0:
                    {
                        s->name = strdup(buffer);
                        break;
                    }
                case 1:
                    {
                        s->value = atof(buffer);
                        break;
                    }
                default:
                    break;
            }
            begin = i + 1;
            counter++;
        }
        i++;
    }

    s->points = point_list_init(&line[i]);
    s->score = 0;
}

static void
_station_shutdown(Station *s)
{
    point_list_shutdown(s->points);
    free(s->name);
    free(s);
}


/*****************
 * API FUNCTIONS *
 *****************/
Eina_List *
station_list_init(int station_list_len, FILE *inst)
{
    int i;
    Eina_List *stations = NULL;

    for(i = 0; i <= station_list_len; i++)
    {
        Station *s;
        char buffer[MAX_SIZE];

        fgets(buffer, MAX_SIZE, inst);
        if (buffer[0] != 'S')
            continue;

        s = malloc(sizeof(Station));
        _station_init(s, buffer);

        stations = eina_list_append(stations, s);
    }
    return stations;
}

void
station_list_shutdown(Eina_List *stations)
{
    int *d;
    Eina_List *l, *l_next;

    EINA_LIST_FOREACH_SAFE(stations, l, l_next, d)
    {
        Station *s = (Station *)d;
        _station_shutdown(s);
        stations = eina_list_remove(stations, l);
    }
    eina_list_free(stations);
}

Eina_List *
station_available_list_init(Eina_List *stations)
{
    Eina_List *available_stations = eina_list_clone(stations);
    return available_stations;
}

Station *
station_random_get(Eina_List *stations)
{
    Station *s;
    srand(time(NULL));

    int r = rand() % eina_list_count(stations);
    s = eina_list_nth(stations, r);

    return s;
}
