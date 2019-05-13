#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include <string>
#include <vector>
#include "user.h"
#include "film.h"
#include "customer.h"

class Customer;

class Publisher : public User {
public:
    Publisher(int _id, std::string _email, std::string _username, std::string _password, int _age);
private:
    int deposible_money;
    std::vector<Film*> published;
    std::vector<Film*> purchased;
    std::vector<Publisher*> followings;
    std::vector<Customer*> followers;
};

#endif