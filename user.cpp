#include "user.h"

using namespace std;

User::User(int _id, std::string _email, std::string _username, unsigned _password, int _age) 
    :   id(_id) , email(_email) , username(_username) , password(_password) , age(_age) {
            spendable_money = 0;
    }

User* User::vertification(string _username, unsigned _password) {
     if(username == _username && password == _password)
        return this;
     return NULL;
}

int User::get_id() { return id; }
string User::get_username() { return username; }

void User::post_money(int amount) {
    spendable_money += amount;
}

void User::add_notif(string conetnt) {
    notifs.push_back( make_pair(conetnt, false) );
}

void User::see_notifs() {
    cout << "#. Notification Message" << endl;
    for(int i = notifs.size() - 1, j = 1; i >= 0; i--) {
        if(notifs[i].second == false) {
            notifs[i].second = true;
            cout << j << ". " << notifs[i].first << endl;
            j++;
        }
        else 
            break;
    }
}

void User::read_notifs(int limit) {
    int j = 1;
    for(int i = notifs.size() - 1; i >= 0 && limit > 0; i--, limit--) {
        cout << j << ". " << notifs[i].first << endl;
        j++;
    }
}

ostream& operator<<(ostream& out, User* user) {
    out << user->id << " | " << user->username << " | " << user->email << endl;
}