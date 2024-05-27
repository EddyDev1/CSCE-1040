/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <string>
#include <ctime>

#include "LibraryItem.h"
#include "Patron.h"
#include "Loan.h"
#include "LibraryItems.h"
#include "Patrons.h"
#include "Loans.h"

using namespace std;
Patrons pat;
LibraryItems lit;
Loans lon;

int main()
{
pat.loadPatrons();
lon.loadLoans();


int choice;
int ids = 0;
int choice2;
string nameC;
double choice3;

while(choice!=4)
{
cout<<"Enter your choice:"<<endl;
cout<<"1 - Patron Transaction"<<endl<<"2 - Library Item Transaction"<<endl<<"3 - Loan Transaction"<<endl<<"4 - Quit"<<endl;
cin>>choice;

switch(choice)
{
 case 1:
 {
 cout<<"Enter your choice:"<<endl;
 cout<<"1 - Add Patron"<<endl<<"2 - Delete Patron"<<endl<<"3 - Print Patron"<<endl<<"4 - Print Patrons"<<endl<<"5 - Edit Patron"<<endl<<"6 - Pay Fines"<<endl;
 cin>>choice2;

 switch(choice2){
 case 1: {
     pat.addPatron();
     pat.storePatrons();
 }
 break;
 case 2:
 cout<<"Enter patron id: "<<endl;
 cin>>ids;
 pat.deletePatron(ids);
 pat.storePatrons();
 break;
 case 3:
 cout<<"Enter patron id: ";
 cin>>ids;
 pat.findAndPrintPatron(ids);
 break;
 case 4:
 pat.printPatrons();
 break;
 case 5:
 cout<<"Enter patron id: ";
 cin>>ids; cin.ignore();
 cout<<"Enter the new name: "<<endl;
 getline(cin,nameC);
 pat.editPatronName(ids,nameC);
 pat.storePatrons();
 break;
 case 6:
 cout<<"Enter patron id: ";
 cin>>ids; cin.ignore();
 pat.payFines(ids);
 break;
 default:
 cout<<"Wrong input. Try again."<<endl;
 break;
  }
 }
 break;
 case 2:
 {
 cout<<"Enter your choice:"<<endl;
 cout<<"1 - Add Item"<<endl<<"2 - Delete Item"<<endl<<"3 - Print Item"<<endl<<"4 - Print Items"<<endl<<"5 - Edit Item"<<endl;
 cin>>choice2;
 switch(choice2){
 case 1:
 lit.addLibraryItem();
 break;
 case 2:
 cout<<"Enter library item id: "<<endl;
 cin>>ids;
 lit.deleteLibraryItem(ids);
 break;
 case 3:
 cout<<"Enter library item id: "<<endl;
 cin>>ids;
 lit.printItem(ids);
 break;
 case 4:
 lit.printAllLibraryItems();
 break;
 case 5:
 cout<<"Enter library item id: ";
 cin>>ids; cin.ignore();
 cout<<"Enter new price: ";
 cin>>choice3; cin.ignore();
 lit.updateItemPrice(ids,choice3);
 break;
 default:
 cout<<"Wrong input. Try again."<<endl;
 break;
  }
 }
 break;
 case 3:
 {
 cout<<"Enter your choice:"<<endl;
 cout<<"1 - Add Loan"<<endl<<"2 - Delete Loan"<<endl<<"3 - Print Patron Items"<<endl<<"4 - Print Loans"<<endl<<"5 - Print all Overdue"<<endl<<"6 - Recheck Loan"<<endl<<"7 - Edit Loan"<<endl<<"8 - Report Lost"<<endl;
 cin>>choice2;
 switch(choice2){
 case 1:
 lon.addLoan();
 lon.storeLoans();
 break;
 case 2:
 cout<<"Enter loan id: ";
 cin>>ids; cin.ignore();
 lon.deleteLoan(ids);
 lon.storeLoans();
 break;
 case 3:
 lon.listPatronItems();
 break;
 case 4:
 lon.printLoans();
 break;
 case 5:
 lon.printOverdueLoans();
 break;
 case 6:
 cout<<"Enter loan id: ";
 cin>>ids; cin.ignore();
 lon.recheckLoan(ids);
 break;
 case 7:
cout<<"Change the loan id number to? ";
cin>>ids; cin.ignore();
 lon.editLoanID(ids);
 lon.storeLoans();
 break;
 case 8:
 lon.lostBook();
 break;
 default:
 cout<<"Wrong input. Try again."<<endl;
 break;
  }
 }
 break;
 case 4:
 cout<<"Closing Program"<<endl;
 choice = 4;
 break;
 default:
 cout<<"Wrong input. Try again."<<endl;
 break;
}
}

pat.storePatrons();
lon.storeLoans();

pat.cleanUp();
lon.cleanUp();

return 0;
}
