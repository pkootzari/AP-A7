#include "customer.h"

using namespace std;

Customer::Customer(int _id, string _email, string _username, string _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {}

string Customer::get_type() { return "customer"; }

bool Customer::add_to_following(User* user) {
    bool is_there_already = false;
    for(int i = 0; i < followings.size(); i++)
        if(user->get_id() == followings[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        followings.push_back(user);
    return is_there_already;
}

void Customer::add_to_purchased(Film* film) {
    bool is_there_already = false;
    for(int i = 0; i < purchased.size(); i++)
        if(film->get_id() == purchased[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        purchased.push_back(film);
}

vector<Film*> Customer::see_purchased_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    vector<Film*> search_result = search(name, min_year, max_year, min_rate, price, director, purchased);
    return search_result;
}

Film* Customer::if_film_purchased(int film_id) {
    for(int  i = 0; i < purchased.size(); i++) 
        if(purchased[i]->get_id() == film_id)
            return purchased[i];
    return NULL; 
}

