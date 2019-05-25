#include "recommandator.h"

using namespace std;

void Recommandator::add_film(Film* film) {
    int size = films_adj_matrix.size();
    for(int i = 0; i < size; i++) 
        films_adj_matrix[i].push_back( make_pair(true, 0) );
    films_adj_matrix.push_back( vector< pair<bool , int> >(size + 1, make_pair(true, 0)) );
    films[film->get_id()] = film;
}

void Recommandator::buy_film(Film* purchased, vector<Film*> also_purchased) {
    int film_id = purchased->get_id();
    for(int i = 0; i < also_purchased.size(); i++) {
        films_adj_matrix[film_id - 1][also_purchased[i]->get_id() - 1].second++;
        films_adj_matrix[also_purchased[i]->get_id() - 1][film_id - 1].second++;
    }
}

void Recommandator::delete_film(Film* film) {
    int film_id = film->get_id();
    for(int  i = 0; i < films_adj_matrix.size(); i++) {
        films_adj_matrix[film_id - 1][i].first = false;
        films_adj_matrix[i][film_id - 1].first = false;
    }
}

vector<Film*> Recommandator::get_recommandations(Film* film, vector<Film*> also_purchased) {
    vector<Film*> return_value;
    vector< vector< pair<bool, int> > > temp = films_adj_matrix;
    int film_id = film->get_id(); 
    for(int i = 0; i < temp[film_id - 1].size(); i++) {
        int max_weight = 0;
        Film* cur = films[i + 1];
        for(int j = i; j < temp[film_id - 1].size(); j++) 
            if(temp[film_id - 1][i].first == true) {
                if(temp[film_id - 1][j].second > max_weight) {
                max_weight = temp[film_id - 1][j].second;
                cur = films[j + 1];
                }
                else if(temp[film_id - 1][j].second == max_weight) {
                    if(cur->get_id() > films[j + 1]->get_id())
                        cur = films[j + 1];
                }
            }
        temp[film_id - 1][cur->get_id() - 1].first = false;
        return_value.push_back(cur);
    }
    return return_value;
}