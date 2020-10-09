/*
Вариант #66
Составить программу построчной фильтрации текста, вводимого пользователем.
Суть фильтра — отбор строк, содержащих адреса электронной почты.
Фильтр должен быть реализован как функция, принимающая на вход указатель на вектор строк, их количество и указатель на результирующую структуру.
На выход функция должна возвращать количество строк в результирующей структуре.
Результат обработки выводится на экран.
*/
/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "./string_list.h"

const char INPUT_FILE_PATH[] = "input2.txt";

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

int filter_lines_with_email(struct lnode **filtered_head, struct lnode *cur) {
    struct lnode *new_head, *new_cur;
    new_head = malloc(sizeof(struct lnode));
    new_head->next = NULL;
    new_cur = new_head;

    int filtered_len = 0;
    while (cur != NULL) {
        if (has_email(cur->s, cur->len)) {
            new_cur->next = malloc(sizeof(struct lnode));
            new_cur = new_cur->next;
            new_cur->s = malloc(cur->len * sizeof(char));
            strncpy(new_cur->s, cur->s, cur->len * sizeof(char));
            new_cur->len = cur->len;
            new_cur->next = NULL;
            filtered_len++;
        }
        cur = cur->next;
    }

    new_cur = new_head->next;
    free(new_head);

    *filtered_head = new_cur;
    return filtered_len;
}

void test() {
    assert(has_email("support@mail.ru", -1) == true);
    assert(has_email("@.ru", 4) == false);
    assert(has_email("asdf sadf asdfas dfasd @asfdsa.ru", -1) == false);
    assert(has_email("kl@lk.ru fasdfasdfasdfasd", -1) == true);
    assert(has_email("@@@@@@@@@@@lk@mail.ru", -1) == true);
    assert(has_email("  sdafas  sadf@@t.ru", -1) == false);
    assert(has_email("@@.ru", -1) == false);
    assert(has_email("@test.ru asdfasd fas d", -1) == false);
    assert(has_email("@", -1) == false);
}

int main() {
    test();

    struct lnode *all_lns_head, *flt_lns_head, *cur;
    int list_len = read_file_to_list(&all_lns_head, INPUT_FILE_PATH);

    int flt_lns_amount = filter_lines_with_email(&flt_lns_head, all_lns_head);

    printf("There are %d lines with email:\n", flt_lns_amount);
    print_list(flt_lns_head);

    free_list(all_lns_head);
    free_list(flt_lns_head);

    return 0;
}
