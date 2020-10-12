/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/string_list.h"

const int DEFAULT_BUF_LEN = 1024;
const int MAX_OUTPUT_LEN = 512;

bool add_to_list(struct lnode *cur, const char *s, const int len) {
    struct lnode *prev;
    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
    }

    prev->next = malloc(sizeof(*prev));
    cur = prev->next;
    if (cur == NULL) {
        return false;
    }

    cur->len = len;
    cur->s = malloc(len * sizeof(*(cur->s)));
    if (cur->s == NULL) {
        return false;
    }
    cur->next = NULL;
    strncpy(cur->s, s, len);

    return true;
}

void free_used(FILE *fp, char *buf, struct lnode *head) {
    fclose(fp);
    free(buf);
    free_list(head);
}

int read_file_to_list(struct lnode **head, const char *fpath) {
    FILE *fp;
    fp = fopen(fpath, "r");
    if (fp == NULL) {
        return -1;
    }

    char c;
    int list_len = 0;
    char *buf = malloc(1024 * sizeof(*buf)), *old_buf;
    *head = malloc(sizeof(**head));
    if (*head == NULL) {
        free_used(fp, buf, *head);
        return -2;
    }
    (*head)->next = NULL;
    struct lnode *cur = *head;
    int len = 0, max_len = DEFAULT_BUF_LEN;
    while ((c = fgetc(fp)) != EOF) {
        // double buffer if there is not enough space
        if (len == max_len) {
            max_len *= 2;
            old_buf = buf;
            buf = realloc(buf, max_len);
            if (buf == NULL) {
                free_used(fp, old_buf, *head);
                return -2;
            }
        }

        buf[len++] = c;
        if (c == 10) {
            buf[len++] = 0;  // NULL terminating the string

            if (!add_to_list(cur, buf, len)) {
                free_used(fp, buf, *head);
                return -2;
            }
            cur = cur->next;

            list_len++;
            len = 0;
        }
    }
    // last line could be without \n, adding it
    if (len > 0) {
        buf[len++] = '\n';
        buf[len++] = 0;
        if (!add_to_list(cur, buf, len)) {
            free_used(fp, buf, *head);
            return -2;
        }
        list_len++;
    }
    free(buf);
    fclose(fp);

    struct lnode *temp = *head;
    *head = (*head)->next;
    free(temp);

    return list_len;
}

void print_list(struct lnode* cur) {
    while (cur != NULL) {
        // if string is too big => cropping it
        if (strlen(cur->s) > MAX_OUTPUT_LEN) {
            char *buf = malloc((MAX_OUTPUT_LEN + 1) * sizeof(*buf));
            buf[MAX_OUTPUT_LEN] = 0;
            strncpy(buf, cur->s, MAX_OUTPUT_LEN);
            printf("%s...\n", buf);
            free(buf);
        } else {
            printf("%s", cur->s);
        }
        cur = cur->next;
    }
}

int free_list(struct lnode *head) {
    struct lnode *cur, *temp;
    int freed_amount = 0;
    cur = head;

    while (cur != NULL) {
        temp = cur;
        free(cur->s);
        cur = cur->next;
        free(temp);
        freed_amount++;
    }

    return freed_amount;
}
