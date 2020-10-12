/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#ifndef SRC_STRING_LIST_H_
#define SRC_STRING_LIST_H_

struct lnode {
    char *s;
    int len;
    struct lnode *next;
};

int read_file_to_list(struct lnode**, const char* fpath);
void print_list(struct lnode*);
void free_list(struct lnode*);

#endif  // SRC_STRING_LIST_H_
