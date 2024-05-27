#include <iostream>

using namespace std;

class LibraryItem{
public:
    LibraryItem(int id, double price, string status, int checkoutPeriod) : IDNum(id), cost(price), status(status), loanPer(checkoutPeriod) {};
    virtual ~LibraryItem(){ }

    void setIDNum(int);
    void setCost(double);
    void setStatus(string);
    void setLoanPer(int);

    int getIDNum();
    double getCost();
    string getStatus();
    int getLoanPer();
    virtual void print();
    virtual void rawPrint();

private:
    int IDNum;
    double cost;
    string status;
    int loanPer;
};
