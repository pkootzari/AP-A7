#include "manager.h"

using namespace std;

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
unsigned hash_str(const char* s)
{
   unsigned h = FIRSTH;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}

Manager::Manager() {
    id_comment = 1;
    id_film = 1;
    id_user = 1;
    cur_user = NULL;
}

bool Manager::if_id_exist(int id) {
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == id)
            return true;
    return false;
}

void print_film_details(Film* film) {
    cout << "Id = " << film->get_id() << endl;
    cout << "Director = " << film->get_director() << endl;
    cout << "Length = " << film->get_length() << endl;
    cout << "Year = " << film->get_year() << endl;
    cout << "Summary = " << film->get_summary() << endl;
    cout << "Rate = " << film->get_rate() << endl;
    cout << "Price = " << film->get_price() << endl; 
}

void Manager::add_publisher(string email, string username, string password, int age) {
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_username() == username)
            throw BadRequest();
    
    int id = id_user;
    id_user++;
    int pass = hash_str(password.c_str());
    users.push_back( new Publisher(id, email, username, pass, age) );
    cur_user = users[users.size() - 1];
}

void Manager::add_customer(string email, string username, string password, int age) {
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_username() == username)
            throw BadRequest();
    
    int id = id_user;
    id_user++;
    int pass = hash_str(password.c_str());
    users.push_back( new Customer(id, email, username, pass, age) );
    cur_user = users[users.size() - 1];
}

void Manager::login(string username, string password) {
    User* temp;
     for(int i = 0; i < users.size(); i++) {
        int pass = hash_str(password.c_str()); 
        temp = users[i]->vertification(username, pass);
        if(temp != NULL)
            break;
    }
    if(temp != NULL) 
        cur_user = temp;
    else 
        throw BadRequest();
}

void Manager::add_film(string name, int year, int length, int price, string summary, string director) {
    if(cur_user != NULL) {
        if(cur_user->get_type() == "publisher") {
            int id = films.size() + 1;
            Film* new_film = new Film(id, name, year, length, summary, director, price); 
            cur_user->add_film(new_film);
            films.push_back(new_film);
        }
        else 
            throw PermissionDenied();
    }
    else
        throw PermissionDenied();
}

void Manager::edit_film(int film_id, string name, int year, int length, int price, string summary, string director) {
    if(cur_user == NULL)
        throw PermissionDenied();
    if(cur_user->get_type() != "publisher")
        throw PermissionDenied();
    if(cur_user->if_film_published(film_id) == NULL)
        throw PermissionDenied();
    
    int i;
    bool is_found = false;
    for(i = 0; i < films.size(); i++) {
        if(films[i]->get_id() == film_id) {
            films[i]->edit_film(name, year, length, price, summary, director);
            is_found = true;
            break;
        }
    }
    if(!is_found)
        throw NotFound();
}

void Manager::delete_film(int film_id) {
    if(cur_user == NULL)
        throw PermissionDenied();
    if(cur_user->get_type() != "publisher")
        throw PermissionDenied();
    if(cur_user->if_film_published(film_id) == NULL)
        throw PermissionDenied();
    
    int i;
    bool is_found = false;
    for(i = 0; i < films.size(); i++) 
        if(films[i]->get_id() == film_id) {
            films.erase(films.begin() + i);
            cur_user->delete_film(film_id);
            is_found = true;
            break;
        }
    if(!is_found)
        throw NotFound();
}

void Manager::get_published_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    if(cur_user == NULL)
        throw PermissionDenied();
    if(cur_user->get_type() != "publisher")
        throw PermissionDenied();
    else {
        vector<Film*> search_result = cur_user->get_published_films(name, min_year, max_year, min_rate, price, director);
        cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
        for(int  i = 0; i < search_result.size(); i++)
            cout << i + 1 << ". " << search_result[i];
    }
}

void Manager::follow_publisher(int user_id) {
    if(cur_user == NULL)
        throw PermissionDenied();
    for(int i = 0; i < users.size(); i++)
        if(users[i]->get_id() == user_id)
            if(users[i]->get_type() != "publisher")
                throw BadRequest();
    
    string content = "";
    content += "User ";  content += cur_user->get_username(); content += " with id "; content += to_string(cur_user->get_id());
    content += " follow you.";
    for(int  i = 0; i < users.size(); i++) {
        if(users[i]->get_id() == user_id) {
            if(users[i]->get_type() == "publisher") {
                if(!cur_user->add_to_following(users[i]))
                    users[i]->add_to_followers(cur_user);
                    users[i]->add_notif(content);
            }
        }
    }
}

