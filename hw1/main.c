/* Вариант #66
Составить программу построчной фильтрации текста, вводимого пользователем.
Суть фильтра — отбор строк, содержащих адреса электронной почты.
Фильтр должен быть реализован как функция, принимающая на вход указатель на вектор строк, их количество и указатель на результирующую структуру.
На выход функция должна возвращать количество строк в результирующей структуре.
Результат обработки выводится на экран.

Автор - Артем Королев
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

const char INPUT_FILE_PATH[] = "input1.txt";

struct lnode {
    char *s;
    int len;
    struct lnode *next;
};

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

struct lnode* filter_strings_with_email(struct lnode *head, int list_len) {
    return head;
}

int main() {
    struct lnode *all_strings_head, *filtered_strings_head, *cur;
    int list_len = read_file_to_list(&all_strings_head, INPUT_FILE_PATH);

    printf("%d\n", list_len);

    filtered_strings_head = filter_strings_with_email(all_strings_head, list_len);

    cur = all_strings_head;
    while (cur->next != NULL) {
        printf("%s", cur->s);
        cur = cur->next;
    }

    free_list(all_strings_head);

    return 0;
}
