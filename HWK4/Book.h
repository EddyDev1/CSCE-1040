/* Edward Asante CSCE 1040 Homework 3*/
using namespace std;

class Book : public LibraryItem{
public:
Book(int, double, string, int, string , string , string , string h);

void setAuthorName(string name);
void setTitle(string desc);
void setISBN(string id);
void setBookCat(string cat);
void print();

string getAuthorName();
string getTitle();
string getISBN();
string getBookCat();

private:
string author;
string title;
string ISBN_number;
string bookCat;
};
