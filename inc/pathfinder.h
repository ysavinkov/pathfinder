#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

#define INFINITY 2147483647

//structures:
typedef struct s_island {
    char *name;
    int length;
}              t_island;

typedef struct s_data {
    int from;
    int to;
    int sum;
    int count_of_islands;
}              t_data;

//pathfinder:
int count_of_islands_validator(int argc, char *argv[]);
void map_validator(char *file, t_island *islands, int *map, int count_of_islands);
void dijkstra(int start, t_island *islands, int *map, int count_of_islands);
int get_current_index(char *string);
char *pathfinder(char *PR, char *D, t_island *islands, int *map, t_data data);

//utilities:
void print_results(t_island *islands, int *map, int count_of_islands);
char *mx_read_str(char *file, int n, bool *end);
void mx_del_islands(t_island *islands, int count_of_islands);
int mx_atoi_special(const char *string, int length);
void mx_line_err(int line);
bool mx_is_wrong(char *string);
void mx_del_array(char **array);
void mx_printerr_int(int n);

#endif
