#include "manager.h"

using namespace std;

Manager::Manager() {
    id_comment = 1;
    id_film = 1;
    id_user = 1;
    cur_user = NULL;
}

void Manager::add_publisher(string email, string username, string password, int age) {
    int id = id_user;
    id_user++;
    users.push_back( new Publisher(id, email, username, password, age) );
    cur_user = users[users.size() - 1];
}

void Manager::add_customer(string email, string username, string password, int age) {
    int id = id_user;
    id_user++;
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
    Film* new_film = new Film(id, name, year, length, summary, director, price); 
    
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

void Manager::get_published_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    if(cur_user->get_type() != "publisher")
        cout << "nmitoni ddsh" << endl;
    else {
        vector<Film*> search_result = cur_user->get_published_films(name, min_year, max_year, min_rate, price, director);
        cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
        for(int  i = 0; i < search_result.size(); i++)
            cout << i + 1 << ". " << search_result[i];
    }
}

void Manager::follow_publisher(int user_id) {
    for(int  i = 0; i < users.size(); i++) {
        if(users[i]->get_id() == user_id) {
            if(users[i]->get_type() == "publisher") {
                cur_user->add_to_following(users[i]);
                users[i]->add_to_followers(cur_user);
            }
            else
                cout << "pointed user is not publisher" << endl;
        }
    }
}

void Manager::see_followers() {
    if(cur_user->get_type() != "publisher")
        cout << "publisher nisti ddsh" << endl;
    else {
        cout << "List of Followers" << endl;
        cout << "#. User Id | User Username | User Email" << endl;
        cur_user->see_followers();
    }
}

void Manager::post_money(int amount) {
    if(amount != -1)
        cur_user->post_money(amount);
    else {
        if(cur_user->get_type() == "publisher")
            cur_user->get_money();
        else
            cout << "publisher nisti ddsh" << endl;
    }
}

void Manager::search_films(string name, int min_year, int max_year, int min_rate, int price,  string director) {
    vector<Film*> search_result = search(name, min_year, max_year, min_rate, price, director, films);
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
        for(int  i = 0; i < search_result.size(); i++)
            cout << i + 1 << ". " << search_result[i];
}

void Manager::buy_film(int film_id) {
    int i;
    for(i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            cur_user->add_to_purchased(films[i]);
            break;
        }
    if(i == films.size())
        cout << "filmet nist ddsh" << endl;
    else
        for(i = 0; i < users.size(); i++)
            if(users[i]->get_type() == "publisher")
                if(users[i]->film_bought(film_id))
                    break;
}

void Manager::see_purchased_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    vector<Film*> search_result = cur_user->see_purchased_films(name, min_year, max_year, min_rate, price, director);
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
    for(int  i = 0; i < search_result.size(); i++)
        cout << i + 1 << ". " << search_result[i];
}

void Manager::rate_film(int film_id, int score) {
    Film* rated_film = cur_user->if_film_purchased(film_id);
    if(rated_film == NULL)
        cout << "filmo ndri ddsh" << endl;
    else 
        rated_film->rate_this(cur_user->get_id(), score);
}

void Manager::send_comment(int film_id, string content) {
    Film* commented_film = cur_user->if_film_purchased(film_id);
    if(commented_film == NULL)
        cout << "filmo ndri ddsh" << endl;
    else
        commented_film->add_comment(content);
}

void Manager::reply_comment(int film_id, int comment_id, string content) {
    Film* commneted_film = cur_user->if_film_published(film_id);
    if(commneted_film == NULL)
        cout << "filmo publish nkrdi ddsh" << endl;
    else
        commneted_film->add_reply(content, comment_id);
}

