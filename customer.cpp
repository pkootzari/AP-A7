#include "customer.h"

using namespace std;

Customer::Customer(int _id, std::string _email, std::string _username, std::string _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {}