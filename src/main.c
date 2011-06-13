#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "point.h"
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
    _print_solution(p.solution);
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
_remove_covered_points(Eina_List *points, Station *s)
{
    Eina_List *l;
    int *d;
    unsigned int covered = 0;

    EINA_LIST_FOREACH(s->points, l, d)
    {
        if (eina_list_data_find(points, d))
        {
            s->points = eina_list_remove(s->points, l);
            covered++;
        }
    }

    return covered;
}

static unsigned int
_insert_covered_points(Eina_List *points, Eina_List *sol_s, Station *s)
{
    Eina_List *l;
    int *d, inserted = 0;

    EINA_LIST_FOREACH(s->points, l, d)
    {
        Eina_Bool insert = EINA_TRUE;
        Eina_List *ll;
        Station *dd;
        EINA_LIST_FOREACH(sol_s, ll, dd)
        {
            if (s == dd)
                continue;

            if (eina_list_data_find(dd->points, d))
            {
                insert = EINA_FALSE;
                break;
            }
        }

        if (!insert)
            continue;

        points = eina_list_sorted_insert(points, point_cmp, d);
        inserted++;
    }

    return inserted;
}

static void
_create_random_solution(Problem *p, Eina_List *stations)
{
    int covered_points = 0;

    while (covered_points < p->n)
    {
        unsigned int points;
        Station *st = station_random_get(stations);

        points = _remove_covered_points(p->solution->points_to_cover, st);

        if (points > 0)
        {
            covered_points += points;
            solution_station_insert(p->solution, st);
            stations = eina_list_remove(stations, st);
        }
    }
}

static Solution *
_solution_clone(Problem *p, Solution *solution)
{
    solution->value = p->solution->value;
    solution->stations = eina_list_clone(p->solution->stations);
    solution->points_to_cover = eina_list_clone(p->points);

    return solution;
}

static void
_local_search(Problem *p, Eina_List *stations)
{
    int counter;
    Solution solution;

    _solution_clone(p, &solution);

    for (counter = 0; counter < sqrt(p->n); counter++)
    {
        int covered_points = 0;
        Station *s_old, *s_new;
        int solution_stations_len = eina_list_count(solution.stations);

        s_old = eina_list_nth(solution.stations, solution_stations_len - 1);
        _insert_covered_points(
                solution.points_to_cover, solution.stations, s_old);
        solution_station_remove(&solution, s_old);
        stations = eina_list_sorted_insert(stations, station_cmp, s_old);

        Eina_List *tested_stations = NULL;

        do
        {
            unsigned int points;
            s_new = eina_list_nth(stations, 0);
            if (!s_new)
                printf("fudeu\n");
            points = _remove_covered_points(solution.points_to_cover, s_new);

            if (points > 0)
            {
                covered_points += points;
                solution_station_insert(&solution, s_new);
            }
            else
                tested_stations = eina_list_append(tested_stations, s_new);

            stations = eina_list_remove(stations, s_new);

        } while (covered_points < p->n);

        {
            Eina_List *l, *l_next;
            Station *d;
            EINA_LIST_FOREACH_SAFE(tested_stations, l, l_next, d)
            {
                stations = eina_list_sorted_insert(stations, station_cmp, l);
                tested_stations = eina_list_remove(tested_stations, l);
            }
        }

        p->solution = solution_compare(p->solution, &solution);
    }
}

static void
_solve_problem(void)
{
    Eina_List *stations = station_available_list_init(p.stations);
    //loop
    _create_random_solution(&p, stations);
    _local_search(&p, stations);
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
    _solve_problem();
    _shutdown();

    return 0;
}
