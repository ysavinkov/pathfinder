#include "../inc/pathfinder.h"

char *mx_read_str(char *file, int n, bool *end) {
    char c;
    int f = open(file, O_RDONLY);
    int len = 0;
    for (int i = 1; i < n; i++) {
        read(f, &c, 1);
        while (c != '\n') {
            read(f, &c, 1);
        }
    }
    int info = read(f, &c, 1);
    while (info > 0) {
        if (c == '\n') {
            break;
        }
        info = read(f, &c, 1);
        len++;
    }
    if (read(f, &c, 1) <= 0) {
        *end = true;
    }
    close(f);
    char *result = mx_strnew(len);
    f = open(file, O_RDONLY);
    len = 0;
    for (int i = 1; i < n; i++) {
        read(f, &c, 1);
        while (c != '\n') {
            read(f, &c, 1);
        }
    }
    read(f, &c, 1);
    while (c != '\n') {
        result[len] = c;
        len++;
        int info = read(f, &c, 1);
        if (info <= 0) {
            break;
        }
    }
    close(f);
    return result;
}

void print_results(t_island *islands, int *map, int count_of_islands) {
    for (int from = 0; from < count_of_islands; from++) {
        for (int to = from + 1; to < count_of_islands; to++) {

            char *info_route = mx_strnew(59 + (mx_strlen(islands[from].name) * 2) + mx_strlen(islands[to].name));
            mx_strcpy(info_route, "========================================\nPath: ");
            mx_strcat(info_route, islands[from].name);
            mx_strcat(info_route, " -> ");
            mx_strcat(info_route, islands[to].name);
            mx_strcat(info_route, "\nRoute: ");
            mx_strcat(info_route, islands[from].name);
            char *info_dist = mx_strnew(11);
            mx_strcpy(info_dist, "\nDistance: ");

            dijkstra(to, islands, (int*)map, count_of_islands);

            t_data data;
            data.count_of_islands = count_of_islands;
            data.from = from;
            data.to = to;
            data.sum = islands[from].length;
            info_route = pathfinder(info_route, info_dist, islands, (int*)map, data);
            mx_printstr(info_route);
            mx_strdel(&info_route);
        }
    }
    mx_del_islands(islands, count_of_islands);
}

int mx_atoi_special(const char *string, int length) {
    if (string == 0)
        return -1;
    int result = 0;
    for (int a = 0; a < length ; a++) {
        if ((string[a] >= 48) && (string[a] <= 57)) {
            result *= 10;
            if (result % 10 != 0) {
                return -1;
            }
            result += (int)string[a] - 48;
        }
        else {
            return -1;
        }
    }
    return result;
}

bool mx_is_wrong(char *string) {
    bool delim1 = false;
    for (int i = 0; i < mx_strlen(string); i++) {
        if (!(((string[i] >= 65) && (string[i] <= 90)) 
            || ((string[i] >= 97) && (string[i] <= 122)))) {
            if ((!delim1) && string[i] == '-') {
                delim1 = true;
            }
            else if (string[i] == ',') {
                return false;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

void mx_printerr_int(int n) {
	int num[30];
	int length = 0;
	char c;
	if (n < 0) write(2, "-", 1);
	else if (n == 0) write(2, "0", 1);
	while (n != 0) {
		if (n % 10 < 0) 
			num[length] = -(n % 10);
		else 
			num[length] = n % 10;
		length++;
		n /= 10;
	}
    for(int i = length - 1; i >= 0; i--) {
		c = 48 + num[i];
        write(2, &c, 1);
	}
}

void mx_line_err(int line) {
    mx_printerr("error: line ");
    mx_printerr_int(line);
    mx_printerr(" is not valid\n");
}

void mx_del_islands(t_island *islands, int count_of_islands) {
    for (int i = 0; i < count_of_islands; i++)
		mx_strdel(&(islands[i].name));
}

void mx_del_array(char **array) {
    for (int i = 0; array[i] != NULL; i++)
		mx_strdel(&array[i]);
}

