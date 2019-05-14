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
            
        }
        else if( command == "PUT" ) {
            string action = line_parts[1];
            if( action == "films" )
                edit_film(line_parts);

        }
        else if( command == "DELETE" ) {

        }
        else if( command == "GET" ) {

        }
    }
}