
using namespace std;

class AudioCD : public LibraryItem{
public:
AudioCD(int, double, string, int, string, string, int, string, string);

void setArtist(string);
void setTitle(string);
void setNumOfTrack(int);
void setReleaseDate(string);
void setGenre(string);
void print();

string getArtist();
string getTitle();
int getNumOfTrack();
string getReleaseDate();
string getGenre();

private:
    string artist;
    string title;
    int numOfTracks;
    string releaseDate;
    string genre;
};