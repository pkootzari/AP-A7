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

bool is_number(string input) {
    for(int i = 0; i < input.size(); i++)
        if(input[i]<48 || input[i]>57)
            throw BadRequest();
    return true;
}

bool if_publisher(string input) {
    if(input != "true" && input != "false")
        throw BadRequest();
    else if(input == "true")
        return true;
    else 
        return false;
}

bool isemailvalid(const string& email)
{
   const std::regex pattern ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return std::regex_match(email, pattern);
}


map<string, string> In_out_handler::process_command(vector<string> line_parts) {
    map<string, string> result;
    result["username"] = "";
    result["password"] = "";
    result["email"] = "";
    result["age"] = "";
    result["publisher"] = "";
    result["year"] = "";
    result["length"] = "";
    result["price"] = "";
    result["summary"] = "";
    result["director"] = "";
    result["min_rate"] = "";
    result["min_year"] = "";
    result["max_year"] = "";
    result["film_id"] = "";
    result["user_id"] = "";
    result["amount"] = "";
    result["content"] = "";
    result["score"] = "";
    result["comment_id"] = "";
    result["name"] = "";
    result["limit"] = "";
    result["year"] = "";
    result["rate"] = "";

    for(int i = 3; i < line_parts.size(); i++)
        for(auto itr = result.begin(); itr != result.end(); itr++)
            if(line_parts[i] == itr->first) {
                if(itr->second == "")
                    itr->second = line_parts[++i];
                else
                    throw BadRequest();
            }
    return result;
}

