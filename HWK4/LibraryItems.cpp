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

bool cont; int save, genId = 0;

LibraryItems::LibraryItems() {
    count = 0;
    loadLibItems();
}
LibraryItems::~LibraryItems() {
    storeLibItems();
    cleanUp();
}
int LibraryItems::getCount()
{
 return count;
}
void LibraryItems::incCount()
{
 count++;
}
void LibraryItems::decCount()
{
 count--;
}


void LibraryItems::addLibItem()
{
    int otype; double num;
    LibraryItem *temp;

    //gather info
    if(LibItemList.size() > 0)
    {
        save = LibItemList.at(LibItemList.size()-1)->getIDNum();
        cont  = true;
    } else {
        cont = false;
    }

    cout<<"Enter price: ";
    cin>>num;

    cout<<"Is this 1. a Library Item, 2. a Book, 3. a Audio CD, or 4. A DVD?: "<<endl;
    cin>>otype;
    cin.ignore();

    if(otype == 1){
        string stat; int lp;
        cout<<"Enter item status: "; getline(cin,stat);
        cout<<"Enter item loan period: "; cin>>lp;

        save++;
        if(cont) {
            temp = new LibraryItem(save, num, stat, lp);
        } else {
            temp = new LibraryItem(genId, num, stat, lp);
        }
    } else if(otype == 2){
        string au, ti, in, bc;
        string stat; int lp;

        cout<<"Enter book status: "<<endl; getline(cin, stat);
        cout<<"Enter book loan period: "<<endl; cin>>lp; cin.ignore();
        cout<<"Enter book author: "<<endl; getline(cin,au);
        cout<<"Enter book title: "<<endl; getline(cin,ti);
        cout<<"Enter book ISBN (xxx-x-xx-xxxxxx-x): "<<endl; getline(cin,in);
        cout<<"Enter book genre: "<<endl; getline(cin,bc);

        save++;
        if(cont) {
            temp = new Book(save, num, stat, lp, au, ti, in, bc);
        } else {
            temp = new Book(genId, num, stat, lp, au, ti, in, bc);
        }
    } else if(otype == 3){
        string ar, ai, ag, rd;
        int at;
        string stat; int lp;

        cout<<"Enter audio cd status: "<<endl; getline(cin,stat);
        cout<<"Enter audio cd loan period: "<<endl; cin>>lp; cin.ignore();
        cout<<"Enter audio cd artist: "<<endl; getline(cin,ar);
        cout<<"Enter audio cd title: "<<endl; getline(cin,ai);
        cout<<"Enter audio cd genre: "<<endl; getline(cin,ag);
        cout<<"Enter audio cd release date: "<<endl; getline(cin,rd);
        cout<<"Enter number of tracks on audio cd: "<< endl; cin>>at;

        save++;
        if(cont) {
            temp = new AudioCD(save, num, stat, lp, ar, ai, at, rd, ag);
        } else {
            temp = new AudioCD(genId, num, stat, lp, ar, ai, at, rd, ag);
        }
    } else if(otype == 4){
        string dt, ds, dc;
        int rt, drl;
        string stat; int lp;

        cout<<"Enter dvd status: "<<endl; getline(cin,stat);
        cout<<"Enter dvd loan period: "<<endl; cin>>lp; cin.ignore();
        cout<<"Enter dvd category: "<<endl; getline(cin,dc);
        cout<<"Enter dvd title: "<<endl; getline(cin,dt);
        cout<<"Enter dvd studio: "<<endl; getline(cin,ds);
        cout<<"Enter dvd release date: "<<endl; cin>>drl; cin.ignore();
        cout<<"Enter runtime of dvd: "<< endl; cin>>rt;

        save++;
        if(cont) {
            temp = new DVD(save, num, stat, lp, dt, dc, rt, ds, drl);
        } else {
            temp = new DVD(genId, num, stat, lp, dt, dc, rt, ds, drl);
        }
    }

    LibItemList.push_back(temp);
    incCount();
    genId++;
}

