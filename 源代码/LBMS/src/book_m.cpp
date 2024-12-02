#include <bits/stdc++.h>
#include "../include/admin.h"
#include "../include/admin_m.h"
#include "../include/book.h"
#include "../include/book_m.h"
#include "../include/rbtree.h"
#include "../include/menu.h"
#include "../include/config.h"
using namespace std;

book_manager::book_manager()
{
    init();
}
book_manager::~book_manager()
{
    save();
    books.destroy();
}
void book_manager::init()
{
    ifstream file(book_path);
    if (!file.is_open())
    {
        cerr << "unable to open book_data.csv!" << endl;
        return;
    }
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, author, publisher, year, ISBN, borrower, flag;
        int borrow_count;
        bool is_borrowed;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, author, ',');
        getline(ss, publisher, ',');
        getline(ss, year, ',');
        getline(ss, flag, ',');
        getline(ss, borrower, ',');
        getline(ss, ISBN, ',');
        if (flag == "0")
            is_borrowed = false;
        else
            is_borrowed = true;
        ss >> borrow_count;
        if (books.search(name))
        {
            cout << "the book already exists!" << endl;
            return;
        }
        book book_new = book(id, name, author, publisher, year, ISBN, borrower, is_borrowed, borrow_count);
        books.insert(name, book_new);
    }
}
void book_manager::insert()
{
    string id, name, author, publisher, x, year, ISBN, borrower;
    int borrow_count;
    bool is_borrowed;
    cout << "please enter the book's name:" << endl;
    cin >> name;
    if (books.search(name))
    {
        cout << "the book already exists!" << endl;
        return;
    }
    cout << "please enter the book's id:" << endl;
    cin >> id;
    cout << "please enter the book's author:" << endl;
    cin >> author;
    cout << "please enter the book's publisher:" << endl;
    cin >> publisher;
    cout << "please enter the book's year:" << endl;
    cin >> year;
    cout << "please enter the book's ISBN:" << endl;
    cin >> ISBN;
    cout << "please enter the book's borrow_count:" << endl;
    cin >> borrow_count;
    cout << "please enter 0 if the book is not borrowed,enter 1 if the book if borrowed" << endl;
    cin >> x;
    if (x == "0")
    {
        is_borrowed = false;
        borrower = "null";
    }
    else
    {
        is_borrowed = true;
        cout << "please enter the book's borrower:" << endl;
        cin >> borrower;
    }
    book book_new = book(id, name, author, publisher, year, ISBN, borrower, is_borrowed, borrow_count);
    books.insert(name, book_new);
    cout << "the book has been added!" << endl;
    save();
}

bool book_manager::empty()
{
    return books.empty();
}

// 保存树节点到文件
void book_manager::save_node(RBTNode<string, book> *node, ofstream &file)
{
    if (node == NULL)
    {
        return;
    }
    this->save_node(node->left, file);

    // 保存当前节点的书籍信息
    book b = node->data;
    file << b.getId() << "," << b.getName() << "," << b.getAuthor() << ","
         << b.getPublisher() << "," << b.getYear() << "," << (b.getIsBorrowed() ? "1" : "0") << ","
         << b.getBorrower() << "," << b.getISBN() << "," << b.getBorrowCount() << endl;
    this->save_node(node->right, file);
}

