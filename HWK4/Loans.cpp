/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iterator>
#include "Loan.h"
#include "Loans.h"

#include "LibraryItems.h"
#include "Patrons.h"
extern Patrons pat;
extern LibraryItems lit;

using namespace std;


int Loans::getCount()
{
return count;
}
int id_gens = 0;
int save2;
bool confirm;
void Loans::incCount()
{
 count++;
}
void Loans::decCount()
{
 count--;
}
void Loans::addLoan()
{
    string buff; int num2, num, num3;
    Loan *temp;
    char taskA = 'a';
    //determine loan id
    if(loanList.size() > 0)
    {
	save2 = loanList.at(loanList.size()-1)->getLoanID();
	confirm  = true;
    } else {
	confirm = false;
    }
    //gather info
    cout<<"Enter Library item id: ";
    cin>>num2;
    cin.ignore();
	lit.addNSet(num2,toupper(taskA));
    cout<<"Enter patron id: ";
    cin>>num;
    cin.ignore();
	pat.addNSetPatron(num,toupper(taskA));
int check = pat.findNGetBooks(num);
cout<<check;
//create loans
if(check+1 < 7)
{
time_t now = time(0);
int num33 = now;
num3 = now+(60*60*24*(lit.findLoanPeriod(num2)));
save2++;
 if(confirm){
    temp = new Loan(save2, num2, num, num33, num3, 0, "Normal");
   } else {
    temp = new Loan(id_gens,num2,num,num33,num3,0,"Normal");
   }
    loanList.push_back(temp);
    incCount();
    id_gens++;

} else {
cout<<"Patron has too many items.";
 }

}


void Loans::deleLoan(int x)
{
    char taskD = 'd';
    char taskF = 'f';
    time_t now = time(0);
    int l = 0;
    for (int i = 0; i < count; i++)
    {
        //if user is found make sure its before their due date then delete loan while updating books/patrons
        if(loanList[i]->getLoanID() == x)
        {
	 if(now < loanList[i]->getDueDate())
	 {
	    pat.addNSetPatron(loanList[i]->getPatronID(),taskD);
	    pat.addNSetPatron(loanList[i]->getPatronID(),taskF);
            lit.addNSet(loanList[i]->getLibItemID(),taskD);
            loanList.erase(loanList.begin()+i);
	 } else {
	   l++;
	 }
       }
    }
    //tell user what they entered was not found
if(l == count)
{
 cout<<"No match found."<<endl;
}
    decCount();
}


void Loans::printOD()
{ int l = 0;
    Loan  *temp;
    for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        temp = *it;
	time_t now = time(0);
    //if due date has passed update info and print loan
	if(temp->getDueDate() < now)
	 {
time_t here = temp->getDueDate();
	char* date_time = ctime(&here);
           cout << "Loan id: " << temp->getLoanID() << " Library item id: " << temp->getLibItemID() <<" Patron id: "<<temp->getPatronID()<<" Due date: "<<date_time<<" Loan Status: "<<temp->getStatus()<<endl;
	   pat.findNPrint(temp->getPatronID());
	 } else {
	  l++;
         }
    }
    //tell user what they entered was not found
if(l == count)
{
 cout<<"No overdue loans found."<<endl;
}
}

void Loans::updateFine()
{
time_t now = time(0);
for(int i = 0; i < count; i ++)
{
    //if patron still hasnt checked in book update info
 if(loanList[i]->getDueDate()+(60*60*24) < now)
 {
	pat.setPatronDebt(loanList[i]->getPatronID(),0.25);
 }
}
}
void Loans::listPatItems()
{
int nums3; int l = 0;
cout<<"Enter patron id: ";
cin>>nums3;
for(int i = 0; i < count; i++){
    //if data entered is found update info
if(loanList[i]->getPatronID() == nums3){
lit.findNPrint(loanList[i]->getLibItemID());
		} else {
		l++;
		}
	}
//tell user what they entered was not found
if(l == count)
{
 cout<<"Patron has 0 Library items checked out."<<endl;
}
}

