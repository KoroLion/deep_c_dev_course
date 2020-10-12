/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#include <check.h>
#include <stdbool.h>

#include "include/string_list.h"
#include "include/email_filter.h"

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
} END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, has_email_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0? 0: 1;
}
