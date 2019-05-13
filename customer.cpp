#include "customer.h"

using namespace std;

Customer::Customer(int _id, string _email, string _username, string _password, int _age) 
    :   User(_id, _email, _username, _password, _age) {}

string Customer::get_type() { return "customer"; }