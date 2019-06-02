#ifndef REC_H_
#define REC_H_

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

class Recommandator {
public:
    void add_film();
    void buy_film(int film_id, std::vector<int> also_purchased);
    void print_matirx();
    std::vector<int> recommand_list(int film_id);
private:
    std::vector< std::vector<int> > adj_matrix;
};

void sort(std::vector< std::pair<int , int> >& unsorted_list);

#endif