
using namespace std;

class DVD : public LibraryItem{
public:
    DVD(int, double, string, int, string, string, int, string, string);

    void setDTitle(string);
    void setDCat(string);
    void setRunTime(int);
    void setStudio(string);
    void setRelDate(int);
    void print();

    string getDTitle();
    string getDCat();
    int getRunTime();
    string getStudio();
    string getDRelDate();

private:
    string dvdTitle;
    string dvdCat;
    int runTime;
    string studio;
    string dvdRelDate;
};