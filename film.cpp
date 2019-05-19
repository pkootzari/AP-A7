#include "film.h"

using namespace std;

Film::Film(int _id, string _name, int _year, int _length, string _summary, string _director) 
    :   id(_id) , name(_name) , year(_year) , length(_length) , summary(_summary) , director(_director) {}

int Film::get_id() { return id; }
int Film::get_length() { return length; }
int Film::get_price() { return price; }
int Film::get_year() { return year; }
double Film::get_rate() { return rate; }
string Film::get_name() { return name; }
string Film::get_director() { return director; }
string Film::get_summary() { return summary; }

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

ostream& operator<<(ostream& out, Film* film) {
    out /*<< film->id << ". "*/ << film->id << " | " << film->name << " | " << film->length << " | "
        << film->price << " | " << film->rate << " | " << film->year << " | " << film->director 
        << endl;
    return out;
}

vector<Film*> search(string name, int min_year, int max_year, int min_rate, int price, string director, vector<Film*> input) {
    vector<Film*> search_result = input;

    for(int j = 0; j < search_result.size(); j++)
        cout << search_result[j];

    if(name != "")
        for(int i = 0; i < search_result.size(); i++)
            if(search_result[i]->get_name() != name) {
                search_result.erase(search_result.begin() + i);
                i--;
            }
    if(min_year != -1)
        for(int i = 0; i < search_result.size(); i++)
            if(search_result[i]->get_year() < min_year) {
                search_result.erase(search_result.begin() + i);
                i--;
            }
    if(max_year != -1)
        for(int i = 0; i < search_result.size(); i++)
            if(search_result[i]->get_year() > max_year) {
                search_result.erase(search_result.begin() + i);
            }
    if(min_rate != -1)
        for(int i = 0; i < search_result.size(); i++)
            if(search_result[i]->get_rate() < min_rate) {
                search_result.erase(search_result.begin() + i);
                i--;
            }
    if(director != "")
        for(int i = 0; i < search_result.size(); i++)
            if(search_result[i]->get_director() != director) {
                search_result.erase(search_result.begin() + i);
                i--;
            }
    if(price != -1)
        for(int i = 0; i < search_result.size(); i++)
            if(search_result[i]->get_price() != price) {
                search_result.erase(search_result.begin() + i);
            }
    return search_result;
    
}



 