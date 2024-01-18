/* Edward Asante CSCE 1040 Homework 3*/
#include <string>
using namespace std;
class Patron
{
public:
Patron(string theName, int thisID, double theBal, int quantity);

string getName();
int getID();
double getBal();
int getBooks();
Patron* getNext();

void setName(string Name);
void setID(int theID);
void setBal(double Bal);
void setBooksAmount(int amount);
void setNext(Patron* p);

private:
string name;
int theirID;
double bal;
int booksOut;
Patron *next;
};
