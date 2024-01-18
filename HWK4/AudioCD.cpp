#include <iostream>
#include <string>
#include "LibraryItem.h"
#include "AudioCD.h"
using namespace std;

AudioCD::AudioCD(int x, double y, string z, int a, string art, string titl, int tra, string dat, string gen): LibraryItem(x,y,z,a){
    artist = art;
    title = titl;
    numOfTracks = tra;
    releaseDate = dat;
    genre = gen;
}

void AudioCD::setArtist(string art){ artist = art;}
void AudioCD::setTitle(string ti){ title = ti;}
void AudioCD::setNumOfTrack(int trac){ numOfTracks = trac;}
void AudioCD::setReleaseDate(string da){ releaseDate = da;}
void AudioCD::setGenre(string ge){ genre = ge;}
void AudioCD::print(){
    LibraryItem::print();
    cout<<"CD info- "<<endl<<" Artist: "<<artist<<" Title: "<<title<<" Number of Tracks: "<<numOfTracks<<" Released: "<<releaseDate<<" Genre: "<<genre<<endl;
}

string AudioCD::getArtist(){ return artist;}
string AudioCD::getTitle(){ return title;}
int AudioCD::getNumOfTrack(){ return numOfTracks;}
string AudioCD::getReleaseDate(){ return releaseDate;}
string AudioCD::getGenre(){ return genre;}
