#ifndef USER_H_
#define USER_H_

#include <utility>
#include <string>
#include <vector>

class User {
public:
    User(int _id, std::string _email, std::string _username, std::string _password, int _age);
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