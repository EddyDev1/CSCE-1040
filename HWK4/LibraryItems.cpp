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

string LibraryItems::inform(int& curramt, int& maxamt)
{
    return curramt == maxamt ? "No match was found.\n" : "A match was found.\n";
}

void LibraryItems::addLibraryItem()
{
    double price;
    LibraryItem *temp;
    int lastId = 0, generateId = 0, operationType, loanPeriod;
    string status, genre, release_date, title;

    //gather info
    if(LibItemList.size() > 0)
        lastId = LibItemList.at(LibItemList.size()-1)->getIDNum();

    cout<<"Enter price: ";
    cin>>price;

    cout<<"Is this 1. a Library Item, 2. a Book, 3. an Audio CD, or 4. a DVD?: \n";
    cin>>operationType;
    cin.ignore();

    switch(operationType)
    {
        case 1:
        {
            cout<<"Enter item status: "; getline(cin,status);
            cout<<"Enter item loan period: "; cin>>loanPeriod;

            temp = lastId ? new LibraryItem( ++lastId, price, status, loanPeriod ) : new LibraryItem( generateId, price, status, loanPeriod );
        }
        break;
        case 2:
        {
            string author, isbn, genre;

            cout<<"Enter book status: \n"; getline(cin, status);
            cout<<"Enter book loan period: \n"; cin>>loanPeriod; cin.ignore();
            cout<<"Enter book author: \n"; getline(cin,author);
            cout<<"Enter book title: \n"; getline(cin,title);
            cout<<"Enter book ISBN (xxx-x-xx-xxxxxx-x): \n"; getline(cin,isbn);
            cout<<"Enter book genre: \n"; getline(cin,genre);

            if(lastId)
                temp = new Book(++lastId, price, status, loanPeriod, author, title, isbn, genre);
            else
                temp = new Book(generateId, price, status, loanPeriod, author, title, isbn, genre);
        }
        break;
        case 3:
        {
            string artist;
            int ntracks;

            cout<<"Enter audio cd status: \n"; getline(cin,status);
            cout<<"Enter audio cd loan period: \n"; cin>>loanPeriod; cin.ignore();
            cout<<"Enter audio cd artist: \n"; getline(cin,artist);
            cout<<"Enter audio cd title: \n"; getline(cin,title);
            cout<<"Enter audio cd genre: \n"; getline(cin,genre);
            cout<<"Enter audio cd release date: \n"; getline(cin,release_date);
            cout<<"Enter number of tracks on audio cd: "<< endl; cin>>ntracks;

            if(lastId)
                temp = new AudioCD(++lastId, price, status, loanPeriod, artist, title, ntracks, release_date, genre);
            else
                temp = new AudioCD(generateId, price, status, loanPeriod, artist, title, ntracks, release_date, genre);
        }
        break;
        case 4:
        {
            string studio_name, category;
            int runtime;

            cout<<"Enter dvd status: \n"; getline(cin,status);
            cout<<"Enter dvd loan period: \n"; cin>>loanPeriod; cin.ignore();
            cout<<"Enter dvd category: \n"; getline(cin,category);
            cout<<"Enter dvd title: \n"; getline(cin,title);
            cout<<"Enter dvd studio: \n"; getline(cin,studio_name);
            cout<<"Enter dvd release date: \n"; cin>>release_date; cin.ignore();
            cout<<"Enter runtime of dvd: "<< endl; cin>>runtime;

            if(lastId)
                temp = new DVD(++lastId, price, status, loanPeriod, title, category, runtime, studio_name, release_date);
            else
                temp = new DVD(generateId, price, status, loanPeriod, title, category, runtime, studio_name, release_date);
        }
    }

    LibItemList.push_back(temp);
    count++;
    generateId++;
}

void LibraryItems::deleteLibraryItem(int x)
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

void LibraryItems::setBookStatus(int x2,char task)
{
    //find book and update a variety of stuff
    for (int i =0; i < count; i++)
    {
        if (LibItemList[i]->getIDNum() == x2)
        {
            switch (toupper(task))
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

double LibraryItems::findAndGetPrice(int id)
{
    int i = 0;
    for (; i < count; i++)
    {
        //find book and return the price
        if (LibItemList[i]->getIDNum() == id)
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

void LibraryItems::updateItemPrice(int id, double amt)
{ 
    int i = 0;
    for (; i < count; i++)
    {
        if (LibItemList[i]->getIDNum() == id)
        {
            LibItemList[i]->setCost(amt);
            return;
        }
    }

    //tell user what they entered was not found
    cout<<inform(i,count);
}

void LibraryItems::printItem(int x1) {
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

void LibraryItems::printAllLibraryItems() {
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
                string s,s2,s3, i3;
                int i2;
                
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



