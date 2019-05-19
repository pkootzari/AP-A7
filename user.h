#ifndef USER_H_
#define USER_H_

#include <utility>
#include <string>
#include <vector>
#include <iostream>

class Film;

class User {
public:
    User(int _id, std::string _email, std::string _username, std::string _password, int _age);
    int get_id();
    User* vertification(std::string _username, std::string _password);
    virtual void add_film(Film* film) {}
    virtual std::string get_type() {}
    virtual bool delete_film(int film_id) {}
    virtual std::vector<Film*> get_published_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director) {}
    virtual void add_to_followers(User* user) {}
    virtual void add_to_following(User* user) {}
    virtual void see_followers() {}
    void post_money(int amount);
    friend std::ostream& operator<<(std::ostream& out, User* user);
private:
    int id;
    int spendable_money;
    std::string email;
    std::string username;
    std::string password;
    std::vector< std::pair <std::string, bool> > notifs;
    int age;
};

#endif