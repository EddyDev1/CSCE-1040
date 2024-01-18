#include <iostream>
#include <string>
#include "LibraryItem.h"
#include "DVD.h"
using namespace std;

DVD::DVD(int x, double y, string z, int a, string dvt, string dvc, int dvrt, string dvs, int drd): LibraryItem(x,y,z,a){
    dvdTitle = dvt;
    dvdCat = dvc;
    runTime = dvrt;
    studio = dvs;
    dvdRelDate = drd;
}

void DVD::setDTitle(string dt){ dvdTitle = dt;}
void DVD::setDCat(string dc){ dvdCat = dc;}
void DVD::setRunTime(int rt){ runTime = rt;}
void DVD::setStudio(string s){ studio = s;}
void DVD::setRelDate(int rd){ dvdRelDate = rd;}
void DVD::print() {
    LibraryItem::print();
    cout<<"DVD info- "<<endl<<"Title: "<<dvdTitle<<" Category: "<<dvdCat<<" Run time: "<<runTime<<" Studio: "<<studio<<" Released: "<<dvdRelDate<<endl;
}

string DVD::getDTitle(){ return dvdTitle;}
string DVD::getDCat(){ return dvdCat;}
int DVD::getRunTime(){ return runTime;}
string DVD::getStudio(){ return studio;}
int DVD::getDRelDate(){ return dvdRelDate;}

