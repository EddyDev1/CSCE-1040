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
void deletePatron(int id);
void printPatrons();
Patron* findPatron(int id);
void updatePatronBooks(int id, char operationType);
void findAndPrintPatron(int id);
void payFines(int id);
void setPatronDebt(int id, double debt);
void editPatronName(int id, string b);
int findAndGetPatronBooks(int id);

void loadPatrons();
void storePatrons();
void cleanUp();

private:
int count;
vector<Patron*> patronList;

};
