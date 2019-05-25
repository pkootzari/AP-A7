#ifndef REC_H_
#define REC_H_

#include <vector>
#include "film.h"

class Recommandator {
public:
    void add_film();
    void delete_film();
    void buy_film();
    std::vector<Film*> get_recommandations(); 
private:
    std::vector< std::vector<Film*> > films_adj_matrix; 
};

#endif