void Manager::see_followers() {
    if(cur_user == NULL)
        throw PermissionDenied();
    if(cur_user->get_type() != "publisher")
        throw PermissionDenied();
    else {
        cout << "List of Followers" << endl;
        cout << "#. User Id | User Username | User Email" << endl;
        cur_user->see_followers();
    }
}

void Manager::post_money(int amount) {
    if(cur_user == NULL)
        throw PermissionDenied();
    
    if(amount != -1)
        cur_user->post_money(amount);
    else {
        if(cur_user->get_type() == "publisher")
            cur_user->get_money();
        else
            throw PermissionDenied();
    }
}

void Manager::search_films(string name, int min_year, int max_year, int min_rate, int price,  string director) {
    if(cur_user == NULL)
        throw PermissionDenied();
    
    vector<Film*> search_result = search(name, min_year, max_year, min_rate, price, director, films);
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
        for(int  i = 0; i < search_result.size(); i++)
            cout << i + 1 << ". " << search_result[i];
}

void Manager::buy_film(int film_id) {
    if(cur_user == NULL)
        throw PermissionDenied();
    
    bool if_found = false;
    Film* bought_film;
    string content = "";
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            cur_user->add_to_purchased(films[i]);
            bought_film = films[i];
            if_found = true;
            break;
        }
    if(!if_found)
        throw NotFound();
    else {
        if(cur_user->if_film_purchased(film_id) == NULL) {
            cur_user->reduce_money(bought_film->get_price());
            content += "User "; content += cur_user->get_username(); content += " with id "; content += to_string(cur_user->get_id());
            content += " buy your film "; content += bought_film->get_name(); content += " with id "; content += to_string(bought_film->get_id());
            content += ".";
            for(int i = 0; i < users.size(); i++)
                if(users[i]->get_type() == "publisher")
                    if(users[i]->film_bought(film_id)) {
                        users[i]->add_notif(content);
                        break;
                    }
        }
    }
}

void Manager::see_purchased_films(string name, int min_year, int max_year, int min_rate, int price, string director) {
    if(cur_user == NULL)
        throw PermissionDenied();
    vector<Film*> search_result = cur_user->see_purchased_films(name, min_year, max_year, min_rate, price, director);
    cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << endl;
    for(int  i = 0; i < search_result.size(); i++)
        cout << i + 1 << ". " << search_result[i];
}

void Manager::rate_film(int film_id, int score) {
    if(cur_user == NULL)
        throw PermissionDenied();

    bool if_exist = false;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            if_exist = true;
            break;
        }
    if(!if_exist)
        throw NotFound();

    Film* rated_film = cur_user->if_film_purchased(film_id);
    if(rated_film == NULL)
        throw PermissionDenied();
    if(score < 0 || score > 10) 
        throw BadRequest();
    else {
        string content = "";
        content += "User "; content += cur_user->get_username(); content += " with id "; content += to_string(cur_user->get_id());
        content += " rate your film "; content += rated_film->get_name(); content += " with id "; content += to_string(rated_film->get_id());
        content += ".";
        rated_film->rate_this(cur_user->get_id(), score);
        for(int i = 0; i < users.size(); i++)
            if(users[i]->get_type() == "publisher")
                if(users[i]->if_film_published(film_id) != NULL) {
                    users[i]->add_notif(content);
                    break;
                }
    }
}

void Manager::send_comment(int film_id, string content) {
    if(cur_user == NULL)
        throw PermissionDenied();
    
    bool if_exist = false;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            if_exist = true;
            break;
        }
    if(!if_exist)
        throw NotFound();

    Film* commented_film = cur_user->if_film_purchased(film_id);
    if(commented_film == NULL)
        throw PermissionDenied();
    else {
        string content = "";
        content += "User "; content += cur_user->get_username(); content += " with id "; content += to_string(cur_user->get_id());
        content += " comment on your film "; content += commented_film->get_name(); content += " with id "; content += to_string(commented_film->get_id());
        content += ".";
        for(int i = 0; i < users.size(); i++)
            if(users[i]->get_type() == "publisher")
                if(users[i]->if_film_published(film_id) != NULL) {
                    users[i]->add_notif(content);
                    break;
                }
        commented_film->add_comment(content, cur_user);
    }
}

