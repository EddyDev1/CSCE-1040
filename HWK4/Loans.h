/* Edward Asante CSCE 1040 Homework 3*/
#include <vector>
#include <ctime>
using namespace std;
class Loans
{
public:
int getCount();
void incCount();
void decCount();

void addLoan();
void deleLoan(int x);
void printLoans();
Loans* findLoan(int y);
void findNPrint(int z);
void printOD();
void listPatItems();
void lostBook();
void editLoan(int xx);
void findNSetStatus();
void recheckLoan(int xx3);
void updateFine();
void editLID(int xx4);

void loadLoans();
void storeLoans();
void cleanUp();
private:
int count;
vector<Loan*> loanList;

};