void Loans::editLID(int n)
{
int sumn; int l = 0;
cout<<"Enter loan id: ";
cin>>sumn;
for(int i = 0; i< count; i++)
 {
    //if data entered is found update info
  if(loanList[i]->getLoanID() == sumn){
        loanList[i]->setLoanID(n);
        } else {
	l++;
	}
 }
//tell user what they entered was not found
if(l == count)
{
 cout<<"No match found."<<endl;
}
}

void Loans::lostBook()
{
double nums; int l = 0;
char task4 = 'l';
cout<<"Enter Library item id: ";
cin>>nums;
for(int i = 0; i < count; i++)
 {
    //if info entered is found update info
  if(loanList[i]->getLibItemID() == nums)
  {
	lit.addNSet(nums,task4);
	double debt = lit.findNGetPrice(nums);
	pat.setPatronDebt(loanList[i]->getPatronID(),debt);
  } else {
	l++;
  }
 }
//tell user what they entered was not found
if(l == count)
{
 cout<<"No match found."<<endl;
}
}


void Loans::recheckLoan(int x22)
{ int l = 0;
for(int i = 0; i < count; i++)
 {
    //if data entered is found&eligible update info
 if(loanList[i]->getLoanID() == x22 && loanList[i]->getCheck() < 1)
  {
	loanList[i]->setDueDate(loanList[i]->getDueDate()+(60*60*24*10));
	loanList[i]->setCheck(1);
  } else {
	l++;
	 }
 }
//tell user what they entered was not found
if(l == count)
{
 cout<<"Loan was not found or it cannot be rechecked again."<<endl;
}
}


void Loans::findNSetStatus()
{
time_t now = time(0);
for(int i = 0; i < count; i++)
 {
    //find the loan and update the status
  if(loanList[i]->getDueDate() < now)
  {
	loanList[i]->setStatus("Overdue");
  }
 }
}


void Loans::findNPrint(int yy)
{ int l = 0;
    for (int i =0; i < count; i++)
    {
        //find the loan and update info
        if (loanList[i]->getLoanID() == yy)
        {
	time_t here = loanList[i]->getDueDate();
        char* date_time = ctime(&here);
         cout << "Loan id: " << loanList[i]->getLoanID() << " Library item id: " << loanList[i]->getLibItemID() <<" Patron id: "<<loanList[i]->getPatronID()<<" Due date: "<<date_time<<" Loan Status: "<<loanList[i]->getStatus()<<endl;
        } else {
	l++;
	}
    }
    //tell user what they entered was not found
if(l == count)
{
 cout<<"No match found."<<endl;
}
}


void Loans::printLoans()
{
    Loan  *temp;
    //print all loans
    for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        temp = *it;
time_t here = temp->getDueDate();
        char* date_time = ctime(&here);
        cout << "Loan id: " << temp->getLoanID() << " Library item id: " << temp->getLibItemID() <<" Patron id: "<<temp->getPatronID()<<" Due date: "<<date_time<<" Loan Status: "<<temp->getStatus()<<endl;
    }
}


void Loans::storeLoans()
{
    ofstream fout;
    fout.open("loans.dat");
    //get size out first
    fout << count << endl;
    
    Loan *temp;
    //now the data follows
   for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        temp= *it;
        fout<< temp->getLoanID() <<" "<< temp->getLibItemID() <<" "<<temp->getPatronID()<<" "<<temp->getStartDate()<<" "<<temp->getDueDate()<<" "<<temp->getCheck()<<" "<<temp->getStatus()<<endl;
    }
    fout.close();
}


void Loans::loadLoans()
{
    ifstream fin;
    int id,num,num2,num3,num4,num5;
    string name;
    fin.open("loans.dat");
    //get the size
    fin >> count; fin.ignore();
    //get the info
    for ( int i=0; i < count; i++)
    {
        
        fin >> id >> num >> num2 >> num3 >> num4 >> num5;
	getline(fin,name);
        loanList.push_back( new Loan(id,num,num2,num3,num4,num5,name) );
    }
    fin.close();
    
}


void Loans::cleanUp()
{
       for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        
        delete *it;
    }
    loanList.clear();
}
