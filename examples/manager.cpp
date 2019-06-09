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
    recommandator = new Recommandator();
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

void Print_films(vector<Film*> input) {
    for(int i = 0; i < input.size(); i++)
        cout << i + 1 << ". " << input[i]->get_id() << " | " << input[i]->get_name() << " | "
             << input[i]->get_length() << " | " << input[i]->get_director() << endl;
}


int Manager::add_publisher(string email, string username, string password, int age) {
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_username() == username)
            throw BadRequest();
    
    int id = id_user;
    id_user++;
    int pass = hash_str(password.c_str());
    users.push_back( new Publisher(id, email, username, pass, age) );
    return id_user - 1;
}

int Manager::add_customer(string email, string username, string password, int age) {
    for (int i = 0; i < users.size(); i++)
        if(users[i]->get_username() == username)
            throw BadRequest();
    
    int id = id_user;
    id_user++;
    int pass = hash_str(password.c_str());
    users.push_back( new Customer(id, email, username, pass, age) );
    return id_user - 1;
}

int Manager::login(string username, string password) {
    User* temp;
     for(int i = 0; i < users.size(); i++) {
        unsigned pass = hash_str(password.c_str()); 
        temp = users[i]->vertification(username, pass);
        if(temp != NULL)
            break;
    }
    if(temp != NULL)
        return temp->get_id();
    else 
        return -1;
}

void Manager::add_film(string name, int year, int length, int price, string summary, string director, int user_id) {   
    User* cur_user = find_user(user_id);
    int id = films.size() + 1;
    Film* new_film = new Film(id, name, year, length, summary, director, price); 
    cur_user->add_film(new_film);
    films.push_back(new_film);
    recommandator->add_film();
}


void Manager::post_money(int amount, int user_id) {
    User* cur_user = find_user(user_id);
    cur_user->post_money(amount);
}


void Manager::buy_film(int film_id, int user_id) {
    User* cur_user = find_user(user_id);
    Film* bought_film;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id) {
            bought_film = films[i];
            break;
        }
    cur_user->add_to_purchased(bought_film, recommandator);
    cur_user->reduce_money(bought_film->get_price());
    for(int i = 0; i < users.size(); i++)
        if(users[i]->get_type() == "publisher")
            int result = users[i]->film_bought(film_id); 
}


bool Manager::if_is_purchasable(int film_id, int user_id) {
    User* user = find_user(user_id);
    Film* film;
    for(int i = 0; i < films.size(); i++)
        if(films[i]->get_id() == film_id)
            film = films[i];
    if(user->see_money() >= film->get_price())
        return true;
    else
        return false;
}

User* Manager::find_user(int id) {
    for(int i = 0; i < users.size(); i++)
        if(users[i]->get_id() == id)
            return users[i];
    return NULL;
}

vector<Film*> Manager::get_purchased(int user_id) {
    User* user = find_user(user_id);
    vector<Film*> return_value;
    for(int i = 0; i < films.size(); i++)
        if(user->if_film_purchased(films[i]->get_id()))
            return_value.push_back(films[i]);
    return return_value;
}

vector<Film*> Manager::get_published(int user_id) {
    User* user = find_user(user_id);
    vector<Film*> return_value;
    for(int i = 0; i < films.size(); i++)
        if(user->if_film_published(films[i]->get_id()))
            return_value.push_back(films[i]);
    return return_value;
}

vector<Film*> Manager::see_purchaeable_films(int user_id) {
    User* user = find_user(user_id);
    vector<Film*> return_value;
    for(int i = 0; i < films.size(); i++) 
        if(films[i]->get_price() <= user->see_money())
            return_value.push_back(films[i]);
    return return_value;
}

bool Manager::if_purchased(Film* film, int user_id) {
    User* user = find_user(user_id);
    if(user->if_film_purchased(film->get_id()))
        return true;
    else
        return false;
}

void Manager::free() {
    for(int i = 0; i < films.size(); i++)
        delete films[i];
    for(int i = 0; i < users.size(); i++)
        delete users[i];
    for(int i = 0; i < commnets.size(); i++)
        delete commnets[i];
}
