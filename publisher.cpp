#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id, std::string _email, std::string _username, unsigned _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {
            withdrawable_money = 0;
    }

void Publisher::add_film(Film* film) {
    published.push_back(film);
    string content = "";
    content += "Publisher ";  content += this->username;  content += " with id ";  content += to_string(this->id);
    content += " register new film.";
    for(int i = 0; i < followings.size(); i++)
        followings[i]->add_notif(content);
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
    bool is_there_already = false;
    for(int i = 0; i < followers.size(); i++)
        if(user->get_id() == followers[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        followers.push_back(user);
}

bool Publisher::add_to_following(User* user) {
    bool is_there_already = false;
    for(int i = 0; i < followings.size(); i++)
        if(user->get_id() == followings[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        followings.push_back(user);
    return is_there_already;
}

void Publisher::see_followers() {
    sort_user_by_id(followers);
    for(int i = 0; i < followers.size(); i++)
        cout << i + 1 << ". " << followers[i];
}

void Publisher::get_money() {
    //cout << "money withdrawed: " << withdrawable_money << endl; 
    withdrawable_money = 0;
}

void Publisher::add_to_purchased(Film* film) {
    bool is_there_already = false;
    for(int i = 0; i < purchased.size(); i++)
        if(film->get_id() == purchased[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        purchased.push_back(film);
}

int Publisher::film_bought(int film_id) {
    int return_value = 0;
    for(int i = 0; i < published.size(); i++)
        if(published[i]->get_id() == film_id) {
            return_value = published[i]->get_price() - calculate_money(published[i]);
            withdrawable_money += calculate_money(published[i]);
            break;
        }
    return return_value;
}

vector<Film*> Publisher::see_purchased_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    vector<Film*> search_result = search(name, min_year, max_year, min_rate, price, director, purchased);
    sort_film_by_id(search_result);
    return search_result;
}

Film* Publisher::if_film_purchased(int film_id) {
    for(int i = 0; i < purchased.size(); i++)
        if(purchased[i]->get_id() == film_id)
            return purchased[i];
    return NULL; 
}

Film* Publisher::if_film_published(int film_id) {
    for(int i = 0; i < published.size(); i++)
        if(published[i]->get_id() == film_id)
            return published[i];
    return NULL;
}

int calculate_money(Film* film) {
    if(film->get_rate() < 5 && film->get_rate() >= 0)
        return 80*film->get_price()/100;
    if(film->get_rate() < 8 && film->get_rate() >= 5)
        return 90*film->get_price()/100;
    if(film->get_rate() >= 8 && film->get_rate() <= 10)
        return 95*film->get_price()/100;
    else 
        cout << "rate beyne 0 ta 10 nist" << endl;
}

void Publisher::reduce_money(int amount) {
    if(spendable_money - amount < 0)
        throw PermissionDenied();
    else
        spendable_money -= amount; 
}

void Publisher::sort_film_by_id(vector<Film*>& input) {
    for(int i = 0; i < input.size(); i++) {
        Film* cur = input[i];
        int pos = i;
        for(int j = i; j < input.size(); j++) 
            if(input[j]->get_id() < input[i]->get_id()) {
                pos = j;
                cur = input[j];
            }
        Film* temp = input[i];
        input[i] = cur;
        input[pos] = temp;
    }
}

void Publisher::sort_user_by_id(vector<User*>& input) {
    for(int i = 0; i < input.size(); i++) {
        User* cur = input[i];
        int pos = i;
        for(int j = i; j < input.size(); j++) 
            if(input[j]->get_id() < input[i]->get_id()) {
                pos = j;
                cur = input[j];
            }
        User* temp = input[i];
        input[i] = cur;
        input[pos] = temp;
    }
}
