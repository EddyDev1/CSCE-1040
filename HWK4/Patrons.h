/* Edward Asante CSCE 1040 Homework 3*/
#include <vector>
//#include "Patron.h"
using namespace std;

class Patron;

class Patrons
{
public:
int getCount();
void incCount();
void decCount();

void addPatron();
void delePatron(int x);
void printPatrons();
Patron* findPatron(int y);
void addNSetPatron(int xx , char aa);
void findNPrint(int xxx);
void payFines(int x5);
void setPatronDebt(int x6, double x7);
void editN(int x9, string b);
int findNGetBooks(int x8);

void loadPatrons();
void storePatrons();
void cleanUp();

private:
int count;
vector<Patron*> patronList;

};
