/*
Copyright 2020 KoroLion (github.com/KoroLion)
*/

#ifndef STRING_LIST_H
#define STRING_LIST_H

struct lnode {
    char *s;
    int len;
    struct lnode *next;
};

int read_file_to_list(struct lnode**, const char* fpath);
void print_list(struct lnode*);
void free_list(struct lnode*);

#endif /* STRING_LIST_H */
