#include <stdio.h>
#include <stdlib.h>
#include "save_world.h"

static void
_usage(void)
{
    printf("Usage:\n"
           "./saveWord inst\n");
}

static void
station_init(Station *s, const char *line)
{
    unsigned int i = 0, begin = 0, counter = 0;

    s->points = NULL;

    for (; i < strlen(line); i++)
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
                    {
                        int *point = malloc(sizeof(int));
                        *point = atoi(buffer);
                        s->points = eina_list_append(s->points, point);
                        break;
                    }
            }
            begin = i + 1;
            counter++;
        }
    }
}

static void
problem_init(Problem *p, const char *inst_name)
{
    FILE *inst = fopen(inst_name, "r");
    int i;

    p->stations = NULL;

    fscanf(inst, "%*s %d %*s %d", &p->n, &p->m);

    for(i = 0; i <= p->m; i++)
    {
        Station *s = malloc(sizeof(Station));
        char buffer[MAX_SIZE];

        fgets(buffer, MAX_SIZE, inst);
        if (buffer[0] != 'S')
            continue;

        station_init(s, buffer);

        p->stations = eina_list_append(p->stations, s);
    }

    fclose(inst);
}

static void
problem_shutdown(Problem *p)
{
    int *d1, *d2;
    Eina_List *l1, *l2, *l1_next, *l2_next;

    EINA_LIST_FOREACH_SAFE(p->stations, l1, l1_next, d1)
    {
        Station *s = (Station *)d1;
        EINA_LIST_FOREACH_SAFE(s->points, l2, l2_next, d2)
        {
            s->points = eina_list_remove(s->points, l2);
            free(d2);
        }
        free(s->name);
        free(s);
        p->stations = eina_list_remove(p->stations, l1);

    }
}

static void
verify_problem(Problem *p)
{
    int *d1, *d2;
    Eina_List *n1, *n2;

    printf("N %d\n", p->n);
    printf("M %d\n", p->m);

    EINA_LIST_FOREACH(p->stations, n1, d1)
    {
        Station *s = (Station *)d1;
        printf("%s %.10f ", s->name, s->value);
        EINA_LIST_FOREACH(s->points, n2, d2)
            printf("%d ", *d2);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    unsigned char r = 0;
    Problem p;

    if (argc != 2)
    {
        _usage();
        r = -1;
        goto _err;
    }

    if (!eina_init())
    {
        r = -2;
        goto _err;
    }

    problem_init(&p, argv[1]);

    problem_shutdown(&p);

    eina_shutdown();

_err:
    return r;
}
