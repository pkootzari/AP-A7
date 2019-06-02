#ifndef FILM_H_
#define FILM_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "exeptions.h"
#include "comment.h"

class User;

class Film {
public:
    Film(int _id, std::string _name, int _year, int _length, std::string _summary, std::string _director, int _price);
    int get_id();
    std::string get_name();
    double get_rate();
    int get_length();
    int get_year();
    int get_price();
    std::string get_summary();
    std::string get_director();
    void rate_this(int user_id, int score);
    void edit_film(std::string name, int year, int length, int price, std::string summary, std::string director);
    void add_comment(std::string content, User* user);
    void add_reply(std::string content, int comment_id);
    void delete_comment(int comment_id);
    void print_comments();
    User* get_comment_sender(int comment_id);
    friend std::ostream& operator<<(std::ostream& out, Film* film);
    friend void sort_by_rate(std::vector<Film*>& input);
private:
    int id;
    std::string name;
    double rate;
    int year;
    int length;
    int price;
    std::string director;
    std::string summary;
    std::vector< std::pair<int, int> > scores_given;
    int initial_comment_id;
    std::vector< std::pair<Comment*, User*> > commnets;
};

std::vector<Film*> search(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director, std::vector<Film*> input);

#endif