void LibraryItems::deleLibItem(int x)
{ int k = 0;
    for (int i  = 0; i < count; i++)
    {
        //find user and delete them
        if (LibItemList[i]->getIDNum() == x)
        {
            LibItemList.erase(LibItemList.begin()+i);
        } else {
	k++;
	}
    }
    //tell user what they entered was not found
if(k == count)
{
 cout<<"No match found."<<endl;
}
decCount();
}
/*
LibraryItem* LibraryItems::findBook(int y)
{
    Book *temp;
    //find and return book
    for (int i =0; i < count; i++)
    {
        if (bookList[i]->getLibID() == y) return bookList[i];
        
    }
  
    return NULL;
}
*/

void LibraryItems::addNSet(double x2,char task3)
{
    //find book and update a variety of stuff
    for (int i =0; i < count; i++)
    {
        if (LibItemList[i]->getIDNum() == x2 && toupper(task3) == 'A')
	    {
 	        LibItemList[i]->setStatus("Out");
	    }
        if (LibItemList[i]->getIDNum() == x2 && toupper(task3) == 'D')
        {
            LibItemList[i]->setStatus("In");
        }
        if (LibItemList[i]->getIDNum() == x2 && toupper(task3) == 'L')
        {
            LibItemList[i]->setStatus("Lost");
        }
    }
}

double LibraryItems::findNGetPrice(int x5)
{
double totals;
int k = 0;
    for (int i =0; i < count; i++)
    {
        //find book and return the price
        if (LibItemList[i]->getIDNum() == x5)
        {
        totals = LibItemList[i]->getCost();
        } else {
	k++;
	}
    }
    //tell user what they entered was not found
if(k == count)
{
 cout<<"No match found."<<endl;
 return 0;
}
return totals;
}

int LibraryItems::findLoanPeriod(int x6)
{
    int per;
    int k = 0;
    for (int i =0; i < count; i++)
    {
        //find book and return the price
        if (LibItemList[i]->getIDNum() == x6)
        {
            per = LibItemList[i]->getLoanPer();
        } else {
            k++;
        }
    }
    //tell user what they entered was not found
    if(k == count)
    {
        cout<<"No match found."<<endl;
        return 0;
    }
    return per;
}

void LibraryItems::editP(int x2, double xd)
{ int k=0;
    for (int i =0; i < count; i++)
    {
        if (LibItemList[i]->getIDNum() == x2)
        {
            LibItemList[i]->setCost(xd);
        } else {
	k++;
	}
    }
    //tell user what they entered was not found
if(k == count)
{
 cout<<"No match found."<<endl;
}
}

void LibraryItems::findNPrint(int x1) {
    int k = 0;
    for (auto it = LibItemList.begin(); it != LibItemList.end(); ++it) {
        if ((*it)->getIDNum() == x1) {
            cout << "ID: " << (*it)->getIDNum() << " price: " << (*it)->getCost() << " status: " << (*it)->getStatus()
                 << " loan info: " << (*it)->getLoanPer() << endl;

            if (typeid(**it) == typeid(AudioCD)) {
                AudioCD *temp = dynamic_cast<AudioCD *>(*it);
                cout << "CD info: " << temp->getArtist() << " " << temp->getTitle() << " " << temp->getNumOfTrack()
                     << " " << temp->getReleaseDate() << " " << temp->getGenre() << endl;
            } else if (typeid(**it) == typeid(Book)) {
                Book *temp = dynamic_cast<Book *>(*it);
                cout << "Book info: " << temp->getAuthorName() << " " << temp->getTitle() << " " << temp->getISBN()
                     << " " << temp->getBookCat() << endl;
            } else if (typeid(**it) == typeid(DVD)) {
                DVD *temp = dynamic_cast<DVD *>(*it);
                cout << "DVD info: " << temp->getDTitle() << " " << temp->getDCat() << " " << temp->getRunTime() << " "
                     << temp->getStudio() << " " << temp->getDRelDate() << endl;
            }
        } else {
            k++;
        }
    }

    //tell user what they entered was not found
if(k == count)
{
 cout<<"No match found."<<endl;
}
}

