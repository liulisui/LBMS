#ifndef MENU_H
#define MENU_H
#include "admin_m.h"
#include "book_m.h"
#include "admin.h"
#include "rbtree.h"
#include "book.h"
#include "config.h"
#include <bits/stdc++.h>
using namespace std;

class menu
{
public:
    void start_menu();
    void manage_book_menu();
};

extern menu m;

#endif