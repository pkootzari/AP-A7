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
    void edit_film(std::string name, int year, int length, int price, std::string summary, std::string director);
private:
    int id;
    std::string name;
    double rate;
    int year;
    int length;
    int price;
    std::string summary;
    std::string director;
};

#endif