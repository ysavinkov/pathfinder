#include "../inc/pathfinder.h"

int get_current_index(char *string) {
    int length = 0;
    for (int i = 0; i < mx_strlen(string); i++) {
        if (string[i] == '\n') {
            length++;
        }
    }
    if (length == 1) return 0;
    for (int i = 0; i < mx_strlen(string); i++) {
        if (string[i] == '\n') {
            length--;
            if (length == 2) {
                return i + 1;
            }
        }
    }
    return 0;
}

char *pathfinder(char *route, char *dist, t_island *islands, int *map, t_data data) {
    if (data.from == data.to) {
        int cnbr = data.sum;
        int length;
        for (length = 0; cnbr > 0; length++)
            cnbr /= 10;
        cnbr = data.sum;
        char sum[length + 1];
        sum[length] = '\0';
        for (int a = 1; cnbr > 0; a++) {
            sum[length - a] = cnbr % 10 + 48;
            cnbr /= 10;
        }
        char *new_route;
        new_route = mx_strnew(mx_strlen(route) + mx_strlen(dist) + length + 42);
        mx_strcpy(new_route, route);
        mx_strcat(new_route, dist);
        mx_strcat(new_route, sum);
        mx_strcat(new_route, "\n========================================\n");
        mx_strdel(&route);
        mx_strdel(&dist);
        return new_route;
    }
    char *old_route = mx_strdup(&(route[get_current_index(route)]));

    bool first_iter = true;
    for (int i = 0; i < data.count_of_islands; i++) {
        
        if (islands[data.from].length - islands[i].length == 
            map[data.from * data.count_of_islands + i]
            && map[data.from * data.count_of_islands + i] != -1) {
            if (!first_iter) {
                char *buf_PR = mx_strjoin(route, old_route);
                mx_strdel(&route);
                route = buf_PR;
            }
            char *new_route;
            new_route = mx_strnew(4 + mx_strlen(islands[i].name) + mx_strlen(route));
            mx_strcpy(new_route, route);
            mx_strcat(new_route, " -> ");
            mx_strcat(new_route, islands[i].name);
            mx_strdel(&route);

            int cnbr = map[data.from * data.count_of_islands + i];
            int length;
            for (length = 0; cnbr > 0; length++)
                cnbr /= 10;
            cnbr = map[data.from * data.count_of_islands + i];
            char bridge[length + 1];
            bridge[length] = '\0';
            for (int a = 1; cnbr > 0; a++) {
                bridge[length - a] = cnbr % 10 + 48;
                cnbr /= 10;
            }
            char *new_dest;
            if (i == data.to && data.sum == islands[data.from].length) {
                new_dest = mx_strdup(dist);
            }
            else {
                new_dest = mx_strnew(3 + length + mx_strlen(dist));
                mx_strcpy(new_dest, dist);
                mx_strcat(new_dest, bridge);
                if (i == data.to)
                    mx_strcat(new_dest, " = ");
                else
                    mx_strcat(new_dest, " + ");
            }
            t_data new_data;
            new_data.sum = data.sum;
            new_data.count_of_islands = data.count_of_islands;
            new_data.from = i;
            new_data.to = data.to;
            route = pathfinder(new_route, new_dest, islands, map, new_data);
            first_iter = false;
        }
    }
    mx_strdel(&old_route);
    mx_strdel(&dist);
    return route;
}
