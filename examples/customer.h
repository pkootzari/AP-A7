#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <iostream>
#include "user.h"
#include "film.h"
#include "publisher.h"

class Publisher;

class Customer : public User {
public:
    Customer(int _id, std::string _email, std::string _username, unsigned _password, int _age);
    virtual std::string get_type();
    virtual bool add_to_following(User* user);
    virtual void add_to_purchased(Film* film, Recommandator* rec);
    virtual std::vector<Film*> see_purchased_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director);
    virtual Film* if_film_purchased(int film_id);
    virtual void reduce_money(int amount);
    virtual void sort_film_by_id(std::vector<Film*>& input);
    virtual void sort_user_by_id(std::vector<User*>& input);
    virtual int see_money();
private:
    std::vector<Film*> purchased;
    std::vector<User*> followings;
};

#endif