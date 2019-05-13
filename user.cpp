#include "user.h"

using namespace std;

User::User(int _id, std::string _email, std::string _username, std::string _password, int _age) 
    :   id(_id) , email(_email) , username(_username) , password(_password) , age(_age) {
            spendable_money = 0;
    }