#ifndef MANAGER_H_
#define MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "publisher.h"
#include "customer.h"
#include "film.h"
#include "comment.h"

class Manager {
public:
    Manager();
    void add_publisher(std::string email, std::string username, std::string password, int age);
    void add_customer(std::string email, std::string username, std::string password, int age);
    void login(std::string username, std::string password);
    void add_film(std::string name, int year, int length, int price, std::string summary, std::string director);
private:
    User* cur_user;
    std::vector<User*> users;
    std::vector<Film*> films;
    std::vector<Comment*> commnets;
}; 

#endif