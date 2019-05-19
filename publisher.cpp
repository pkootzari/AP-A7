#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {
            withdrawable_money = 0;
    }

void Publisher::add_film(Film* film) {
     published.push_back(film);
}

string Publisher::get_type() { return "publisher"; }

bool Publisher::delete_film(int film_id) {
    for(int i = 0; i < published.size(); i++)
        if(published[i]->get_id() == film_id) {
            published.erase(published.begin() + i);
            return true;
        }
    return false;
}

vector<Film*> Publisher::get_published_films(string name, int min_year, int max_year, int min_rate, int price,  string director) {
    vector<Film*> search_result = search(name, min_year, max_year, min_rate, price, director, published);
    return search_result;
}

void Publisher::add_to_followers(User* user) {
    followers.push_back(user);
}

void Publisher::add_to_following(User* user) {
    followings.push_back(user);
}

void Publisher::see_followers() {
    for(int i = 0; i < followers.size(); i++)
        cout << i + 1 << ". " << followers[i];
}

void Publisher::get_money() {
    withdrawable_money = 0;
}