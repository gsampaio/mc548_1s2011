#include <stdlib.h>
#include <Eina.h>
#include "save_word.h"

Solution* compare_solution(Solution*s1, Solution*s2) {
    if (s1->value == s2->value)
        return s1;
    else if (s1->value > s2->value)
        return s1;
    else
        return s2;
}


