#include <bits/stdc++.h>
#include "../include/admin.h"
#include "../include/admin_m.h"
#include "../include/book.h"
#include "../include/book_m.h"
#include "../include/rbtree.h"
#include "../include/menu.h"
#include "../include/config.h"
using namespace std;

book::book()
{
    id = "";
    name = "";
    author = "";
    publisher = "";
    year = "";
    borrower = "null";
    isBorrowed = false;
    ISBN = "";
    borrowCount = 0;
}

book::book(string id, string name, string author, string publisher, string year, string ISBN, string borrower, bool is_borrowed, int borrowCount)
{
    this->id = id;
    this->name = name;
    this->author = author;
    this->publisher = publisher;
    this->year = year;
    this->ISBN = ISBN;
    this->isBorrowed = is_borrowed;
    this->borrower = borrower;
    this->borrowCount = borrowCount;
}
book::~book() {}
int book::getBorrowCount()
{
    return borrowCount;
}
void book::setBorrowCount(int borrowCount)
{
    this->borrowCount = borrowCount;
}
string book::getId()
{
    return id;
}
string book::getAuthor()
{
    return author;
}
string book::getBorrower()
{
    return borrower;
}
string book::getYear()
{
    return year;
}
string book::getISBN()
{
    return ISBN;
}
bool book::getIsBorrowed()
{
    return isBorrowed;
}
string book::getName()
{
    return name;
}
string book::getPublisher()
{
    return publisher;
}
void book::setId(string id)
{
    this->id = id;
}
void book::setName(string name)
{
    this->name = name;
}
void book::setAuthor(string author)
{
    this->author = author;
}
void book::setPublisher(string publisher)
{
    this->publisher = publisher;
}
void book::setYear(string year)
{
    this->year = year;
}
void book::setBorrower(string borrower)
{
    this->borrower = borrower;
}
void book::setIsBorrowed(bool isBorrowed)
{
    this->isBorrowed = isBorrowed;
}
void book::setISBN(string ISBN)
{
    this->ISBN = ISBN;
}

ostream &operator<<(ostream &out, book &b)
{
    out << "the information of the book:" << endl;
    out << "the ID of the book:" << b.id << endl;
    out << "the name of the book:" << b.name << endl;
    out << "the author of the book:" << b.author << endl;
    out << "the publisher of the book:" << b.publisher << endl;
    out << "the year of the book:" << b.year << endl;
    out << "the ISBN of the book:" << b.ISBN << endl;
    if (b.isBorrowed)
    {
        out << "the borrowing status of the book:checked out" << endl;
        out << "the borrower of the book:" << b.borrower << endl;
    }
    else
        out << "the borrowing status of the book:in library" << endl;
    out << "the borrow count of the book:" << b.borrowCount << endl;
    return out;
}
