#ifndef REC_H_
#define REC_H_

#include <vector>
#include <utility>
#include <map>
#include "film.h"

class Recommandator {
public:
    void add_film(Film* film);
    void delete_film(Film* film);
    void buy_film(Film* purchased, std::vector<Film*> also_purchased);
    std::vector<Film*> get_recommandations(Film* film); 
private:
    std::vector< std::vector< std::pair<bool, int> > > films_adj_matrix;
    std::map<int, Film*> films;
};

#endif