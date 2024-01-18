/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <string>

#include "LibraryItem.h"
#include "Book.h"

using namespace std;


Book::Book(int x, double y, string z, int i, string bx, string by, string bz, string ba):LibraryItem(x,y,z,i)
{
 author = bx;
 title = by;
 ISBN_number = bz;
 bookCat = ba;
}

void Book::setAuthorName(string name)
{
 author = name;
}
void Book::setTitle(string desc)
{
 title = desc;
}
void Book::setISBN(string id)
{
 ISBN_number = id;
}
void Book::setBookCat(string cat)
{
    bookCat = cat;
}

void Book::print() {
    LibraryItem::print();
    cout<<"Book info- "<<endl<<"Author: "<<author<<" Title: "<<title<<" ISBN: "<<ISBN_number<<" Genre: "<<bookCat<<endl;
}

string Book::getAuthorName()
{
 return author;
}
string Book::getTitle()
{
 return title;
}
string Book::getISBN()
{
 return ISBN_number;
}
string Book::getBookCat()
{
    return bookCat;
}




