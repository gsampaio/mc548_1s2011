#ifndef POINT_H__
#define POINT_H__

#include <Eina.h>

Eina_List *point_list_init_from_file(const char *line, Eina_List *all_points);
void point_list_shutdown(Eina_List *points);
Eina_List *point_available_list_init(int points);
int point_cmp(const void *a, const void *b);

#endif /* POINT_H__ */
