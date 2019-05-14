#include "film.h"

using namespace std;

Film::Film(int _id, string _name, int _year, int _length, string _summary, string _director) 
    :   id(_id) , name(_name) , year(_year) , length(_length) , summary(_summary) , director(_director) {}

int Film::get_id() { return id; }

void Film::edit_film(string name, int year, int length, int price, string summary, string director) {
    if(name != "")
        this->name = name;
    if(year != -1)
        this->year = year;
    if(length != -1)
        this->length = length;
    if(price != -1)
        this->price = price;
    if(summary != "")
        this->summary = summary;
    if(director != "")
        this->director = director;
}

 