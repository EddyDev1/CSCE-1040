/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip>

#include "Patron.h"
#include "Patrons.h"

using namespace std;

const static int id_generator = 100000;
int id_gen = 0, save3;
bool check3;

void Patrons::incCount() { count++; }
void Patrons::decCount() { count--; }
int Patrons::getCount() { return count; }

void Patrons::addPatron()
{
    string buff; 
    int num2; 
    double num;
    Patron *temp;
    
    //calculate patron id
    if(patronList.size() > 0)
    {
        save3 = patronList.at(patronList.size()-1)->getID();
	    check3 = true;
    } else {
	    check3 = false;
    }

    int id_gen2 = id_gen+id_generator;
    //get patron info
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, buff);

    cout<<"Enter patron balance: ";
    cin>>num;
    cin.ignore();

    cout<<"Enter amount of items: ";
    cin>>num2;
    //create patron
    if(check3)
        temp = new Patron(buff, save3+1, num, num2);
    else
	    temp = new Patron(buff, id_gen2,num,num2);
    
    patronList.push_back(temp);
    //update trackers
    incCount();
    id_gen++;
}

void Patrons::delePatron(int d)
{ // track failed attempts when searching for id match
//find user by looping through vector
    int j = 0;
    for (auto& pat: patronList)
    {
        if (pat->getID() == d)
        {
            patronList.erase(patronList.begin()+j);
            decCount();
            return;
        }
        j++;
    }
    
    cout<<"Patron does not exist."<<endl;
}

Patron* Patrons::findPatron(int id)
{
    for (int i =0; i < count; i++) //loop till patron is found
        if (patronList[i]->getID() == id) 
            return patronList[i];
        
    return NULL;
}
void Patrons::addNSetPatron(int y , char a)
{
    double rate = 0.25;
//find patron and update a variety of things
    for (int i =0; i < count; i++)
    {
        if(patronList[i]->getBal() == 0 && patronList[i]->getID() == y){
            switch (toupper(a))
            {
                case 'A':
                    patronList[i]->setBooksAmount((patronList[i]->getBooks())+1);
                    break;
                case 'D':
                    patronList[i]->setBooksAmount(patronList[i]->getBooks()-1);
                    break;
                case 'F':
                    patronList[i]->setBooksAmount(patronList[i]->getBal()+rate);
                    break;
                default:
                    break;
            }
            return;
       }
    }
    cout<<"Pay fines first."<<endl;
}

void Patrons::setPatronDebt(int xx, double xxx)
{
    //find patron and set their new bal
    for(int i = 0; i< count; i++)
    {
    if(patronList[i]->getID() == xx){
            patronList[i]->setBal((patronList[i]->getBal())+xxx);
            cout<<xxx<<" "<<patronList[i]->getBal();
            return;
        }
    }
}

void Patrons::editN(int xx2, string x4)
{ 
    auto it = find_if(patronList.begin(), patronList.end(), [xx2](Patron* p) { return p->getID() == xx2; });
    if (it != patronList.end())
        (*it)->setName(x4), cout<< "Name change complete." << endl;
    else
        cout << "Patron does not exist." << endl;
}
int Patrons::findNGetBooks(int yyy)
{
    auto it = find_if(patronList.begin(), patronList.end(), [yyy](Patron* p) { return p->getID() == yyy; });
    return it != patronList.end() ? (*it)->getBooks() : -1;
}
void Patrons::findNPrint(int yy)
{ 
    int i = 0;
    for (; i < count; i++)
    {
        //if user is found print all their data
        if (patronList[i]->getID() == yy)
        {
         cout<<"Patron id: "<<patronList[i]->getID()<<" Patron name: "<<patronList[i]->getName()<<" Patron balance: $"<<setprecision(4)<<patronList[i]->getBal()<<" Patron items: "<<patronList[i]->getBooks()<<endl;
         return;
        }
    }
    //tell user what they entered was not found
    if(i == count)
        cout<<"Patron does not exist."<<endl;
}
void Patrons::payFines(int x5x)
{
 double x55x;
 int j = 0;
 for(int i = 0; i < count; i++)
 {
     //if user is found update their bal
  if(patronList[i]->getID()==x5x){
	findNPrint(x5x);
	cout<<"Enter amount: ";
	cin>>x55x;
    if((patronList[i]->getBal() - x55x) >= 0) {
        patronList[i]->setBal(patronList[i]->getBal() - x55x);
    } else {
        cout<<"Do not overpay."<<endl;
    }
  } else {
	j++;
  }
 }
    //tell user what they entered was not found
if(j == count)
{
cout<<"Patron does not exist."<<endl;
}
}
void Patrons::cleanUp()
{
    for (auto it = patronList.begin(); it !=patronList.end(); ++it)
        delete *it;

    patronList.clear();
}

void Patrons::printPatrons()
{
    Patron  *temp;
    //print info for all patrons
    for (auto it = patronList.begin(); it !=patronList.end(); ++it)
    {
        temp = *it;
        cout << "Patron id: " << temp->getID() << " Patron name: " << temp->getName() <<" Patron balance: $"<<setprecision(4)<<temp->getBal()<<" Patron items: "<<temp->getBooks()<<endl;
    }
}
void Patrons::storePatrons()
{
    ofstream fout;
    fout.open("patrons.dat");
    //put size of vector first
    fout << count << endl;
    
    Patron *temp;
    //write out the data to file
   for (auto it = patronList.begin(); it !=patronList.end(); ++it)
    {
        temp= *it;
        fout<< temp->getID() <<" ,"<< temp->getName() <<", "<<temp->getBal()<<" "<<temp->getBooks()<<endl;
    }
    fout.close();
}

void Patrons::loadPatrons()
{
    ifstream fin;
    int id, num; 
    double mon;
    string name, grabSpace;
    fin.open("patrons.dat");
    //establish size of vector
    fin >> count; fin.ignore();

    //gather data from file and create new patron and then add to vector
    for ( int i=0; i < count; i++)
    {
        fin >> id;
        
        getline(fin,grabSpace,',');
	    getline(fin, name,',');
	    
        fin >> mon >> num;
        
        patronList.push_back( new Patron(name,id,mon,num) );
    }
    
    fin.close();
}
