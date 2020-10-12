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

#include "include/string_list.h"
#include "include/email_filter.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./<bin> <path_to_file_with_emails>\n");
        return 1;
    }

    const char *input_file_path = argv[1];

    struct lnode *all_lns_head, *flt_lns_head;

    int all_lns_amount = read_file_to_list(&all_lns_head, input_file_path);
    if (all_lns_amount < 0) {
        if (all_lns_amount == -1) {
            printf("ERROR: Unable to open file %s\n", input_file_path);
            return 1;
        } else if (all_lns_amount == -2) {
            printf("ERROR: Not enough memory!\n");
            return 1;
        }
    }

    int flt_lns_amount = filter_lines_with_email(all_lns_head,
                                                 all_lns_amount,
                                                 &flt_lns_head);
    if (flt_lns_amount < 0) {
        printf("ERROR: Not enough memory!\n");
        return 1;
    }

    printf("There are %d lines with email:\n", flt_lns_amount);
    print_list(flt_lns_head);

    free_list(all_lns_head);
    free_list(flt_lns_head);

    return 0;
}
