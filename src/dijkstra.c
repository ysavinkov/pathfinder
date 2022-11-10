#include "../inc/pathfinder.h"

void dijkstra(int start, t_island *islands, int *map, int count_of_islands) {
    bool block[count_of_islands];
    for (int i = 0; i < count_of_islands; i++) {
        islands[i].length = INFINITY;
        block[i] = false;
    }
    islands[start].length = 0;
    int current = start;
    for (int a = 0; a < count_of_islands; a++) {
        block[current] = true;
        for (int i = 0; i < count_of_islands; i++) {
            if (map[current * count_of_islands + i] != -1) {
                if (islands[i].length > map[current * count_of_islands + i] + islands[current].length && !block[i]) {
                    islands[i].length = map[current * count_of_islands + i] + islands[current].length;
                }
            }
        }
        int min = INFINITY;
        for (int i = 0; i < count_of_islands; i++) {
            if (islands[i].length < min && !block[i]) {
                current = i;
                min = islands[i].length;
            }
        }
    }
}