void In_out_handler::signup(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        string username;
        string password;
        string email;
        bool if_is_publisher = false;
        int age;
        input["username"] != "" ? username = input["username"] : throw BadRequest();
        input["password"] != "" ? password = input["password"] : throw BadRequest();
        input["email"] != "" && isemailvalid(input["email"]) ? email = input["email"] : throw BadRequest();
        input["age"] != "" && is_number(input["age"]) ? age = stoi(input["age"]) : throw BadRequest();
        input["publisher"] != "" ? if_is_publisher = if_publisher(input["publisher"]) : if_is_publisher = false;
        if(if_is_publisher == true)
            manager->add_publisher(email, username, password, age);
        else
            manager->add_customer(email, username, password, age);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::login(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        string username;
        string password;
        input["username"] != "" ? username = input["username"] : throw BadRequest();
        input["password"] != "" ? password = input["password"] : throw BadRequest();
        manager->login(username, password);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::post_film(vector<string> line_parts) {
    try{
        map<string, string> input = process_command(line_parts);
        string name;
        string summary;
        string director;
        int year;
        int length;
        int price;
        input["name"] != "" ? name = input["name"] : throw BadRequest();
        input["summary"] != "" ? summary = input["summary"] : throw BadRequest();
        input["director"] != "" ? director = input["director"] : throw BadRequest();
        input["year"] != "" && is_number(input["year"]) ? year = stoi(input["year"]) : throw BadRequest();
        input["length"] != "" && is_number(input["length"]) ? length = stoi(input["length"]) : throw BadRequest();
        input["price"] != "" && is_number(input["price"]) ? price = stoi(input["price"]) : throw BadRequest();
        manager->add_film(name, year, length, price, summary, director);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::edit_film(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        int film_id;
        string name = "";
        int year = -1;
        int price = -1;
        int length = -1;
        string summary = "";
        string director = "";
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        input["name"] != "" ? name = input["name"] : name = "";
        input["summary"] != "" ? summary = input["summary"] : summary = "";
        input["director"] != "" ? director = input["director"] : director = "";
        input["year"] != "" && is_number(input["year"]) ? year = stoi(input["year"]) : year = -1;
        input["price"] != "" && is_number(input["price"]) ? price = stoi(input["price"]) : price = -1;
        input["length"] != "" && is_number(input["length"]) ? length = stoi(input["length"]) : length = -1;
        manager->edit_film(film_id, name, year, length, price, summary, director);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::delete_film(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        int film_id;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        manager->delete_film(film_id);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::get_published_films(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        string name = "";
        int min_year = -1;
        int max_year = -1;
        int min_rate = -1;
        int price = -1;
        int length = -1;
        string summary = "";
        string director = "";
        input["name"] != "" ? name = input["name"] : name = "";
        input["summary"] != "" ? summary = input["summary"] : summary = "";
        input["director"] != "" ? director = input["director"] : director = "";
        input["min_year"] != "" && is_number(input["min_year"]) ? min_year = stoi(input["min_year"]) : min_year = -1;
        input["max_year"] != "" && is_number(input["max_year"]) ? max_year = stoi(input["max_year"]) : max_year = -1;
        input["min_rate"] != "" && is_number(input["min_rate"]) ? min_rate = stoi(input["min_rate"]) : min_rate = -1;
        input["price"] != "" && is_number(input["price"]) ? price = stoi(input["price"]) : price = -1;
        input["length"] != "" && is_number(input["length"]) ? length = stoi(input["length"]) : length = -1;
        manager->get_published_films(name, min_year, max_year, min_rate, price, director);
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::follow_publisher(vector<string> line_parts) {
    try{
        map<string, string> input = process_command(line_parts);
        int user_id;
        input["user_id"] != "" && is_number(input["user_id"]) ? user_id = stoi(input["user_id"]) : throw BadRequest();
        manager->follow_publisher(user_id);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::see_followers(vector<string> line_parts) {
    manager->see_followers();
}

void In_out_handler::post_money(vector<string> line_parts) {
    try{
        map<string, string> input = process_command(line_parts);
        int amount;
        input["amount"] != "" && is_number(input["amount"]) ? amount = stoi(input["amount"]) : throw BadRequest();
        manager->post_money(amount);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::search_films(vector<string> line_parts) {
    try{
        map<string, string> input = process_command(line_parts);
        if(input["film_id"] != "") 
            see_details(line_parts);
        else {
            string name = input["name"];
            string director = input["director"];
            int min_year;
            int max_year;
            int min_rate;
            int price;
            input["min_year"] != "" && is_number(input["min_year"]) ? min_year = stoi(input["min_year"]) : min_year = -1;
            input["max_year"] != "" && is_number(input["max_year"]) ? max_year = stoi(input["max_year"]) : max_year = -1;
            input["min_rate"] != "" && is_number(input["min_rate"]) ? min_rate = stoi(input["min_rate"]) : min_rate = -1;
            input["price"] != "" && is_number(input["price"]) ? price = stoi(input["price"]) : price = -1;
            manager->search_films(name, min_year, max_year, min_rate, price, director);
        }
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::buy_film(vector<string> line_parts) {
    try{
        map<string, string> input = process_command(line_parts);
        int film_id;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        manager->buy_film(film_id);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::see_purchased_films(vector<string> line_parts) {
    try{
        map<string, string> input = process_command(line_parts);
        string name = input["name"];
        string director = input["director"];
        int min_year;
        int max_year;
        int min_rate;
        int price;
        input["min_year"] != "" && is_number(input["min_year"]) ? min_year = stoi(input["min_year"]) : min_year = -1;
        input["max_year"] != "" && is_number(input["max_year"]) ? max_year = stoi(input["max_year"]) : max_year = -1;
        input["min_rate"] != "" && is_number(input["min_rate"]) ? min_rate = stoi(input["min_rate"]) : min_rate = -1;
        input["price"] != "" && is_number(input["price"]) ? price = stoi(input["price"]) : price = -1;
        manager->see_purchased_films(name, min_year, max_year, min_rate, price, director);
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::rate_film(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        int film_id;
        int score;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        input["score"] != "" && is_number(input["score"]) ? score = stoi(input["score"]) : throw BadRequest();
        manager->rate_film(film_id, score);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::send_comment(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        int film_id;
        string content;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        input["content"] != "" ? content = input["content"] : throw BadRequest();
        manager->send_comment(film_id, content);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::reply_comment(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        int film_id;
        int comment_id;
        string content;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        input["comment_id"] != "" && is_number(input["comment_id"]) ? comment_id = stoi(input["comment_id"]) : throw BadRequest();
        input["content"] != "" ? content = input["content"] : throw BadRequest();
        manager->reply_comment(film_id, comment_id, content);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::delete_comment(vector<string> line_parts) {
    try { 
        map<string, string> input = process_command(line_parts);
        int film_id;
        int comment_id;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        input["comment_id"] != "" && is_number(input["comment_id"]) ? comment_id = stoi(input["comment_id"]) : throw BadRequest();
        manager->delete_comment(film_id, comment_id);
        cout << DONE_MASSAGE << endl;
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::see_details(vector<string> line_parts) {
    try {
        map<string, string> input = process_command(line_parts);
        int film_id;
        input["film_id"] != "" && is_number(input["film_id"]) ? film_id = stoi(input["film_id"]) : throw BadRequest();
        manager->see_details(film_id);
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::see_notifs(vector<string> line_parts) {
    if(line_parts.size() == 2 || line_parts.size() == 3)
        manager->see_notifs();
    else {
        try{
            map<string, string> input = process_command(line_parts);
            int limit;
            input["limit"] != "" && is_number(input["limit"]) ? limit = stoi(input["limit"]) : throw BadRequest();
            manager->read_notifs(limit);
        }
        catch(exception& ex) {
            cout << ex.what() << endl;
        }
    }
}

void In_out_handler::logout() {
    try {
        manager->logout();
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::see_money() {
    try {
        manager->see_money();
    }
    catch(exception& ex) {
        cout << ex.what() << endl;
    }
}

void In_out_handler::free() {
    manager->free();
}

void In_out_handler::input_reader() {
    string line;
    while( getline(cin, line) ) {
        vector<string> line_parts = get_command(line);
        if(line_parts.empty()) continue;
        string command = line_parts[0];
        if( command == "POST" ) {
            string action = line_parts[1];
            if( action == "signup" ) signup(line_parts);
            else if( action == "login" ) login(line_parts);
            else if( action == "films" ) post_film(line_parts);
            else if( action == "followers" ) follow_publisher(line_parts);
            else if( action == "money" ) post_money(line_parts);
            else if( action == "buy" ) buy_film(line_parts);
            else if( action == "rate" ) rate_film(line_parts); 
            else if( action == "comments" ) send_comment(line_parts);
            else if( action == "replies" ) reply_comment(line_parts);
            else if( action == "put_films" ) edit_film(line_parts);
            else if( action == "delete_films" ) delete_film(line_parts);
            else if( action == "dlete_comments" ) delete_comment(line_parts);
            else if( action == "logout") logout();
            else cout << "Not Found" << endl;        
        }
        // else if( command == "PUT" ) {
        //     string action = line_parts[1];
        //     //if( action == "films" ) edit_film(line_parts);
        //     else cout << "Not Found" << endl;        
        // }
        // else if( command == "DELETE" ) {
        //     string action = line_parts[1];
        //     //if( action == "films" ) delete_film(line_parts);
        //     //if( action == "comments" ) delete_comment(line_parts);
        //     else cout << "Not Found" << endl;        
        // }
        else if( command == "GET" ) {
            string action = line_parts[1];
            if( action == "published" ) get_published_films(line_parts);
            else if( action == "followers" ) see_followers(line_parts);
            else if( action == "films" ) search_films(line_parts);
            else if( action == "purchased" ) see_purchased_films(line_parts);
            else if( action == "notifications" ) see_notifs(line_parts);
            else if( action == "get money" ) see_money();
            else cout << "Not Found" << endl;        
        }
        else cout << "Bad Request" << endl;
    }
}