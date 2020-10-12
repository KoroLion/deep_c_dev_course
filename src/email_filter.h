#ifndef EMAIL_FILTER_H
#define EMAIL_FILTER_H

bool has_email(char *s, int len);
int filter_lines_with_email(struct lnode *cur, int lines_amount, struct lnode **filtered_head);

#endif