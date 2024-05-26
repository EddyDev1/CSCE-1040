/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <string>

#include "Loan.h"

using namespace std;

Loan::Loan(int loanId, int itemId, int patronId, int checkout_date, int due_date, int check, string loan_status)
{
  loanID = loanId;
  libItemID = itemId;
  patronID = patronId;
  Start_Date = checkout_date;
  Due_Date = due_date;
  status = loan_status;
  checks = check;
}

void Loan::setLoanID(int theID) {loanID = theID;}
void Loan::setLibItemID(int theID2) {libItemID = theID2;}
void Loan::setPatronID(int theID3) {patronID = theID3;}
void Loan::setDueDate(int date) {Due_Date = date;}
void Loan::setStartDate(int dates) {Start_Date = dates;}
void Loan::setCheck(int datess) {checks = datess;}
void Loan::setStatus(string desc) {status = desc;}

int Loan::getLoanID() {return loanID;}
int Loan::getLibItemID() {return libItemID;}
int Loan::getPatronID() {return patronID;}
int Loan::getDueDate() {return Due_Date;}
int Loan::getStartDate() {return Start_Date;}
int Loan::getCheck() {return checks;}
string Loan::getStatus() {return status;}


