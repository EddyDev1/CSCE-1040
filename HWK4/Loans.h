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
void deleteLoan(int loanID);
void printLoans();
Loans* findLoan(int loanID);
void findAndPrintLoan(int loanID);
void printOverdueLoans();
void listPatronItems();
void lostBook();
void editLoan(int loanID);
void findAndSetStatus();
void recheckLoan(int loanID);
void updateFine();
void editLoanID(int new_loanID);

void loadLoans();
void storeLoans();
void cleanUp();

private:
int count;
vector<Loan*> loanList;
};

