/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./string_list.h"
#include "./email_filter.h"

bool has_email(char *s, int len) {
    if (len < 0) {
        len = strlen(s);
    }
    bool correct_email = false;
    for (int i = 1; i < len - 2; i++) {
        if (s[i] == 0) {
            break;
        }

        bool has_correct_at = s[i - 1] != '@' && s[i] == '@' && s[i + 1] != '@';
        if (s[i - 1] != ' ' && has_correct_at && s[i + 1] != '.') {
            correct_email = true;
        } else if (s[i] == ' ') {
            correct_email = false;
        } else if (s[i] == '.' && s[i + 1] != ' ' && correct_email) {
            return true;
        }
    }
    return false;
}

int filter_lines_with_email(struct lnode *cur, int lines_amount, struct lnode **filtered_head) {
    struct lnode *new_head, *new_cur;
    new_head = malloc(sizeof(*new_head));
    if (new_head == NULL) {
        return -2;
    }
    new_head->next = NULL;
    new_cur = new_head;

    int filtered_amount = 0, i = 0;
    while (cur != NULL && i < lines_amount) {
        if (has_email(cur->s, cur->len)) {
            new_cur->next = malloc(sizeof(*new_cur));
            if (new_cur->next == NULL) {
                return -2;
            }
            new_cur = new_cur->next;

            new_cur->len = cur->len;
            new_cur->s = malloc(new_cur->len * sizeof(*(new_cur->s)));
            if (new_cur->s == NULL) {
                return -2;
            }
            strncpy(new_cur->s, cur->s, cur->len);
            new_cur->next = NULL;
            filtered_amount++;
        }
        cur = cur->next;
        i++;
    }

    new_cur = new_head->next;
    free(new_head);
    *filtered_head = new_cur;

    return filtered_amount;
}
