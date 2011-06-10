#include <stdio.h>
#include <stdlib.h>
#include <Eina.h>
#include "problem.h"

int main(__attribute__((unused)) int argc, char* argv[]) {
    Problem p;
    eina_init();

    printf("INIT - PROBLEM TEST\n");
    problem_init(&p, argv[1]);

    problem_shutdown(&p);
    printf("END - PROBLEM TEST OKAY\n");

    eina_shutdown();
    return 0;
}