// 保存所有书籍信息到文件
void book_manager::save()
{
    ofstream file(book_path, ios::trunc); // 使用trunc模式，覆盖旧文件
    if (!file.is_open())
    {
        cerr << "unable to open book_data.csv!" << endl;
        return;
    }

    file << "id,name,author,publisher,year,isborrowed,borrower,ISBN,borrowcount" << endl;
    this->save_node(books.get_root(), file);

    file.close(); // 关闭文件
}
void book_manager::find_all_lend1(RBTNode<string, book> *node)
{
    if (node == NULL)
    {
        return;
    }
    this->find_all_lend1(node->left); // 递归遍历左子树
    // 获取当前节点的书籍信息
    book b = node->data;

    if (b.getIsBorrowed())
        cout << "<<" << b.getName() << ">>" << endl;
    this->find_all_lend1(node->right); // 递归遍历右子树
}
void book_manager::find_all_lend()
{
    cout << "these books were borrowed:" << endl;
    // 调用递归函数，遍历红黑树
    this->find_all_lend1(books.get_root());
}
void book_manager::lend()
{
    cout << "please enter the name of the book:" << endl;
    string key;
    cin >> key;

    // 查找书籍
    RBTNode<string, book> *node = books.search(key);
    if (node == NULL)
    {
        cout << "the book does not exist!" << endl;
        return;
    }

    book b = node->data;

    // 检查是否已经借出
    if (b.getIsBorrowed())
    {
        cout << "the book has been borrowed!" << endl;
        return;
    }

    // 让用户输入借阅人的信息
    cout << "please enter the name of the borrower" << endl;
    string borrower;
    cin >> borrower;

    // 更新书籍的借阅状态
    b.setIsBorrowed(true);
    b.setBorrower(borrower); // 设置借阅人

    // 记录借阅次数
    b.setBorrowCount(b.getBorrowCount() + 1);

    // 更新树中的书籍信息
    node->data = b;

    cout << "the book <<" << b.getName() << ">> has been borrowed by " << borrower << "!" << endl;
    save();
}

void book_manager::return_book()
{
    cout << "please enter the name of the book:" << endl;
    string key;
    cin >> key;

    // 查找书籍
    RBTNode<string, book> *node = books.search(key);
    if (node == NULL)
    {
        cout << "the book does not exist!" << endl;
        return;
    }

    book b = node->data;

    // 检查是否已借出
    if (!b.getIsBorrowed())
    {
        cout << "the book has not been borrowed!" << endl;
        return;
    }

    // 更新书籍的借阅状态为未借出
    b.setIsBorrowed(false);
    b.setBorrower("null"); // 清空借阅人

    // 更新树中的书籍信息
    node->data = b;

    cout << "the book <<" << b.getName() << ">> has been returned!" << endl;
    save();
}

void book_manager::search()
{
    cout << "please enter the name of the book:" << endl;
    string name;
    cin >> name;

    // 查找书籍
    RBTNode<string, book> *node = books.search(name);
    if (node == NULL)
    {
        cout << "the book does not exist!" << endl;
        return;
    }

    // 找到书籍后，显示书籍信息
    book b = node->data;
    cout << b;
}

void book_manager::update()
{
    cout << "please enter the name of the book:" << endl;
    string name;
    cin >> name;

    // 查找书籍
    RBTNode<string, book> *node = books.search(name);
    if (node == NULL)
    {
        cout << "the book does not exist!" << endl;
        return;
    }

    // 找到书籍后，提示用户进行修改
    book b = node->data;
    cout << "find the book <<" << b.getName() << ">>,please update" << endl;

    string id, author, publisher, year, ISBN, borrower, is_borrowed;
    int borrow_count;
    bool flag;
    cout << "please enter the ID: " << endl;
    cin >> id;
    cout << "please enter the name: " << endl;
    cin >> name;
    if (name != b.getName() && books.search(name) != NULL)
    {
        cout << "the name has been used!" << endl;
        return;
    }
    cout << "please enter the author: " << endl;
    cin >> author;
    cout << "please enter the publisher:  " << endl;
    cin >> publisher;
    cout << "please enter the year: " << endl;
    cin >> year;
    cout << "please enter 0 if the book is not borrowed,enter 1 if the book if borrowed:" << endl;
    cin >> is_borrowed;
    if (is_borrowed == "0")
    {
        flag = false;
        borrower = "null";
    }
    else
    {
        flag = true;
        cout << "please enter the borrower: " << endl;
        cin >> borrower;
    }
    cout << "please enter the ISBN: " << endl;
    cin >> ISBN;
    cout << "please enter the borrow_count: " << endl;
    cin >> borrow_count;

    // 更新书籍信息
    b.setId(id);
    b.setAuthor(author);
    b.setPublisher(publisher);
    b.setYear(year);
    b.setISBN(ISBN);
    b.setName(name);
    b.setIsBorrowed(flag);
    b.setBorrower(borrower);
    b.setBorrowCount(borrow_count);

    // 更新树中的书籍
    node->data = b;

    cout << "update successfully!" << endl;
    save();
}

