#include "film.h"

using namespace std;

Film::Film(int _id, string _name, int _year, int _length, string _summary, string _director, int _price) 
    :   id(_id) , name(_name) , year(_year) , length(_length) , summary(_summary) , director(_director) , price(_price) 
{ initial_comment_id = 1; rate = 0; }

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
        << film->price << " | " << setprecision(2) << film->rate << " | " << film->year << " | " << film->director 
        << endl;
    return out;
}

void Film::rate_this(int user_id, int score) {
    bool already_scored = false;
    for(int i = 0; i < scores_given.size(); i++)
        if(scores_given[i].first == user_id) {
            scores_given[i].second = score;
            already_scored = true;
        }
    if(!already_scored)
        scores_given.push_back( make_pair(user_id, score) );
    double sum = 0;
    for(int i = 0; i < scores_given.size(); i++)
        sum += scores_given[i].second;
    rate = sum / scores_given.size();
}

void Film::add_comment(string content, User* user) {
    commnets.push_back( make_pair(new Comment(initial_comment_id, content), user) );
    initial_comment_id++;
}

void Film::add_reply(string content, int comment_id) {
    bool comment_found = false;
    for(int i = 0; i < commnets.size(); i++)
        if(commnets[i].first->get_id() == comment_id) {
            commnets[i].first->add_reply(content);
            comment_found = true;
            break;
        }
    if(!comment_found)
        throw NotFound();
}

void Film::delete_comment(int comment_id) {
    bool comment_found = false;
    for(int i = 0; i < commnets.size(); i++)
        if(commnets[i].first->get_id() == comment_id) {
            commnets.erase(commnets.begin() + i);
            comment_found = true;
            break;
        }
    if(!comment_found)
        throw NotFound();
}

void Film::print_comments() {
    for(int i = 0; i < commnets.size(); i++)
        cout << commnets[i].first;
}

User* Film::get_comment_sender(int comment_id) {
    for(int i = 0; i < commnets.size(); i++)
        if(commnets[i].first->get_id() == comment_id)
            return commnets[i].second;
    return NULL;
}

vector<Film*> search(string name, int min_year, int max_year, int min_rate, int price, string director, vector<Film*> input) {
    vector<Film*> search_result = input;
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

void sort_by_rate(vector<Film*>& input) {
    for(int i = 0; i < input.size(); i++) {
        int pos = i;
        Film* max_rate = input[i];
        for(int j = i; j < input.size(); j++) {
            if(input[j]->get_rate() > max_rate->get_rate()) {
                pos = j;
                max_rate = input[j];
            }
            else if(input[j]->get_rate() == max_rate->get_rate())
                if(input[j]->get_id() < max_rate->get_rate()) {
                    pos = j;
                    max_rate = input[j];
                }
        }
        Film* temp = input[i];
        input[i] = max_rate;
        input[pos] = temp;
    }
}



 