#ifndef ADMIN_M_H
#define ADMIN_M_H
#include "admin.h"
#include "rbtree.h"
#include "config.h"
#include <bits/stdc++.h>

class admin_manager
{
private:
    RBTree<string, admin> admins;

public:
    admin_manager();
    ~admin_manager();
    void init();
    bool regist();
    bool login();
    void save();
    void save_node(RBTNode<string, admin>* node, ofstream &file);
};

extern admin_manager admin_m;

#endif