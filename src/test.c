/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <check.h>

#include "include/string_list.h"
#include "include/email_filter.h"

const char TEST_DATA_FPATH[] = "test_data.txt";

START_TEST(string_list_test) {
    const char *fname = "temp_data.txt";
    FILE *tmpf = fopen(fname, "wr");
    if (tmpf == NULL) {
        exit(1);
    }
    fputs("line1\nwolf\nline3\nline4", tmpf);
    fclose(tmpf);

    struct lnode *head = malloc(sizeof(*head));
    int ln_amount = read_file_to_list(&head, fname);
    fail_unless(ln_amount == 4, "read_file_to_list");
    fail_unless(head->len == 7, "read_file_to_list");  // line1\n\0
    fail_unless(strcmp(head->s, "line1\n") == 0, "read_file_to_list");
    fail_unless(strcmp(head->next->s, "wolf\n") == 0, "read_file_to_list");
    fail_unless(strcmp(head->next->next->s, "line3\n") == 0,
                "read_file_to_list");
    fail_unless(strcmp(head->next->next->next->s, "line4\n") == 0,
                "read_file_to_list");

    fail_unless(free_list(head) == 4, "free_list");

    unlink(fname);
} END_TEST

START_TEST(has_email_test) {
    fail_unless(has_email("support@mail.ru", -1) == true, "email test");
    fail_unless(has_email("@.ru", 4) == false, "email test");
    fail_unless(has_email("asdf sadf @asfdsa.ru", -1) == false, "email test");
    fail_unless(has_email("kl@lk.ru fasdfasd", -1) == true, "email test");
    fail_unless(has_email("@@@@@@@@@@@lk@mail.ru", -1) == true, "email test");
    fail_unless(has_email("  sdafas  sadf@@t.ru", -1) == false, "email test");
    fail_unless(has_email("@@.ru", -1) == false, "email test");
    fail_unless(has_email("@test.ru asdfasd fas d", -1) == false, "email test");
    fail_unless(has_email("@", -1) == false, "email test");

    fail_unless(has_email("test@restru", 100) == false, "incorrect len test");
} END_TEST

START_TEST(filter_email_test) {
    struct lnode *head = malloc(sizeof(*head));

    int ln_amount = read_file_to_list(&head, "donotcreatemepls34@51");
    fail_unless(ln_amount == -1, "file_not_exist");

    ln_amount = read_file_to_list(&head, TEST_DATA_FPATH);
    fail_unless(ln_amount == 161, "read_big_file_to_list");

    struct lnode *flt_head;
    int flt_amount = filter_lines_with_email(head, ln_amount, &flt_head);
    fail_unless(flt_amount == 95, "filtered_amount");
    flt_amount = filter_lines_with_email(head, ln_amount - 4, &flt_head);
    fail_unless(flt_amount == 92, "filtered_amount_lim");
} END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, has_email_test);
    tcase_add_test(tc1_1, string_list_test);
    tcase_add_test(tc1_1, filter_email_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0? 0: 1;
}
