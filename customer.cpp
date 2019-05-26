#include "customer.h"

using namespace std;

Customer::Customer(int _id, string _email, string _username, unsigned _password, int _age) 
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

void Customer::add_to_purchased(Film* film, Recommandator* rec) {
    bool is_there_already = false;
    for(int i = 0; i < purchased.size(); i++)
        if(film->get_id() == purchased[i]->get_id())
            is_there_already = true;
    if(!is_there_already) {
        vector<int> film_ids;
        for(int j = 0; j < purchased.size(); j++)
            film_ids.push_back(purchased[j]->get_id());
        rec->buy_film(film->get_id(), film_ids);
        purchased.push_back(film);
    }
}

vector<Film*> Customer::see_purchased_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    vector<Film*> search_result = search(name, min_year, max_year, min_rate, price, director, purchased);
    sort_film_by_id(search_result);
    return search_result;
}

Film* Customer::if_film_purchased(int film_id) {
    for(int  i = 0; i < purchased.size(); i++) 
        if(purchased[i]->get_id() == film_id)
            return purchased[i];
    return NULL; 
}

void Customer::reduce_money(int amount) {
    if(spendable_money - amount < 0)
        throw PermissionDenied();
    else
        spendable_money -= amount;
}

int Customer::see_money() { return spendable_money; }

void Customer::sort_film_by_id(vector<Film*>& input) {
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

void Customer::sort_user_by_id(vector<User*>& input) {
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

