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
    virtual std::vector<Film*> get_published_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director);
    virtual void add_to_followers(User* user);
    virtual void add_to_following(User* user);
private:
    int deposible_money;
    std::vector<Film*> published;
    std::vector<Film*> purchased;
    std::vector<User*> followings;
    std::vector<User*> followers;
};

#endif