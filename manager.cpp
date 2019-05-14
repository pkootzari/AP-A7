#include "manager.h"

using namespace std;

Manager::Manager() {
    cur_user = NULL;
}

void Manager::add_publisher(string email, string username, string password, int age) {
    int id = users.size() + 1;
    users.push_back( new Publisher(id, email, username, password, age) );
    cur_user = users[users.size() - 1];
}

void Manager::add_customer(string email, string username, string password, int age) {
    int id = users.size() + 1;
    users.push_back( new Customer(id, email, username, password, age) );
    cur_user = users[users.size() - 1];
}

void Manager::login(string username, string password) {
    User* temp;
     for(int i = 0; i < users.size(); i++) {
        temp = users[i]->vertification(username, password);
        if(temp != NULL)
            break;
    }
    if(temp != NULL) 
        cur_user = temp;
}

void Manager::add_film(string name, int year, int length, int price, string summary, string director) {
    int id = films.size() + 1;
    Film* new_film = new Film(id, name, year, length, summary, director); 
    
    if(cur_user->get_type() == "publisher")
        cur_user->add_film(new_film);
    else if(cur_user->get_type() == "customer")
        cout << "ridi ddsh" << endl;
    
    films.push_back(new_film);
}

void Manager::edit_film(int film_id, string name, int year, int length, int price, string summary, string director) {
    int i;
    for(i = 0; i < films.size(); i++) {
        if(films[i]->get_id() == film_id) {
            films[i]->edit_film(name, year, length, price, summary, director);
            break;
        }
    }
    if(i == films.size())
        cout << "ridi ddsh" << endl;
}

void Manager::delete_film(int film_id) {
    int i;
    for(i = 0; i < films.size(); i++) 
        if(films[i]->get_id() == film_id) {
            films.erase(films.begin() + i);
            break;
        }
    
    if(cur_user->get_type() == "publisher")
        cur_user->delete_film(film_id);
    else
        cout << "nmitoni ddsh" << endl;
}