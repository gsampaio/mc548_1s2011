#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "point.h"
#include "station.h"

/**********************
 * INTERNAL FUNCTIONS *
 **********************/
void
_station_init(Station *s, const char *line, Eina_List *points)
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

    s->points = point_list_init_from_file(&line[i], points);
    s->score = s->value/eina_list_count(s->points);
}

static void
_station_shutdown(Station *s)
{
    point_list_shutdown(s->points);
    free(s->name);
    free(s);
}

static int
_score_cmp(const void *d1, const void *d2)
{
    const Station *s1 = d1;
    const Station *s2 = d2;
    double epsilon = 0.000000000000001;

    if (s1->score - s2->score > epsilon)
        return 1;
    else if (s1->score - s2->score < epsilon)
        return -1;

    return 0;
}


/*****************
 * API FUNCTIONS *
 *****************/
Eina_List *
station_list_init(int station_list_len, FILE *inst, Eina_List *points)
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
        _station_init(s, buffer, points);

        stations = eina_list_append(stations, s);
    }
    return stations;
}

void
station_list_shutdown(Eina_List *stations)
{
    Station *s;

    EINA_LIST_FREE(stations, s)
        _station_shutdown(s);
}

Eina_List *
station_available_list_init(Eina_List *stations)
{
    Eina_List *available_stations = eina_list_clone(stations);
    available_stations = eina_list_sort(available_stations,
                                        eina_list_count(available_stations),
                                        _score_cmp);
    return available_stations;
}

Station *
station_random_get(Eina_List *stations)
{
    Station *s;

    int r = rand() % eina_list_count(stations);
    s = eina_list_nth(stations, r);
    stations = eina_list_remove(stations, s);

    return s;
}
