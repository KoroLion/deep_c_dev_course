/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./string_list.h"

const int DEFAULT_BUF_LEN = 1024;
const int MAX_OUTPUT_LEN = 512;

int read_file_to_list(struct lnode **head, const char *fpath) {
    FILE *fp;
    fp = fopen(fpath, "r");
    if (fp == NULL) {
        printf("ERROR: Unable to open file %s", fpath);
        return -1;
    }

    char c;
    int list_len = 0;
    char *buf = malloc(1024 * sizeof(*buf));
    *head = malloc(sizeof(**head));
    (*head)->next = NULL;
    struct lnode *cur = *head;
    int len = 0, max_len = DEFAULT_BUF_LEN;
    while ((c = fgetc(fp)) != EOF) {
        // double buffer if there is not enough space
        if (len == max_len) {
          max_len *= 2;
          buf = realloc(buf, max_len);
        }

        buf[len++] = c;
        if (c == 10) {
            buf[len++] = 0; // NULL terminating the string
            cur->next = malloc(sizeof(*cur));
            cur = cur->next;

            cur->len = len;
            cur->s = malloc(len * sizeof(*(cur->s)));
            cur->next = NULL;
            strncpy(cur->s, buf, len);

            list_len++;

            len = 0;
        }
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
