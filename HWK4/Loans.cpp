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
const int timer = 86400;

using namespace std;

int Loans::getCount() { return count; }
void Loans::incCount() { count++; }
void Loans::decCount() { count--; }

void Loans::addLoan()
{
    int itemId, patronId, dueDate, lastId = 0, id_gens = 0;
    Loan *temp;
    
    //determine loan id
    if(loanList.size() > 0)
	    lastId = loanList.at(loanList.size()-1)->getLoanID();

    //gather info
    cout<<"Enter Library item id: ";
    cin>>itemId;
    cin.ignore();

    cout<<"Enter patron id: ";
    cin>>patronId;
    cin.ignore();

    lit.addNSet(itemId,toupper('a'));
	pat.addNSetPatron(patronId,toupper('a'));
    
//create loans
    if(pat.findNGetBooks(patronId) + 1 < 7)
    {
        time_t time_at_checkout = time(0);
        dueDate = int(time(0))+(timer*(lit.findLoanPeriod(itemId)));

        if(lastId++)
            temp = new Loan(lastId, itemId, patronId, int(time_at_checkout), dueDate, 0, "Normal");
        else
            temp = new Loan(id_gens, itemId, patronId, int(time_at_checkout), dueDate, 0, "Normal");

        loanList.push_back(temp);
        count++;
        id_gens++;

    } else {
        cout<<"Patron has too many items.";
    }
}


void Loans::deleteLoan(int id)
{
    time_t currTime = time(0);
    int i = 0;

    for (; i < count; i++)
    {
        //if user is found make sure its before their due date then delete loan while updating books/patrons
        if(loanList[i]->getLoanID() == id)
        {
            if(currTime < loanList[i]->getDueDate())
            {
                pat.addNSetPatron(loanList[i]->getPatronID(),'d');
                pat.addNSetPatron(loanList[i]->getPatronID(),'f');
                lit.addNSet(loanList[i]->getLibItemID(),'d');
                loanList.erase(loanList.begin()+i);
                count--;
                return;
            }
       }
    }
    //tell user what they entered was not found
    if(i == count)
    {
    cout<<"No match found."<<endl;
    }
}


void Loans::printOverdueLoans()
{
    Loan  *temp; 
    int l = 0;
    for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        temp = *it;
    //if due date has passed update info and print loan
        if(temp->getDueDate() < time(0))
        {
            time_t time = temp->getDueDate();
            char* date_time = ctime(&time);
            cout << "Loan id: " << temp->getLoanID() << " Library item id: " << temp->getLibItemID() <<" Patron id: "<<temp->getPatronID()<<" Due date: "<<date_time
            <<" Loan Status: "<<temp->getStatus()<<endl;
            pat.findNPrint(temp->getPatronID());
            l++;
        }
    }
    //tell user what they entered was not found
    printf("%d%s\n", count - l, " loan(s) are not overdue.");
}

void Loans::updateFine()
{
    time_t currTime = time(0);
    for(int i = 0; i < count; i ++)
    {
        //if patron still hasnt checked in book update info
        if(loanList[i]->getDueDate()+timer < currTime)
        {
            pat.setPatronDebt(loanList[i]->getPatronID(),0.25f);
            return;
        }
    }
}
void Loans::listPatronItems()
{
    int patronId, i = 0;
    
    cout<<"Enter patron id: ";
    cin>>patronId;

    for(; i < count; i++)
    {
        //if data entered is found update info
        if(loanList[i]->getPatronID() == patronId){
            lit.findNPrint(loanList[i]->getLibItemID());
            return;
        } 
	}
    
    //tell user what they entered was not found
    if(i == count)
        cout<<"Patron has 0 Library items checked out."<<endl;
}

void Loans::editLoanID(int new_id)
{
    int loanId, i = 0;
    
    cout<<"Enter loan id: ";
    cin>>loanId;
    
    for(; i < count; i++)
    {
    //if data entered is found update info
        if(loanList[i]->getLoanID() == loanId){
            loanList[i]->setLoanID(new_id);
            return;
        }
	}

    //tell user what they entered was not found
    if(i == count)
        cout<<"No match found."<<endl;
}

void Loans::lostBook()
{
    int itemId, i = 0;
    
    cout<<"Enter Library item id: ";
    cin>>itemId;
    
    for(; i < count; i++)
    {
    //if info entered is found update info
        if(loanList[i]->getLibItemID() == itemId)
        {
	        lit.addNSet(itemId,'l');
	        pat.setPatronDebt(loanList[i]->getPatronID(), lit.findNGetPrice(itemId));
            return;
        }
    }

    //tell user what they entered was not found
    if(i == count)
        cout<<"No match found."<<endl;
}


void Loans::recheckLoan(int id)
{
    for (auto& loan : loanList)
    {
        if(loan->getLoanID() == id && loan->getCheck() < 1)
        {
            loan->setDueDate(loan->getDueDate()+timer);
            loan->setCheck(1);
            return;
        }
    }
    
    //tell user what they entered was not found
    cout<<"Loan was not found or it cannot be rechecked again."<<endl;
}


void Loans::findAndSetStatus()
{
    time_t currTime = time(0);
    for(int i = 0; i < count; i++)
    {
        //find the loan and update the status
        if(loanList[i]->getDueDate() < currTime)
	        loanList[i]->setStatus("Overdue");
    }
}


void Loans::findAndPrintLoan(int id)
{ 
    for (auto& loan : loanList)
    {
        if(loan->getLoanID() == id)
        {
            time_t time = loan->getDueDate();
            char* date_time = ctime(&time);
            cout << "Loan id: " << loan->getLoanID() << " Library item id: " << loan->getLibItemID() <<" Patron id: "<<loan->getPatronID()<<" Due date: "<<date_time<<" Loan Status: "<<loan->getStatus()<<endl;
            return; 
        }
    }

    cout<<"No match found."<<endl;
}


void Loans::printLoans()
{
    Loan  *temp;
    //print all loans
    for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        temp = *it;
        time_t time = temp->getDueDate();
        char* date_time = ctime(&time);
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
        fout<< temp->getLoanID() <<' '<< temp->getLibItemID() <<' '<<temp->getPatronID()<<' '<<temp->getStartDate()<<' '<<temp->getDueDate()<<' '<<temp->getCheck();
        fout<<' '<<temp->getStatus()<<'\n';
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
        delete *it;
    
    loanList.clear();
}
