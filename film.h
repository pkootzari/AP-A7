#ifndef FILM_H_
#define FILM_H_

#include <string>
#include <vector>
#include <utility>

class Film {
public:
    Film(int _id, std::string _name, int _year, int _lenght, std::string _summary, std::string _director);
private:
    int id;
    std::string name;
    double rate;
    int year;
    int lenght;
    int price;
    std::string summary;
    std::string director;
};

#endif