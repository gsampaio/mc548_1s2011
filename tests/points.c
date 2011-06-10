#include <stdio.h>
#include <Eina.h>
#include "point.h"

int main() {
    eina_init();

    Eina_List* node;
    int *data;
    Eina_List* points = point_available_list_init(10);

    printf("POINTS AVAIABLE LIST INIT: \n");
    EINA_LIST_FOREACH(points, node, data) {
        printf("\tPOINT: %d\n", *data);
    }

    eina_shutdown();
    return 0;
}
