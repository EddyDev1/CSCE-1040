/* Edward Asante CSCE 1040 Homework 3*/
#include <vector>

using namespace std;

class LibraryItem;

class LibraryItems
{
public:
LibraryItems();
~LibraryItems();

int getCount();
void incCount();
void decCount();

void addLibItem();
void deleLibItem(int x);
void printLibItem();
LibraryItem* findLibItem(int y);

void addNSet(double xxx,char taskk);
void findNPrint(int x4);
void editP(int xx, double xD);
double findNGetPrice(int x5);
int findLoanPeriod(int x6);


void loadLibItems();
void storeLibItems();
void cleanUp();

private:
int count;
vector<LibraryItem*> LibItemList;

};
