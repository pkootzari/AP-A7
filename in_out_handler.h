#ifndef IN_OUT_HANDLER_H_
#define IN_OUT_HANDLER_H_

#include <string>
#include <iostream>
#include <sstream>
#include "manager.h"

#define DONE_MASSAGE "OK"

class In_out_handler {
public:
    In_out_handler();
    void input_reader();
    void signup(std::vector<std::string> line_parts);
    void login(std::vector<std::string> line_parts);
    void post_film(std::vector<std::string> line_parts);
    void edit_film(std::vector<std::string> line_parts);
    void delete_film(std::vector<std::string> line_parts);
    void get_published_films(std::vector<std::string> line_parts);
    void follow_publisher(std::vector<std::string> line_parts);
    void see_followers(std::vector<std::string> line_parts);
    void post_money(std::vector<std::string> line_parts);
    void search_films(std::vector<std::string> line_parts);
    void buy_film(std::vector<std::string> line_parts);
    void see_purchased_films(std::vector<std::string> line_parts);
    friend std::vector<std::string> get_command(std::string input);
private:
    Manager* manager;
};

#endif