#include <stdio.h>
#include <Eina.h>
#include "problem.h"

int main(__attribute__((unused)) int argc, char* argv[]) {
    eina_init();

    Problem p;
    problem_init(&p, argv[1]);

    printf("SOLUTION INIT START\n");
    Solution *s = solution_init(p.n);
    Solution *s2 = solution_init(p.n-1);
    printf("SOLUTION INIT FINISHED");

    printf("SOLUCAO IGUAL %d", (solution_compare(s,s2) == s));


    Station* station = eina_list_nth(s->stations, p.n-1);
    Station* station2 = eina_list_nth(s->stations, p.n-2);

    solution_update(s, station, station2);

    problem_shutdown(&p);
    eina_shutdown();
    return 0;
}