void Manager::reply_comment(int film_id, int comment_id, string content) {
    if(cur_user == NULL)
        throw PermissionDenied();
    
    bool if_exist = false;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            if_exist = true;
            break;
        }
    if(!if_exist)
        throw NotFound();
    
    Film* commneted_film = cur_user->if_film_published(film_id);
    if(commneted_film == NULL)
        throw PermissionDenied();
    else {
        commneted_film->add_reply(content, comment_id);
        User* comment_owner = commneted_film->get_comment_sender(comment_id);
        if(comment_owner == NULL)
            throw NotFound();
        else {
            string content = "";
            content += "Publisher ";  content += cur_user->get_username();  content += " with id ";  content += to_string(cur_user->get_id());
            content += " reply to your comment.";
            comment_owner->add_notif(content);
        }
    }
}

void Manager::delete_comment(int film_id, int comment_id) {
    if(cur_user == NULL)
        throw PermissionDenied();

    bool if_exist = false;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            if_exist = true;
            break;
        }
    if(!if_exist)
        throw NotFound();
    
    Film* commented_film = cur_user->if_film_published(film_id);
    if(commented_film == NULL)
        throw PermissionDenied();
    else
        commented_film->delete_comment(comment_id);
}

void Manager::see_details(int film_id) {
    if(cur_user == NULL)
        throw PermissionDenied();
    
    Film* desired_film = NULL;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            desired_film = films[i];
            break;
        }
    if(desired_film == NULL)
        throw NotFound();
    else {
        cout << "Details of Film " << desired_film->get_name() << endl;
        print_film_details(desired_film);
        cout << endl;
        cout << "Comments" << endl;
        desired_film->print_comments();
        cout << endl;
        cout << "Recommendation Film" << endl;
        cout << "#. Film Id | Film Name | Film Length | Film Director" << endl;
        print_recommandations(desired_film);
    }
}

void Manager::print_recommandations(Film* except_this) {
    vector<Film*> input = films;
    sort_by_rate(input);
    for(int i = 0, count = 1; i < input.size() && count <= 4; i++) {
        if(input[i] != except_this && cur_user->if_film_purchased(input[i]->get_id()) == NULL) {
            cout << count << ". " << input[i]->get_id() << " | " << input[i]->get_name() << " | "
                 << input[i]->get_length() << " | " << input[i]->get_director() << endl;;
            count ++;
        }
    }
}

void Manager::see_notifs() {
    if(cur_user == NULL)
        cout << "permision denide" << endl;
    else 
        cur_user->see_notifs();
}

void Manager::read_notifs(int limit) {
    if(cur_user == NULL)
        cout << "permision denide" << endl;
    else
        cur_user->read_notifs(limit);
}

void Manager::sort_film_by_id(vector<Film*>& input) {
    for(int i = 0; i < input.size(); i++) {
        Film* cur = input[i];
        int pos = i;
        for(int j = i; j < input.size(); j++) 
            if(input[j]->get_id() < input[i]->get_id()) {
                pos = j;
                cur = input[j];
            }
        Film* temp = input[i];
        input[i] = cur;
        input[pos] = temp;
    }
}

void Manager::sort_user_by_id(vector<User*>& input) {
    for(int i = 0; i < input.size(); i++) {
        User* cur = input[i];
        int pos = i;
        for(int j = i; j < input.size(); j++) 
            if(input[j]->get_id() < input[i]->get_id()) {
                pos = j;
                cur = input[j];
            }
        User* temp = input[i];
        input[i] = cur;
        input[pos] = temp;
    }
}

void Manager::free() {
    for(int i = 0; i < films.size(); i++)
        delete films[i];
    for(int i = 0; i < users.size(); i++)
        delete users[i];
    for(int i = 0; i < commnets.size(); i++)
        delete commnets[i];
}