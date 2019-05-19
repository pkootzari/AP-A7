#include "in_out_handler.h"

using namespace std;

In_out_handler::In_out_handler() {
    manager = new Manager();
}

vector<string> get_command(string input) {
    vector<string> output;
    string part;
    stringstream temp;
    temp << input;
    while(temp >> part)
        output.push_back(part);
    return output;
}

void In_out_handler::signup(vector<string> line_parts) {
    string username;
    string password;
    string email;
    int age;
    bool if_is_publisher = false;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "username" ) 
            username = line_parts[++i];
        else if( line_parts[i] == "password" )
            password = line_parts[++i];
        else if( line_parts[i] == "email" )
            email = line_parts[++i];
        else if( line_parts[i] == "age" )
            age = stoi(line_parts[++i]);
        else if( line_parts[i] == "publisher" ) {
            if( line_parts[i + 1] == "true")
                if_is_publisher = true;
            else if( line_parts[i + 1] == "false" )
                if_is_publisher = false;
        }
    }

    if(if_is_publisher == true)
        manager->add_publisher(email, username, password, age);
    else
        manager->add_customer(email, username, password, age);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::login(vector<string> line_parts) {
    string username;
    string password;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "username" )
            username = line_parts[++i];
        else if( line_parts[i] == "password" )
            password = line_parts[++i];
    }
    manager->login(username, password);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::post_film(vector<string> line_parts) {
    string name;
    string summary;
    string director;
    int year;
    int length;
    int price;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "name" )
            name = line_parts[++i];
        else if( line_parts[i] == "year" )
            year = stoi(line_parts[++i]);
        else if( line_parts[i] == "length" )
            length = stoi(line_parts[++i]);
        else if( line_parts[i] == "price" )
            price = stoi(line_parts[++i]);
        else if( line_parts[i] == "summary" )
            summary = line_parts[++i];
        else if( line_parts[i] == "director" )
            director = line_parts[++i];
    }
    manager->add_film(name, year, length, price, summary, director);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::edit_film(vector<string> line_parts) {
    int film_id;
    string name = "";
    int year = -1;
    int price = -1;
    int length = -1;
    string summary = "";
    string director = "";
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "film_id" )
            film_id = stoi(line_parts[++i]);
        else if( line_parts[i] == "name" )
            name = line_parts[++i];
        else if( line_parts[i] == "year" ) 
            year = stoi(line_parts[++i]);
        else if( line_parts[i] == "length" )
            length = stoi(line_parts[++i]);
        else if( line_parts[i] == "summary" )
            summary = line_parts[++i];
        else if( line_parts[i] == "director" ) 
            director = line_parts[++i];
        else if( line_parts[i] == "price" )
            price = stoi(line_parts[++i]);
    }
    manager->edit_film(film_id, name, year, length, price, summary, director);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::delete_film(vector<string> line_parts) {
    int film_id;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "film_id" )
            film_id = stoi(line_parts[++i]);
        else
            cout << "vorodie kiri" << endl;
    }

    manager->delete_film(film_id);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::get_published_films(vector<string> line_parts) {
    string name = "";
    int min_year = -1;
    int min_rate = -1;
    int price = -1;
    int max_year = -1;
    string director = "";
    for(int  i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "name" )
            name = line_parts[++i];
        else if( line_parts[i] == "min_rate" )
            min_rate = stoi(line_parts[++i]);
        else if( line_parts[i] == "min_year" )
            min_year = stoi(line_parts[++i]);
        else if( line_parts[i] == "max_year" )
            max_year = stoi(line_parts[++i]);
        else if( line_parts[i] == "price" )
            price = stoi(line_parts[++i]);
        else if( line_parts[i] == "director" )
            director = line_parts[++i];
    }
    manager->get_published_films(name, min_year, max_year, min_rate, price, director);
    //cout << DONE_MASSAGE << endl;
}

void In_out_handler::follow_publisher(vector<string> line_parts) {
    int user_id;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "user_id" )
            user_id = stoi(line_parts[++i]);
    }
    manager->follow_publisher(user_id);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::see_followers(vector<string> line_parts) {
    manager->see_followers();
    //cout << DONE_MASSAGE << endl;
}

void In_out_handler::post_money(vector<string> line_parts) {
    int amount = -1;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "amount" )
            amount = stoi(line_parts[++i]);
    }
    manager->post_money(amount);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::search_films(vector<string> line_parts) {
    string name = "";
    int min_year = -1;
    int min_rate = -1;
    int price = -1;
    int max_year = -1;
    string director = "";
    for(int  i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "name" )
            name = line_parts[++i];
        else if( line_parts[i] == "min_rate" )
            min_rate = stoi(line_parts[++i]);
        else if( line_parts[i] == "min_year" )
            min_year = stoi(line_parts[++i]);
        else if( line_parts[i] == "max_year" )
            max_year = stoi(line_parts[++i]);
        else if( line_parts[i] == "price" )
            price = stoi(line_parts[++i]);
        else if( line_parts[i] == "director" )
            director = line_parts[++i];
    }
    manager->search_films(name, min_year, max_year, min_rate, price, director);
    //cout << DONE_MASSAGE << endl;
}

void In_out_handler::buy_film(vector<string> line_parts) {
    int film_id = -1;
    for(int i = 3; i < line_parts.size(); i++) {
        if( line_parts[i] == "film_id" )
            film_id = stoi(line_parts[++i]);
    }
    manager->buy_film(film_id);
    cout << DONE_MASSAGE << endl;
}

void In_out_handler::input_reader() {
    string line;
    while( getline(cin, line) ) {
        vector<string> line_parts = get_command(line);
        string command = line_parts[0];
        if( command == "POST" ) {
            string action = line_parts[1];
            if( action == "signup" )
                signup(line_parts);
            else if( action == "login" )
                login(line_parts);
            else if( action == "films" )
                post_film(line_parts);
            else if( action == "followers" )
                follow_publisher(line_parts);
            else if( action == "money" )
                post_money(line_parts);
            else if( action == "buy" )
                buy_film(line_parts);            
        }
        else if( command == "PUT" ) {
            string action = line_parts[1];
            if( action == "films" )
                edit_film(line_parts);

        }
        else if( command == "DELETE" ) {
            string action = line_parts[1];
            if( action == "films" )
                delete_film(line_parts);
        }
        else if( command == "GET" ) {
            string action = line_parts[1];
            if( action == "published" )
                get_published_films(line_parts);
            else if( action == "followers" )
                see_followers(line_parts);
            else if( action == "films" )
                search_films(line_parts);

        }
    }
}