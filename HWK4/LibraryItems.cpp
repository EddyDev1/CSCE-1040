/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <iterator>
#include <typeinfo>
#include <ctime>

#include "LibraryItem.h"
#include "AudioCD.h"
#include "Book.h"
#include "DVD.h"
#include "LibraryItems.h"

using namespace std;

LibraryItems::LibraryItems() {
    count = 0;
    loadLibItems();
}
LibraryItems::~LibraryItems() {
    storeLibItems();
    cleanUp();
}

int LibraryItems::getCount() { return count; }
void LibraryItems::incCount() { count++; }
void LibraryItems::decCount() { count--; }

string inform(int& curramt, int& maxamt)
{
    return curramt == maxamt ? "No match was found.\n" : "A match was found.\n";
}

string okay(LibraryItem* curramt) { return "okay";}

void LibraryItems::addLibItem()
{
    double price;
    LibraryItem *temp;
    bool cont;
    int lastId, generateId = 0, operationType;

    //gather info
    if(LibItemList.size() > 0)
    {
        lastId = LibItemList.at(LibItemList.size()-1)->getIDNum();
        cont  = true;
    } else {
        cont = false;
    }

    cout<<"Enter price: ";
    cin>>price;

    cout<<"Is this 1. a Library Item, 2. a Book, 3. an Audio CD, or 4. a DVD?: \n";
    cin>>operationType;
    cin.ignore();

    if(operationType == 1){
        string status; int loanPeriod;
        cout<<"Enter item status: "; getline(cin,status);
        cout<<"Enter item loan period: "; cin>>loanPeriod;

        lastId++;
        if(cont) {
            temp = new LibraryItem( lastId, price, status, loanPeriod );
        } else {
            temp = new LibraryItem( generateId, price, status, loanPeriod );
        }
    } else if(operationType == 2){
        string au, ti, in, bc;
        string status; int loanPeriod;

        cout<<"Enter book status: \n"; getline(cin, status);
        cout<<"Enter book loan period: \n"; cin>>loanPeriod; cin.ignore();
        cout<<"Enter book author: \n"; getline(cin,au);
        cout<<"Enter book title: \n"; getline(cin,ti);
        cout<<"Enter book ISBN (xxx-x-xx-xxxxxx-x): \n"; getline(cin,in);
        cout<<"Enter book genre: \n"; getline(cin,bc);

        lastId++;
        if(cont) {
            temp = new Book(lastId, price, status, loanPeriod, au, ti, in, bc);
        } else {
            temp = new Book(generateId, price, status, loanPeriod, au, ti, in, bc);
        }
    } else if(operationType == 3){
        string ar, ai, ag, rd;
        int at, loanPeriod;
        string status;

        cout<<"Enter audio cd status: \n"; getline(cin,status);
        cout<<"Enter audio cd loan period: \n"; cin>>loanPeriod; cin.ignore();
        cout<<"Enter audio cd artist: \n"; getline(cin,ar);
        cout<<"Enter audio cd title: \n"; getline(cin,ai);
        cout<<"Enter audio cd genre: \n"; getline(cin,ag);
        cout<<"Enter audio cd release date: \n"; getline(cin,rd);
        cout<<"Enter number of tracks on audio cd: "<< endl; cin>>at;

        lastId++;
        if(cont) {
            temp = new AudioCD(lastId, price, status, loanPeriod, ar, ai, at, rd, ag);
        } else {
            temp = new AudioCD(generateId, price, status, loanPeriod, ar, ai, at, rd, ag);
        }
    } else if(operationType == 4){
        string dt, ds, dc;
        int rt, drl;
        string status; int loanPeriod;

        cout<<"Enter dvd status: \n"; getline(cin,status);
        cout<<"Enter dvd loan period: \n"; cin>>loanPeriod; cin.ignore();
        cout<<"Enter dvd category: \n"; getline(cin,dc);
        cout<<"Enter dvd title: \n"; getline(cin,dt);
        cout<<"Enter dvd studio: \n"; getline(cin,ds);
        cout<<"Enter dvd release date: \n"; cin>>drl; cin.ignore();
        cout<<"Enter runtime of dvd: "<< endl; cin>>rt;

        lastId++;
        if(cont) {
            temp = new DVD(lastId, price, status, loanPeriod, dt, dc, rt, ds, drl);
        } else {
            temp = new DVD(generateId, price, status, loanPeriod, dt, dc, rt, ds, drl);
        }
    }

    LibItemList.push_back(temp);
    count++;
    generateId++;
}

void LibraryItems::deleLibItem(int x)
{ 
    int i = 0;
    for (; i < count; i++)
    {
        //find user and delete them
        if (LibItemList[i]->getIDNum() == x)
        {
            LibItemList.erase(LibItemList.begin()+i);
            count--;
            return;
        }
    }
    //tell user what they entered was not found
    cout<<inform(i,count);
}

void LibraryItems::addNSet(double x2,char task3)
{
    //find book and update a variety of stuff
    for (int i =0; i < count; i++)
    {
        if (LibItemList[i]->getIDNum() == x2)
        {
            switch (toupper(task3))
            {
                case 'A':
                    LibItemList[i]->setStatus("Out");
                    break;
                case 'D':
                    LibItemList[i]->setStatus("In");
                    break;
                case 'L':
                    LibItemList[i]->setStatus("Lost");
                    break;
            }
        }
    }
}

double LibraryItems::findNGetPrice(int x5)
{
    int i = 0;
    for (; i < count; i++)
    {
        //find book and return the price
        if (LibItemList[i]->getIDNum() == x5)
            return LibItemList[i]->getCost();
    }
    //tell user what they entered was not found
    cout<<inform(i,count);

    return -1.0;
}

