/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#ifndef SRC_INCLUDE_EMAIL_FILTER_H_
#define SRC_INCLUDE_EMAIL_FILTER_H_

bool has_email(char *s, int len);
int filter_lines_with_email(
    struct lnode *cur,
    int lines_amount,
    struct lnode **filtered_head
);

#endif  // SRC_INCLUDE_EMAIL_FILTER_H_
