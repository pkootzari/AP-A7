#include "manager.h"

using namespace std;

Manager::Manager() {
    cur_user = NULL;
}

void Manager::add_publisher(string email, string username, string password, int age) {
    int id = users.size() + 1;
    users.push_back( Publisher(id, email, username, password, age) );
    cur_user = &users[users.size() - 1];
}

void Manager::add_customer(string email, string username, string password, int age) {
    int id = users.size() + 1;
    users.push_back( Customer(id, email, username, password, age) );
    cur_user = &users[users.size() - 1];
}
