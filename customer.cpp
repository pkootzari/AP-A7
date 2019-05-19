#include "customer.h"

using namespace std;

Customer::Customer(int _id, string _email, string _username, string _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {}

string Customer::get_type() { return "customer"; }

void Customer::add_to_following(User* user) {
    bool is_there_already = false;
    for(int i = 0; i < followings.size(); i++)
        if(user->get_id() == followings[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        followings.push_back(user);
}

void Customer::add_to_purchased(Film* film) {
    bool is_there_already = false;
    for(int i = 0; i < purchased.size(); i++)
        if(film->get_id() == purchased[i]->get_id())
            is_there_already = true;
    if(!is_there_already)
        purchased.push_back(film);
}