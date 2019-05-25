#ifndef IN_OUT_HANDLER_H_
#define IN_OUT_HANDLER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <regex>
#include <unordered_map>
#include "exeptions.h"
#include "manager.h"

#define DONE_MASSAGE "OK"

class In_out_handler {
public:
    In_out_handler();
    std::map<std::string, std::string> process_command(std::vector<std::string> line_parts);
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
    void rate_film(std::vector<std::string> line_parts);
    void send_comment(std::vector<std::string> line_parts);
    void reply_comment(std::vector<std::string> line_parts);
    void delete_comment(std::vector<std::string> line_parts);
    void see_details(std::vector<std::string> line_parts);
    void see_notifs(std::vector<std::string> line_parts);
    void logout();
    void free();
    friend std::vector<std::string> get_command(std::string input);
private:
    Manager* manager;
};

#endif