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

void addLibraryItem();
void deleteLibraryItem(int id);
void printAllLibraryItems();
LibraryItem* findLibItem(int y);

void setBookStatus(int id, char status);
void printItem(int id);
string inform(int&, int&);
void updateItemPrice(int id, double new_price);
double findAndGetPrice(int id);
int findLoanPeriod(int id);


void loadLibItems();
void storeLibItems();
void cleanUp();

private:
int count;
vector<LibraryItem*> LibItemList;

};
