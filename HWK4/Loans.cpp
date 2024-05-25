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

int id_gens = 0;
int save2;
bool confirm;

int Loans::getCount() { return count; }
void Loans::incCount() { count++; }
void Loans::decCount() { count--; }

void Loans::addLoan()
{
    string buff; 
    int num2, num, num3;
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
//create loans
    if(check+1 < 7)
    {
        time_t now = time(0);
        num3 = int(time(0))+(60*60*24*(lit.findLoanPeriod(num2)));
        save2++;

        if(confirm)
            temp = new Loan(save2, num2, num, int(now), num3, 0, "Normal");
        else
            temp = new Loan(id_gens,num2,num,int(now),num3,0,"Normal");

        loanList.push_back(temp);
        incCount();
        id_gens++;

    } else {
        cout<<"Patron has too many items.";
    }
}


void Loans::deleLoan(int x)
{
    time_t now = time(0);
    int i = 0;

    for (; i < count; i++)
    {
        //if user is found make sure its before their due date then delete loan while updating books/patrons
        if(loanList[i]->getLoanID() == x)
        {
            if(now < loanList[i]->getDueDate())
            {
                pat.addNSetPatron(loanList[i]->getPatronID(),'d');
                pat.addNSetPatron(loanList[i]->getPatronID(),'f');
                lit.addNSet(loanList[i]->getLibItemID(),'d');
                loanList.erase(loanList.begin()+i);
                decCount();
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


void Loans::printOD()
{
    Loan  *temp; 
    int l = 0;
    for (auto it = loanList.begin(); it !=loanList.end(); ++it)
    {
        temp = *it;
    //if due date has passed update info and print loan
        if(temp->getDueDate() < time(0))
        {
            time_t here = temp->getDueDate();
            char* date_time = ctime(&here);
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
    time_t now = time(0);
    for(int i = 0; i < count; i ++)
    {
        //if patron still hasnt checked in book update info
        if(loanList[i]->getDueDate()+(60*60*24) < now)
        {
            pat.setPatronDebt(loanList[i]->getPatronID(),0.25f);
            return;
        }
    }
}
void Loans::listPatItems()
{
    int nums3, i = 0;
    
    cout<<"Enter patron id: ";
    cin>>nums3;

    for(; i < count; i++)
    {
        //if data entered is found update info
        if(loanList[i]->getPatronID() == nums3){
            lit.findNPrint(loanList[i]->getLibItemID());
            return;
        } 
	}
    
    //tell user what they entered was not found
    if(i == count)
        cout<<"Patron has 0 Library items checked out."<<endl;
}

void Loans::editLID(int n)
{
    int sumn, i = 0;
    
    cout<<"Enter loan id: ";
    cin>>sumn;
    
    for(; i< count; i++)
    {
    //if data entered is found update info
        if(loanList[i]->getLoanID() == sumn){
            loanList[i]->setLoanID(n);
            return;
        }
	}

    //tell user what they entered was not found
    if(i == count)
        cout<<"No match found."<<endl;
}

void Loans::lostBook()
{
    double nums; 
    int i = 0;
    
    cout<<"Enter Library item id: ";
    cin>>nums;
    
    for(; i < count; i++)
    {
    //if info entered is found update info
        if(loanList[i]->getLibItemID() == nums)
        {
	        lit.addNSet(nums,'l');
	        double debt = lit.findNGetPrice(nums);
	        pat.setPatronDebt(loanList[i]->getPatronID(),debt);
            return;
        }
    }

    //tell user what they entered was not found
    if(i == count)
        cout<<"No match found."<<endl;
}


void Loans::recheckLoan(int x22)
{
    for (auto& loan : loanList)
    {
        if(loan->getLoanID() == x22 && loan->getCheck() < 1)
        {
            loan->setDueDate(loan->getDueDate()+(60*60*24*10));
            loan->setCheck(1);
            return;
        }
    }
    
    //tell user what they entered was not found
    cout<<"Loan was not found or it cannot be rechecked again."<<endl;
}


void Loans::findNSetStatus()
{
    time_t now = time(0);
    for(int i = 0; i < count; i++)
    {
        //find the loan and update the status
        if(loanList[i]->getDueDate() < now)
	        loanList[i]->setStatus("Overdue");
    }
}


void Loans::findNPrint(int yy)
{ 
    for (auto& loan : loanList)
    {
        if(loan->getLoanID() == yy)
        {
            time_t here = loan->getDueDate();
            char* date_time = ctime(&here);
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
