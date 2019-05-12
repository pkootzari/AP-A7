#ifndef FILM_H_
#define FILM_H_

#include <string>
#include <vector>
#include <utility>

class Film {
public:
    Film();
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