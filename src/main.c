#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    int count_of_islands = count_of_islands_validator(argc, argv);

    int map[count_of_islands * count_of_islands];
    t_island islands[count_of_islands];
    
    map_validator(argv[1], islands, (int*)map, count_of_islands);

    print_results(islands, (int*)map, count_of_islands);
    return 0;
}
