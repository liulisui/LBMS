#include <bits/stdc++.h>
#include "../include/admin.h"
#include "../include/admin_m.h"
#include "../include/book.h"
#include "../include/book_m.h"
#include "../include/rbtree.h"
#include "../include/menu.h"
#include "../include/config.h"
using namespace std;



admin::admin() {}
admin::~admin() {}
admin::admin(string account, string password)
{
    this->account = account;
    this->password = password;
}
string admin::getAccount()
{
    return account;
}
string admin::getPassword()
{
    return password;
}
void admin::setAccount(string account)
{
    this->account = account;
}
void admin::setPassword(string password)
{
    this->password = password;
}



