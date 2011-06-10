#include <stdio.h>
#include <Eina.h>
#include "problem.h"
#include "station.h"


int main(__attribute__((unused)) int argc, char* argv[]) {

    Problem p;
    Eina_List *stations;
    int i;

    eina_init();
    problem_init(&p, argv[1]);

    stations = eina_list_clone(p.stations);
    printf("STATION RANDOM GET TEST:\n");
    for (i = 0; i < 5; i++) {
        Station *random = station_random_get(stations);
        printf("\tVALUE=%.10lf, SCORE=%.10lf\n", random->value, random->score);
    }


    problem_shutdown(&p);
    eina_shutdown();
    return 0;
}
