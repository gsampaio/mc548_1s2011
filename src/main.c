#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "problem.h"
#include "solution.h"
#include "station.h"

/***************
 * GLOBAL VARS *
 ***************/
Problem p;


/*******************************
 * INTERNAL FUNCTIONS' PRAGMAS *
 *******************************/
static void _usage(void);
static void _verify_problem(Problem *p);
static void _print_solution(Solution *s);
static void _init(const char *file);
static void _shutdown(void);
static void _alarm_handler (__attribute__((unused)) int sig);


/**************************************
 * INTERNAL FUNCTIONS' IMPLEMENTATION *
 **************************************/
static void
_usage(void)
{
    printf("Usage:\n"
           "./saveWord inst\n");
}

static void
_verify_problem(Problem *p)
{
    int *d1, *d2;
    Eina_List *n1, *n2;

    printf("N %d\n"
           "M %d\n",
           p->n, p->m);

    EINA_LIST_FOREACH(p->stations, n1, d1)
    {
        Station *s = (Station *)d1;
        printf("%s %.10f ", s->name, s->value);
        EINA_LIST_FOREACH(s->points, n2, d2)
            printf("%d ", *d2);
        printf("\n");
    }
}

static void
_print_solution(Solution *s)
{
    /*TODO: testar*/
    int size;
    Eina_List *node;
    Station *station;

    size = eina_list_count(s->stations);
    printf("Valor: %lf\n"
           "Total: %d\n",
            s->value, size);

    EINA_LIST_FOREACH(s->stations, node, station)
        printf("%s\n", station->name);
}

static void
_init(const char *file)
{
    if (!eina_init())
        exit(-1);

    srand(time(NULL));
    problem_init(&p, file);
    signal(SIGALRM, _alarm_handler);
    alarm(56);
}

static void
_shutdown()
{
    problem_shutdown(&p);
    eina_shutdown();
    exit(0);
}

static void
_alarm_handler(__attribute__((unused)) int sig)
{
    _shutdown();
}

static unsigned int
_update_covered_points(Eina_List *points, Station *s)
{
    Eina_List *l;
    int *d;
    unsigned int covered = 0;

    EINA_LIST_FOREACH(s->points, l, d)
    {
        Eina_List *ll, *ll_next;
        int *dd = NULL;
        EINA_LIST_FOREACH_SAFE(points, ll, ll_next, dd)
            if (*d == *dd)
            {
                points = eina_list_remove(points, ll);
                covered++;
            }
    }

    return covered;
}

static void
_create_random_solution(void)
{
    Eina_List *stations = station_available_list_init(p.stations);
    int covered_points = 0;

    while (covered_points < p.n)
    {
        printf("p.n - covered_points: %d\n", p.n - covered_points);
        unsigned int points;
        printf("stations_len: %d\n", eina_list_count(stations));
        Station *st = station_random_get(stations);
        printf("station name: %s\n", st->name);
        points = _update_covered_points(p.solution->points_to_cover, st);

        if (points > 0)
        {
            covered_points += points;
            solution_station_insert(p.solution, st);
        }
    }
    _print_solution(p.solution);
}


/********
 * MAIN *
 ********/
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        _usage();
        return -1;
    }

    _init(argv[1]);
//    _verify_problem(&p);
    _create_random_solution();
    _shutdown();

    return 0;
}