int LibraryItems::findLoanPeriod(int x6)
{
    int i = 0;
    for (; i < count; i++)
    {
        //find book and return the price
        if (LibItemList[i]->getIDNum() == x6)
            return LibItemList[i]->getLoanPer();
    }
    //tell user what they entered was not found
    cout<<inform(i,count);

    return -1;
}

void LibraryItems::editP(int x2, double xd)
{ 
    int i = 0;
    for (; i < count; i++)
    {
        if (LibItemList[i]->getIDNum() == x2)
        {
            LibItemList[i]->setCost(xd);
            return;
        }
    }

    //tell user what they entered was not found
    cout<<inform(i,count);
}

void LibraryItems::findNPrint(int x1) {
    auto it = LibItemList.begin();
    for (; it != LibItemList.end(); ++it) {
        if ((*it)->getIDNum() == x1) {
            if (typeid(**it) == typeid(AudioCD)) {
                AudioCD *temp = dynamic_cast<AudioCD *>(*it);
                temp->print();
            } else if (typeid(**it) == typeid(Book)) {
                Book *temp = dynamic_cast<Book *>(*it);
                temp->print();
            } else if (typeid(**it) == typeid(DVD)) {
                DVD *temp = dynamic_cast<DVD *>(*it);
                temp->print();
            }
            return;
        }
    }
    
    //tell user what they entered was not found
    auto inform = [&](auto curr, auto end) -> string {
        return curr == end ? "No match was found.\n" : "A match was found.\n";
    };

    cout << inform(it, LibItemList.end());
}

void LibraryItems::printLibItem() {
    for(auto it = LibItemList.begin(); it != LibItemList.end(); ++it) {
        if (typeid(**it) == typeid(LibraryItem)) {
            (*it)->print();
        }

        if(typeid(**it) == typeid(AudioCD))
        {
            AudioCD *temp = dynamic_cast<AudioCD*>(*it);
            temp->print();
        } else if(typeid(**it) == typeid(Book)){
            Book *temp = dynamic_cast<Book*>(*it);
            temp->print();
        } else if(typeid(**it) == typeid(DVD)){
            DVD *temp = dynamic_cast<DVD*>(*it);
            temp->print();
        }
    }
}

void LibraryItems::loadLibItems()
{
    ifstream fin;
    int id, itype, loanPeriod; 
    double price;
    string status;

    fin.open("items.dat");
    //get size for the vector
    fin >> count; //fin.ignore();

    LibraryItem *temp;
    //get data and populate vector
    for ( int i=0; i < count; i++)
    {
        
        fin >> id >> price;
        fin >> status;
        fin >> loanPeriod >> itype;

        switch (itype)
        {
            case 1:
                LibItemList.push_back(new LibraryItem(id, price, status, loanPeriod));
                break;
            case 2:
            {
                string s,s2,s3,s4;
                getline(fin, s, ','); //FIXME: getline does not work properly
                getline(fin, s2, ','); //might have to use commas again
                getline(fin, s3, ',');
                getline(fin, s4);

                LibItemList.push_back(new Book(id, price, status, loanPeriod, s, s2, s3, s4));
            }
            break;
            case 3:
            {
                string s,s2,s3, s4;
                int i2;

                getline(fin, s, ',');
                getline(fin, s2, ',');
                
                fin>>i2;
                
                getline(fin,s4,',');
                getline(fin,s3);

                LibItemList.push_back(new AudioCD(id, price, status, loanPeriod, s, s2, i2, s4, s3));
            }
            break;
            case 4:
            {
                string s,s2,s3;
                int i2,i3;
                
                getline(fin, s, ',');
                getline(fin, s2, ',');
                
                fin>>i2;
                
                getline(fin,s3,' ');
                
                fin>>i3;

                LibItemList.push_back(new DVD(id, price, status, loanPeriod, s, s2, i2, s3, i3));
            }
        }
    }

    fin.close();
}

void LibraryItems::storeLibItems()
{
    ofstream fout;
    fout.open("items.dat");
    //make sure size is safe
    fout << count << endl;
    
    LibraryItem *temp;
    //now the data may follow
   for (auto it = LibItemList.begin(); it != LibItemList.end(); ++it)
    {
        temp = *it;
        fout << temp->getIDNum() <<" "<< temp->getCost()<<" "<<temp->getStatus()<<" "<<temp->getLoanPer()<<endl;

        if(typeid((**it)) == typeid(LibraryItem)){
            fout<<"1\n";
        } else if(typeid(**it) == typeid(AudioCD)){
            AudioCD *temp = dynamic_cast<AudioCD*>(*it);
            fout<<"3\n";
            fout<<temp->getArtist()<<", "<<temp->getTitle()<<", "<<temp->getNumOfTrack()<<" "<<temp->getReleaseDate()<<", "<<temp->getGenre()<<endl;
        } else if(typeid(**it) == typeid(Book)){
            Book *temp = dynamic_cast<Book*>(*it);
            fout<<"2\n";
            fout<<temp->getAuthorName()<<", "<<temp->getTitle()<<", "<<temp->getISBN()<<", "<<temp->getBookCat()<<endl;
        } else if(typeid(**it) == typeid(DVD)){
            DVD *temp = dynamic_cast<DVD*>(*it);
            fout<<"4\n";
            fout<<temp->getDTitle()<<", "<<temp->getDCat()<<", "<<temp->getRunTime()<<" "<<temp->getStudio()<<", "<<temp->getDRelDate()<<endl;
        }

    }

    fout.close();
}
void LibraryItems::cleanUp()
{
    for (auto it = LibItemList.begin(); it !=LibItemList.end(); ++it)
        delete *it;
    
    LibItemList.clear();
}