void book_manager::remove()
{
    cout << "please enter the name of the book:" << endl;
    string name;
    cin >> name;

    // 查找书籍
    RBTNode<string, book> *node = books.search(name);
    if (node == NULL)
    {
        cout << "the book does not exist!" << endl;
        return;
    }

    book b = node->data;

    // 如果书籍已经借出，提示不能删除
    if (b.getIsBorrowed())
    {
        cout << "the book has been borrowed,so it can not be deleted!" << endl;
        return;
    }

    // 删除书籍
    books.remove(name);
    cout << "the book <<" << name << ">> has been deleted successfully!" << endl;
    save();
}
void book_manager::fuzzy_search()
{
    cout << "please enter the name of the book:" << endl;
    string input;
    cin.ignore();        // 忽略之前输入的换行符
    getline(cin, input); // 获取用户输入的书名

    // 将用户输入的字符串转为小写，方便不区分大小写进行搜索
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    bool found = false;
    // 遍历树中的所有书籍
    RBTNode<string, book> *node = books.get_root();
    stack<RBTNode<string, book> *> s;

    while (!s.empty() || node != NULL)
    {
        if (node != NULL)
        {
            s.push(node);
            node = node->left;
        }
        else
        {
            node = s.top();
            s.pop();

            book b = node->data;
            string book_name = b.getName();

            // 将书名转为小写，以进行不区分大小写的匹配
            transform(book_name.begin(), book_name.end(), book_name.begin(), ::tolower);

            // 检查书名是否包含用户输入的字符串（模糊匹配）
            if (book_name.find(input) != string::npos)
            {
                found = true;
                cout << b;
                cout << endl;
            }

            node = node->right;
        }
    }

    if (!found)
    {
        cout << "fail to find!" << endl;
    }
}
void book_manager::max_lend()
{
    // 存储所有书籍的名称和借阅次数
    vector<pair<string, int>> book_lends;

    // 遍历红黑树中的每本书
    RBTNode<string, book> *node = books.get_root();
    stack<RBTNode<string, book> *> s;

    while (!s.empty() || node != NULL)
    {
        if (node != NULL)
        {
            s.push(node);
            node = node->left;
        }
        else
        {
            node = s.top();
            s.pop();
            book b = node->data;
            string book_name = b.getName();
            int borrow_count = b.getBorrowCount();
            book_lends.push_back(make_pair(book_name, borrow_count));
            node = node->right;
        }
    }

    // 按照借阅次数降序排序

    sort(book_lends.begin(), book_lends.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.second > b.second; // 按照借阅次数降序排序
         });                             // 排序规则：借阅次数更多的排在前面

    // 输出借阅次数最多的十本书
    cout << "the ten most frequently checked out books:" << endl;
    int max_display = min(10, (int)book_lends.size());
    for (int i = 0; i < max_display; i++)
    {
        string book_name = book_lends[i].first;
        int borrow_count = book_lends[i].second;
        cout << i + 1 << ". " << book_name << " - number of borrowings: " << borrow_count << endl;
        int bar_length = borrow_count / 2; // 每5次借阅占1个字符宽度，调整此值来控制条形图的比例
        for (int j = 0; j < bar_length; j++)
        {
            cout << "#";
        }
        cout << endl;
    }
}

book_manager book_m;
