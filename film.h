#ifndef FILM_H_
#define FILM_H_

#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Film {
public:
    Film(int _id, std::string _name, int _year, int _length, std::string _summary, std::string _director);
    int get_id();
    std::string get_name();
    double get_rate();
    int get_length();
    int get_year();
    int get_price();
    std::string get_summary();
    std::string get_director();
    void edit_film(std::string name, int year, int length, int price, std::string summary, std::string director);
    friend std::ostream& operator<<(std::ostream& out, Film* film);
private:
    int id;
    std::string name;
    double rate;
    int year;
    int length;
    int price;
    std::string director;
    std::string summary;
};

std::vector<Film*> search(std::string name, int min_year, int max_year, int min_rate, int price,  std::string director, std::vector<Film*> input);

#endif