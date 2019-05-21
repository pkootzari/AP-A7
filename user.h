#ifndef USER_H_
#define USER_H_

#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include "exeptions.h"

class Film;

class User {
public:
    User(int _id, std::string _email, std::string _username, std::string _password, int _age);
    int get_id();
    std::string get_username();
    User* vertification(std::string _username, std::string _password);
    virtual void add_film(Film* film) {}
    virtual std::string get_type() {}
    virtual bool delete_film(int film_id) {}
    virtual std::vector<Film*> get_published_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director) {}
    virtual void add_to_followers(User* user) {}
    virtual bool add_to_following(User* user) {}
    virtual void see_followers() {}
    virtual void get_money() {}
    virtual void add_to_purchased(Film* film) {}
    virtual bool film_bought(int film_id) {}
    virtual std::vector<Film*> see_purchased_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director) {}
    virtual Film* if_film_purchased(int film_id) {}
    virtual Film* if_film_published(int film_id) {}
    virtual void reduce_money(int amount) {}
    void post_money(int amount);
    void add_notif(std::string content);
    void see_notifs();
    void read_notifs(int limit);
    friend std::ostream& operator<<(std::ostream& out, User* user);
protected:
    int id;
    int spendable_money;
    std::string email;
    std::string username;
    std::string password;
    std::vector< std::pair <std::string, bool> > notifs;
    int age;
};

#endif