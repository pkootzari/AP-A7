#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <string>
#include <vector>
#include <iostream>
#include "user.h"
#include "film.h"
#include "customer.h"

class Customer;

class Publisher : public User {
public:
    Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age);
    virtual void add_film(Film* film);
    virtual std::string get_type();
    virtual bool delete_film(int film_id);
private:
    int deposible_money;
    std::vector<Film*> published;
    std::vector<Film*> purchased;
    std::vector<Publisher*> followings;
    std::vector<Customer*> followers;
};

#endif