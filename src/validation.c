#include "../inc/pathfinder.h"

int count_of_islands_validator(int argc, char *argv[]) {
    if (argc != 2){
		mx_printerr("usage: ./pathfinder [filename]\n");
		exit(0);
	}
    int f = open(argv[1], O_RDONLY);
    if (f < 0) {
        close(f);
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
		exit(0);
    }
    int result = 0;
    int len = 0;
    int len_digits = 0;
    bool digits = true;
    char c;
    int info = read(f, &c, 1);
    while (info > 0) {
        if (digits) {
            if (c == '\n') {
                digits = false;
            } else {
                len_digits++;
            }
        }
        info = read(f, &c, 1);
        len++;
    }
    close(f);
    if (len == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
		exit(0);
    }
    if (len_digits == 0) {
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }

    f = open(argv[1], O_RDONLY);
    char str[len_digits];
    read(f, str, len_digits);
    close(f);

    result = mx_atoi_special(str, len_digits);
    if (result < 0) {
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }
    return result;
}

void map_validator(char *file, t_island *islands, int *map, int count_of_islands) {
    int sum_bridges = 0;
    int line = 2;
    bool end = false;
    char *names[count_of_islands + 1];
    for (int i = 0; i <= count_of_islands; i++) {
        names[i] = NULL;
    }
    for (int i = 0; i < count_of_islands * count_of_islands; i++) {
        map[i] = -1;
    }
    
    int empty = 0;
    while (!end) {
        char *str = mx_read_str(file, line, &end);
        int name1_len = mx_get_char_index(str, '-');
        int name2_len = mx_get_char_index(str, ',');
        name2_len -= name1_len + 1;
        if (name1_len < 1 || name2_len < 1 || mx_is_wrong(str)
            || mx_strncmp(&(str[name1_len + 1]), str, name1_len) == 0) {
            mx_line_err(line);
            mx_strdel(&str);
            mx_del_array((char**)names);
            exit(0);
        }
        
        bool nothing = true;
        for (int i = 0; i < count_of_islands; i++) {
            if (names[i] != NULL) {
                if (mx_strncmp(str, names[i], name1_len) == 0) {
                    nothing = false;
                    break;
                }
            }
        }
        if (nothing) {
            if (empty < count_of_islands) {
                names[empty] = mx_strndup(str, name1_len);
                empty ++;
            }
            else {
                mx_printerr("error: invalid number of islands\n");
                mx_strdel(&str);
                mx_del_array((char**)names);
                exit(0);
            }
        }
        
        nothing = true;
        for (int i = 0; i < count_of_islands; i++) {
            if (names[i] != NULL) {
                if (mx_strncmp(&(str[name1_len + 1]), names[i], name2_len) == 0) {
                    nothing = false;
                    break;
                }
            }
        }
        if (nothing) {
            if (empty < count_of_islands) {
                names[empty] = mx_strndup(&(str[name1_len + 1]), name2_len);
                empty ++;
            }
            else {
                mx_printerr("error: invalid number of islands\n");
                mx_strdel(&str);
                mx_del_array((char**)names);
                exit(0);
            }
        }
        mx_strdel(&str);
        line++;
    }
    if (names[count_of_islands - 1] == NULL) {
        mx_printerr("error: invalid number of islands\n");
        mx_del_array((char**)names);
        exit(0);
    }

    
    for (int i = 0; i < count_of_islands; i++) {
        islands[i].name = names[i];
    }

    line = 2;
    end = false;
    while (!end) {
        int bridge;
        int node1;
        int node2;
        char *str = mx_read_str(file, line, &end);
        int name1_len = mx_get_char_index(str, '-');
        int name2_len = mx_get_char_index(str, ',');
        int num_index = mx_get_char_index(str, ',') + 1;
        int num_len = mx_strlen(str) - num_index;
        name2_len -= name1_len + 1;
        if (num_len < 1) {
            mx_line_err(line);
            mx_strdel(&str);
            mx_del_islands(islands, count_of_islands);
            exit(0);
        }
        bridge = mx_atoi_special(&(str[num_index]), num_len);
        if (bridge < 0) {
            mx_line_err(line);
            mx_strdel(&str);
            mx_del_islands(islands, count_of_islands);
            exit(0);
        }

        if (sum_bridges >= 0) {
            sum_bridges += bridge;
        }

        for (node1 = 0; node1 < count_of_islands; node1++) {
            if (mx_strncmp(str, islands[node1].name, name1_len) == 0) {
                break;
            }
        }
        for (node2 = 0; node2 < count_of_islands; node2++) {
            if (mx_strncmp(&(str[name1_len + 1]), islands[node2].name, name2_len) == 0) {
                break;
            }
        }
        if (map[node1 * count_of_islands + node2] == -1) {
            map[node1 * count_of_islands + node2] = bridge;
            map[node2 * count_of_islands + node1] = bridge;
        }
        else {
            mx_del_islands(islands, count_of_islands);
            mx_printerr("error: duplicate bridges\n");
            mx_strdel(&str);
            exit(0);
        }
        mx_strdel(&str);
        line++;
    }
    if (sum_bridges < 0) {
        mx_del_islands(islands, count_of_islands);
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(0);
    }
}

