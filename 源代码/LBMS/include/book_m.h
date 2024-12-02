#ifndef BOOK_M_H
#define BOOK_M_H
#include <bits/stdc++.h>
#include "rbtree.h"
#include "book.h"
#include "config.h"
using namespace std;

class book_manager
{
private:
    RBTree<string, book> books;

public:
    book_manager();
    ~book_manager();
    void init();
    void insert();
    bool empty();
    void search();
    void update();
    void remove();
    void lend();
    void return_book();
    void find_all_lend();
    void save();
    void max_lend();
    void fuzzy_search();
    void save_node(RBTNode<string, book> *node, ofstream &file);
    void find_all_lend1(RBTNode<string, book> *node);
};


extern book_manager book_m;

#endif