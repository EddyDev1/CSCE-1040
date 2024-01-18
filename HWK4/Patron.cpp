/* Edward Asante CSCE 1040 Homework 3*/
#include <iostream>
#include <string>

#include "Patron.h"

using namespace std;

Patron::Patron(string theName, int thisID, double theBal, int quantity)
{
 name = theName;
 theirID = thisID;
 bal = theBal;
 booksOut = quantity;
}

string Patron::getName()
{
 return name;
}
int Patron::getID()
{
 return theirID;
}
double Patron::getBal()
{
 return bal;
}
int Patron::getBooks()
{
 return booksOut;
}
Patron* Patron::getNext()
{
 return next;
}

void Patron::setNext(Patron* np)
{
 next = np;
}
void Patron::setName(string Name)
{
 name = Name;
}
void Patron::setID(int theID)
{
 theirID = theID;
}
void Patron::setBal(double Bal)
{
 bal = Bal;
}
void Patron::setBooksAmount(int amount)
{
 booksOut = amount;
}


