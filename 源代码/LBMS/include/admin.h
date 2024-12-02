#ifndef ADMIN_H
#define ADMIN_H
#include <bits/stdc++.h>
using namespace std;
class admin
{
private:
    string account;  // 账号
    string password; // 密码
public:
    admin();
    ~admin();
    admin(string account, string password);
    string getAccount();
    string getPassword();
    void setAccount(string account);
    void setPassword(string password);
};



#endif