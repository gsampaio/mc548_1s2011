#include <stdlib.h>
#include <string.h>
#include "point.h"


/*****************
 * API FUNCTIONS *
 *****************/
int
point_cmp(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;

    return *ia - *ib;
}

Eina_List *
point_list_init_from_file(const char *line, Eina_List *all_points)
{
    Eina_List *points = NULL;
    unsigned int i = 0, begin = 0;

    for (; i < strlen(line); i++)
    {
        if (line[i] == ' ')
        {
            int point_value, *point;
            int len = i - begin;
            char buffer[len + 1];
            strncpy(buffer, &line[begin], len);
            buffer[len] = '\0';

            point_value = atoi(buffer);
            point = eina_list_nth(all_points, point_value - 1);
            points = eina_list_sorted_insert(points, point_cmp, point);

            begin = i + 1;
        }
    }
    return points;
}

void
point_list_shutdown(Eina_List *points)
{
    int *d;

    EINA_LIST_FREE(points, d)
        free(d);
}

Eina_List *
point_available_list_init(int points)
{
    Eina_List *available_points = NULL;
    int i;

    for(i = 1; i <= points; i++)
    {
        int *d = malloc(sizeof(int));
        *d = i;

        available_points = eina_list_append(available_points, d);
    }

    return available_points;
}
