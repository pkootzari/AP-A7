#include "recommandator.h"

using namespace std;

void Recommandator::add_film() {
    for(int i = 0; i < adj_matrix.size(); i++)
        adj_matrix[i].push_back(0);
    adj_matrix.push_back( vector<int>(adj_matrix.size() + 1, 0) );
}

void Recommandator::buy_film(int film_id, vector<int> also_purchased) {
    for(int i = 0; i < also_purchased.size(); i++) {
        adj_matrix[film_id - 1][also_purchased[i] - 1]++;
        adj_matrix[also_purchased[i] - 1][film_id - 1]++;
    }
}

void print(vector< pair<int , int> > unsorted_list) {
    for(int i = 0; i < unsorted_list.size(); i++)
        cout << unsorted_list[i].first << ":" << unsorted_list[i].second << "  ";
    cout << endl;
}

vector<int> Recommandator::recommand_list(int film_id) {
    vector<int> return_value;
    vector< pair<int , int> > unsorted_list;
    for(int i = 0; i < adj_matrix[film_id - 1].size(); i++)
        unsorted_list.push_back( make_pair(adj_matrix[film_id - 1][i], i + 1) );
    //print(unsorted_list);
    sort(unsorted_list);
    //print(unsorted_list);
    for(int i = 0; i < unsorted_list.size(); i++)
        return_value.push_back(unsorted_list[i].second);
    return return_value;
}

void Recommandator::print_matirx() {
    for(int i = 0; i < adj_matrix.size(); i++) {
        for(int j = 0; j < adj_matrix[i].size(); j++)
            cout << adj_matrix[i][j] << "  ";
        cout << endl;
    }
}

void sort(vector< pair<int , int> >& unsorted_list) {
    for(int i = 0; i < unsorted_list.size(); i++) {
        pair<int , int> max = unsorted_list[i];
        int pos = i;
        for(int j = i; j < unsorted_list.size(); j++) {
            if(unsorted_list[j].first > max.first) {
                max = unsorted_list[j];
                pos = j;
            }
        }
        iter_swap(unsorted_list.begin() + i, unsorted_list.begin() + pos);
    }
}