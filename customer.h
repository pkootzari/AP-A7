#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include "user.h"
#include "film.h"
#include "publisher.h"

class Publisher;

class Customer : public User {
public:
    Customer(int _id, std::string _email, std::string _username, std::string _password, int _age);
private:
    std::vector<Film*> purchased;
    std::vector<Publisher*> followings;
};

#endif