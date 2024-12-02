#include <bits/stdc++.h>
#include "../include/admin.h"
#include "../include/admin_m.h"
#include "../include/book.h"
#include "../include/book_m.h"
#include "../include/rbtree.h"
#include "../include/menu.h"
#include "../include/config.h"
using namespace std;


admin_manager::admin_manager()
{
    init();
}
admin_manager::~admin_manager()
{
    save();
    admins.destroy();
}
void admin_manager::init()
{
    ifstream file(admin_path);
    if (!file.is_open())
    {
        cerr << "unable to open admin_data.csv!" << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string account, password;
        getline(ss, account, ',');
        getline(ss, password);
        admin admin_new = admin(account, password);
        admins.insert(account, admin_new);
    }
    file.close();
}
bool admin_manager::regist()
{
    cout << "please enter the secret key:" << endl;
    string secret_key;
    cin >> secret_key;
    if (secret_key != key)
    {
        cout << "wrong secret key!" << endl;
        return false;
    }
    cout << "please enter the account:" << endl;
    string account;
    cin >> account;
    if (admins.search(account))
    {
        cout << "the account already exists!" << endl;
        return false;
    }
    cout << "please enter the password:" << endl;
    string password, password_check;
    cin >> password;
    cout << "please enter the password again:" << endl;
    cin >> password_check;
    if (password != password_check)
    {
        cout << "the two passwords do not match!" << endl;
        return false;
    }
    admin admin_new = admin(account, password);
    admins.insert(account, admin_new);
    cout << "register successfully!" << endl;
    save();
    return true;
}
bool admin_manager::login()
{
    cout << "please enter the account:" << endl;
    string account;
    cin >> account;
    RBTNode<string, admin> *node = admins.search(account);
    if (node == NULL)
    {
        cout << "the account does not exist!" << endl;
        return false;
    }
    else
    {
        cout << "please enter the password:" << endl;
        string password;
        cin >> password;
        if ((node->data).getPassword() == password)
        {
            cout << "login successfully!" << endl;
            return true;
        }
        else
        {
            cout << "wrong password!" << endl;
            return false;
        }
    }
}
// 保存树节点到文件
void admin_manager::save_node(RBTNode<string, admin> *node, ofstream &file)
{
    if (node == NULL)
    {
        return;
    }
    // 递归保存左子树
    this->save_node(node->left, file);

    // 保存当前节点的账号和密码
    file << (node->data).getAccount() << "," << (node->data).getPassword() << endl;

    // 递归保存右子树
    this->save_node(node->right, file);
}

// 保存所有管理员数据到文件
void admin_manager::save()
{
    ofstream file(admin_path, ios::trunc); // 使用trunc模式，覆盖旧文件
    if (!file.is_open())
    {
        cerr << "unable to open admin_data.csv!" << endl;
        return;
    }
    file << "account,password" << endl;

    // 保存红黑树的根节点数据
    this->save_node(admins.get_root(), file);

    file.close(); // 关闭文件
}
admin_manager admin_m;


