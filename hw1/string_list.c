#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "string_list.h"

int read_file_to_list(struct lnode **head, const char *fpath) {
    FILE *fp;
    fp = fopen(fpath, "r");
    if (fp == NULL) {
        printf("ERROR: Unable to open file %s", fpath);
        return -1;
    }

    char c;
    int list_len = 0;
    char *buf = malloc(1024 * sizeof(char*));
    *head = malloc(sizeof(struct lnode));
    (*head)->next = NULL;
    struct lnode *cur = *head;
    int len = 0;
    while ((c = fgetc(fp)) != EOF && len < 1024 * sizeof(char*)) {
        buf[len++] = c;
        if (c == 10) {
            buf[len] = 0;

            cur->len = len;
            cur->s = malloc(len * sizeof(char));
            cur->next = malloc(sizeof(struct lnode));
            cur->next->next = NULL;
            strncpy(cur->s, buf, len);
            list_len++;
            cur = cur->next;

            len = 0;
        }
    }
    free(buf);
    fclose(fp);

    return list_len;
}

void print_list(struct lnode* cur) {
    while (cur != NULL) {
        printf("%s", cur->s);
        cur = cur->next;
    }
}

void free_list(struct lnode *head) {
    struct lnode *cur, *temp;
    cur = head;

    while (cur != NULL) {
        temp = cur;
        free(cur->s);
        cur = cur->next;
        free(temp);
    }
}
