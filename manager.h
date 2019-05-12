#ifndef MANAGER_H_
#define MANAGER_H_

#include <string>
#include <vector>
#include "user.h"
#include "publisher.h"
#include "customer.h"
#include "film.h"
#include "comment.h"

class Manger {
public:
    Manger();
private:
    User* cur_user;
    std::vector<User> users;
    std::vector<Film> films;
    std::vector<Comment*> commnets;
}; 

#endif