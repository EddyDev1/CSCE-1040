/* Edward Asante CSCE 1040 Homework 3*/
#include <string>
using namespace std;

class Loan
{
public:
Loan(int l, int m, int n, int o, int os, int c,  string p);

void setLoanID(int theID);
void setLibItemID(int theID2);
void setPatronID(int theID3);
void setStartDate(int theID4);
void setCheck(int theID5);
void setDueDate(int date);
void setStatus(string desc);

int getLoanID();
int getLibItemID();
int getPatronID();
int getDueDate();
int getStartDate();
int getCheck();
string getStatus();

private:
int loanID;
int libItemID;
int patronID;
int Due_Date;
int Start_Date;
int checks;
string status;


};
