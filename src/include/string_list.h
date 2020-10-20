/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#ifndef SRC_INCLUDE_STRING_LIST_H_
#define SRC_INCLUDE_STRING_LIST_H_

struct lnode {
    char *s;
    int len;
    struct lnode *next;
};

bool add_to_list(struct lnode *cur, const char *s, const int len);
int read_file_to_list(struct lnode**, const char* fpath);
void print_list(struct lnode*);
int free_list(struct lnode*);

#endif  // SRC_INCLUDE_STRING_LIST_H_
