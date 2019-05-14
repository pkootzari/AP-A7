#ifndef USER_H_
#define USER_H_

#include <utility>
#include <string>
#include <vector>

class Film;

class User {
public:
    User(int _id, std::string _email, std::string _username, std::string _password, int _age);
    User* vertification(std::string _username, std::string _password);
    virtual void add_film(Film* film) {}
    virtual std::string get_type() {}
    virtual bool delete_film(int film_id) {}
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