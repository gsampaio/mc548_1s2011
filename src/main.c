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
    int i = 0, j = 0, begin = 0, counter = 0;

    s->points = NULL;

    for (; i < strlen(line); i++)
    {
        if (line[i] == ' ')
        {
            int len = i - begin;
            char buffer[len + 1], buff;
            strncpy(buffer, &line[begin], len);
            buffer[len] = '\0';

            switch (counter)
            {
                case 0:
                    {
                        s->name = malloc(len);
                        strcpy(s->name, buffer);
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
                        j++;
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

    Station s[p->m];
    for(i = 0; i <= p->m; i++)
    {
        char buffer[MAX_SIZE];
        char *endline, del = '\n';
        int len;

        fgets(buffer, MAX_SIZE, inst);
        if (buffer[0] != 'S')
            continue;

        station_init(&s[i], buffer);

        p->stations = eina_list_append(p->stations, &s[i]);
    }

    fclose(inst);
}

static void
verify_problem(Problem *p)
{
    int i, *d1, *d2;
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

    verify_problem(&p);

    eina_shutdown();

_err:
    return r;
}