#include "user.h"

using namespace std;

User::User(int _id, std::string _email, std::string _username, std::string _password, int _age) 
    :   id(_id) , email(_email) , username(_username) , password(_password) , age(_age) {
            spendable_money = 0;
    }

User* User::vertification(string _username, string _password) {
     if(username == _username && password == _password)
        return this;
     return NULL;
}

int User::get_id() { return id; }

void User::post_money(int amount) {
    spendable_money += amount;
}

ostream& operator<<(ostream& out, User* user) {
    out << user->id << " | " << user->username << " | " << user->email << endl;
}