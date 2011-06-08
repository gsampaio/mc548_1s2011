#ifndef POINT_H__
#define POINT_H__

#include <Eina.h>

Eina_List *point_list_init(const char *line);
void point_list_shutdown(Eina_List *points);
Eina_List *point_available_list_init(int size);

#endif /* POINT_H__ */
