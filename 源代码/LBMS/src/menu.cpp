#include <bits/stdc++.h>
#include "../include/admin.h"
#include "../include/admin_m.h"
#include "../include/book.h"
#include "../include/book_m.h"
#include "../include/rbtree.h"
#include "../include/menu.h"
#include "../include/config.h"
using namespace std;



void menu::start_menu()
{
    while (1)
    {
        cout << "----------------------------------------------------------\n";
        cout << "Welcome to the Library Management System!" << endl;
        char x;
        cout << "1.login" << endl;
        cout << "2.register" << endl;
        cout << "3.exit" << endl;
        cin >> x;
        bool flag;
        switch (x)
        {
        case '1':
            flag = admin_m.login();
            if (flag)
            {
                manage_book_menu();
            }
            break;
        case '2':
            admin_m.regist();
            break;
        case '3':
            return;
        default:
            cout << "invalid input" << endl;
        }
    }
}
void menu::manage_book_menu()
{
    while (true)
    {
        int x;
        cout << "----------------------------------------------------------\n";
        cout << "please enter a number to choice:\n";
        cout << "1.insert book" << endl;
        cout << "2.remove book" << endl;
        cout << "3.update book" << endl;
        cout << "4.search book" << endl;
        cout << "5.lend book" << endl;
        cout << "6.return book" << endl;
        cout << "7.find all the books that were borrowed" << endl;
        cout << "8.find the ten most frequently checked out books:" << endl;
        cout << "9.fuzzy search" << endl;
        cout << "10.exit" << endl;
        cin >> x;
        switch (x)
        {
        case 1:
            book_m.insert();
            break;
        case 2:
            book_m.remove();
            break;
        case 3:
            book_m.update();
            break;
        case 4:
            book_m.search();
            break;
        case 5:
            book_m.lend();
            break;
        case 6:
            book_m.return_book();
            break;
        case 7:
            book_m.find_all_lend();
            break;
        case 8:
            book_m.max_lend();
            break;
        case 9:
            book_m.fuzzy_search();
            break;
        case 10:
            return;
        default:
            cout << "invalid input" << endl;
        }
    }
}

menu m;