void LibraryItems::printLibItem() {
    for(auto it = LibItemList.begin(); it != LibItemList.end(); ++it) {
        if (typeid(**it) == typeid(LibraryItem)) {
        cout << "ID: " << (*it)->getIDNum() << " price: " << setprecision(4) << (*it)->getCost() << " status: "
             << (*it)->getStatus() << " loan period: " << (*it)->getLoanPer() << endl;
    }
        if(typeid(**it) == typeid(AudioCD))
        {
            AudioCD *temp = dynamic_cast<AudioCD*>(*it);
            temp->print();
            //cout<<"CD info: "<<endl<<"Artist: "<<temp->getArtist()<<" Title: "<<temp->getTitle()<<" Number of Tracks: "<<temp->getNumOfTrack()<<" Released: "<<temp->getReleaseDate()<<" Genre: "<<temp->getGenre()<<endl;
        } else if(typeid(**it) == typeid(Book)){
            Book *temp = dynamic_cast<Book*>(*it);
            temp->print();
            //cout<<"Book info: "<<endl<<"Author: "<<temp->getAuthorName()<<" Title: "<<temp->getTitle()<<" ISBN: "<<temp->getISBN()<<" Genre: "<<temp->getBookCat()<<endl;
        } else if(typeid(**it) == typeid(DVD)){
            DVD *temp = dynamic_cast<DVD*>(*it);
            temp->print();
            //cout<<"DVD info: "<<endl<<"Title: "<<temp->getDTitle()<<" Category: "<<temp->getDCat()<<" Run time: "<<temp->getRunTime()<<" Studio: "<<temp->getStudio()<<" Released: "<<temp->getDRelDate()<<endl;
        }
    }
}

void LibraryItems::loadLibItems()
{
    ifstream fin;
    int id; double num;
    string stat; int lp;
    int itype;
    fin.open("items.dat");
    //get size for the vector
    fin >> count; //fin.ignore();

    LibraryItem *temp;
    //get data and populate vector
    for ( int i=0; i < count; i++)
    {
        
        fin >> id >> num;
        fin>>stat;
        fin >> lp >> itype;

        if(itype == 1){
            LibItemList.push_back(new LibraryItem(id, num, stat, lp));
        } else if(itype == 2){
            string s,s2,s3,s4;
            getline(fin, s, ','); //FIXME: getline does not work properly
            getline(fin, s2, ','); //might have to use commas again
            getline(fin, s3, ',');
            getline(fin, s4);

            LibItemList.push_back(new Book(id, num, stat, lp, s, s2, s3, s4));
        } else if(itype == 3){
            string s,s2,s3, s4;
            int i2;
            getline(fin, s, ',');
            getline(fin, s2, ',');
            fin>>i2;
            getline(fin,s4,',');
            getline(fin,s3);

            LibItemList.push_back(new AudioCD(id, num, stat, lp, s, s2, i2, s4, s3));
        } else if(itype == 4){
            string s,s2,s3;
            int i2,i3;
            getline(fin, s, ',');
            getline(fin, s2, ',');
            fin>>i2;
            getline(fin,s3,' ');
            fin>>i3;

            LibItemList.push_back(new DVD(id, num, stat, lp, s, s2, i2, s3, i3));
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
   for (auto it = LibItemList.begin(); it !=LibItemList.end(); ++it)
    {
        temp= *it;
        fout << temp->getIDNum() <<" "<< temp->getCost()<<" "<<temp->getStatus()<<" "<<temp->getLoanPer()<<endl;
        if(typeid((**it)) == typeid(LibraryItem)){
            fout<<"1"<<endl;
        } else if(typeid(**it) == typeid(AudioCD)){
            AudioCD *temp = dynamic_cast<AudioCD*>(*it);
            fout<<"3"<<endl;
            fout<<temp->getArtist()<<", "<<temp->getTitle()<<", "<<temp->getNumOfTrack()<<" "<<temp->getReleaseDate()<<", "<<temp->getGenre()<<endl;
        } else if(typeid(**it) == typeid(Book)){
            Book *temp = dynamic_cast<Book*>(*it);
            fout<<"2"<<endl;
            fout<<temp->getAuthorName()<<", "<<temp->getTitle()<<", "<<temp->getISBN()<<", "<<temp->getBookCat()<<endl;
        } else if(typeid(**it) == typeid(DVD)){
            DVD *temp = dynamic_cast<DVD*>(*it);
            fout<<"4"<<endl;
            fout<<temp->getDTitle()<<", "<<temp->getDCat()<<", "<<temp->getRunTime()<<" "<<temp->getStudio()<<", "<<temp->getDRelDate()<<endl;
        }

    }
    fout.close();
}
void LibraryItems::cleanUp()
{
       for (auto it = LibItemList.begin(); it !=LibItemList.end(); ++it)
    {
        
        delete *it;
    }
    LibItemList.clear();
}



