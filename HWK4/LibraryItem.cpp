#include <iostream>
#include <string>
#include "LibraryItem.h"

using namespace std;

LibraryItem::LibraryItem(int m, double n, string b, int v){
    IDNum = m;
    cost = n;
    status = b;
    loanPer = v;
}

void LibraryItem::setIDNum(int z){ IDNum = z;}
void LibraryItem::setCost(double x){ cost = x;}
void LibraryItem::setStatus(string c){ status = c;}
void LibraryItem::setLoanPer(int g){ loanPer = g;}

int LibraryItem::getIDNum(){ return IDNum;}
double LibraryItem::getCost(){ return cost;}
string LibraryItem::getStatus(){ return status;}
int LibraryItem::getLoanPer(){ return loanPer;}

void LibraryItem::print() {
    cout<<"Item ID: "<<IDNum<<" Price: "<<cost<<" Item status: "<<status<<" Loan period: "<<loanPer<<endl;
}
void LibraryItem::rawPrint() {
    cout<<IDNum<<" "<<cost<<" "<<status<<" "<<loanPer<<endl;
}