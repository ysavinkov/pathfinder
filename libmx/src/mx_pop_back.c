#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
    t_list *curr = NULL;
    curr = *head;
    if (head == NULL || *head == NULL)
        return;
    if (curr->next == NULL) {
        free(curr);
        curr = NULL;
    } 
    else {
        while (curr->next->next != NULL)
            curr = curr->next;
        free(curr->next);
        curr->next = NULL;
    }
}
