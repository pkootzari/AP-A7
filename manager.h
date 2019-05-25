#ifndef MANAGER_H_
#define MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "user.h"
#include "publisher.h"
#include "customer.h"
#include "film.h"
#include "comment.h"
#include "exeptions.h"

class Manager {
public:
    Manager();
    void add_publisher(std::string email, std::string username, std::string password, int age);
    void add_customer(std::string email, std::string username, std::string password, int age);
    void login(std::string username, std::string password);
    void add_film(std::string name, int year, int length, int price, std::string summary, std::string director);
    void edit_film(int film_id, std::string name, int year, int length, int price, std::string summary, std::string director);
    void delete_film(int film_id);
    void get_published_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director);
    void follow_publisher(int user_id);
    void see_followers();
    void post_money(int amount);
    void search_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director);
    void buy_film(int film_id);
    void see_purchased_films(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director);
    void rate_film(int film_id, int score);
    void send_comment(int film_id, std::string content);
    void reply_comment(int film_id, int comment_id, std::string content);
    void delete_comment(int film_id, int comment_id);
    void see_details(int film_id);
    void print_recommandations(Film* except_this);
    void see_notifs();
    void read_notifs(int limit);
    bool if_id_exist(int id);
    void see_money();
    void logout();
    void free();
    void sort_film_by_id(std::vector<Film*>& input);
    void sort_user_by_id(std::vector<User*>& input);
private:
    int id_film;
    int id_user;
    int id_comment;
    User* cur_user;
    std::vector<User*> users;
    std::vector<Film*> films;
    std::vector<Comment*> commnets;
};

void print_film_details(Film* film);

#endif