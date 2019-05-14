#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {
            deposible_money = 0;
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