#ifndef BOOK_H
#define BOOK_H
#include <bits/stdc++.h>
using namespace std;
class book
{
private:
    string id;        // ID
    string name;      // 书名
    string author;    // 作者
    string publisher; // 出版社
    string year;      // 出版年份
    string borrower;  // 借阅者
    bool isBorrowed;  // 是否借出
    string ISBN;      // ISBN
    int borrowCount;  // 借阅次数
public:
    book();
    book(string id, string name, string author, string publisher, string year, string ISBN, string borrower, bool is_borrowed, int borrowCount);
    ~book();
    string getId();
    string getName();
    string getAuthor();
    string getPublisher();
    string getYear();
    string getBorrower();
    int getBorrowCount();
    bool getIsBorrowed();
    string getISBN();
    void setId(string id);
    void setName(string name);
    void setAuthor(string author);
    void setPublisher(string publisher);
    void setYear(string year);
    void setBorrower(string borrower);
    void setIsBorrowed(bool isBorrowed);
    void setISBN(string ISBN);
    void setBorrowCount(int borrowCount);
    friend ostream &operator<<(ostream &out, book &b);
};


#endif