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

void Patrons::incCount() { count++; }
void Patrons::decCount() { count--; }
int Patrons::getCount() { return count; }

void Patrons::addPatron()
{
    const int id_generator = 100000;

    string buff; 
    int num2, save3, id_gen = 0; 
    double num;
    Patron *temp;
    bool check3;
    
    //calculate patron id
    if(patronList.size() > 0)
    {
        save3 = patronList.at(patronList.size()-1)->getID();
	    check3 = true;
    } else {
	    check3 = false;
    }

    id_gen += id_generator;
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
        temp = new Patron( buff, ++save3, num, num2 ), id_gen = save3;
    else
	    temp = new Patron( buff, id_generator, num, num2 );
    
    patronList.push_back(temp);
    //update trackers
    count++;
    id_gen++;
}

void Patrons::delePatron(int id)
{ // track failed attempts when searching for id match
//find user by looping through vector
    int j = 0;
    for (auto& pat: patronList)
    {
        if (pat->getID() == id)
        {
            patronList.erase(patronList.begin()+j);
            count--;
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
void Patrons::addNSetPatron(int id , char task)
{
    double rate = 0.25;
//find patron and update a variety of things
    for (int i =0; i < count; i++)
    {
        if(patronList[i]->getBal() == 0 && patronList[i]->getID() == id){
            switch (toupper(task))
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

void Patrons::setPatronDebt(int id, double amt)
{
    //find patron and set their new bal
    for(int i = 0; i< count; i++)
    {
    if(patronList[i]->getID() == id){
            patronList[i]->setBal((patronList[i]->getBal())+amt);
            cout<<amt<<" "<<patronList[i]->getBal();
            return;
        }
    }
}

void Patrons::editN(int id, string name)
{ 
    auto it = find_if(patronList.begin(), patronList.end(), [id](Patron* p) { return p->getID() == id; });
    if (it != patronList.end())
        (*it)->setName(name), cout<< "Name change complete." << endl;
    else
        cout << "Patron does not exist." << endl;
}
int Patrons::findNGetBooks(int id)
{
    auto it = find_if(patronList.begin(), patronList.end(), [id](Patron* p) { return p->getID() == id; } );
    return it != patronList.end() ? (*it)->getBooks() : -1;
}
void Patrons::findNPrint(int id)
{ 
    int i = 0;
    for (; i < count; i++)
    {
        //if user is found print all their data
        if (patronList[i]->getID() == id)
        {
         cout<<"Patron id: "<<patronList[i]->getID()<<" Patron name: "<<patronList[i]->getName()<<" Patron balance: $"<<setprecision(4)<<patronList[i]->getBal()<<" Patron items: "<<patronList[i]->getBooks()<<endl;
         return;
        }
    }
    //tell user what they entered was not found
    cout<<"Patron does not exist."<<endl;
}
void Patrons::payFines(int id)
{
    double paymentAmt;
    int i = 0;

    for(; i < count; i++)
    {
        //if user is found update their bal
    if(patronList[i]->getID()==id){
        findNPrint(id);
        cout<<"Enter amount: ";
        cin>>paymentAmt;
        if((patronList[i]->getBal() - paymentAmt) >= 0) {
            patronList[i]->setBal(patronList[i]->getBal() - paymentAmt);
            return;
        } else {
            cout<<"Do not overpay."<<endl;
        }
    }
 }
    //tell user what they entered was not found
    cout << "Patron does not exist.\n";
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
