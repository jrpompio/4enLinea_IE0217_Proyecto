#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
using namespace std;

class Matrix6x7 {
protected:
    vector<vector<int>> table;
    vector<int> path;
    const int maxR = 6 - 1;
    const int maxC = 7 - 1;
public:
    Matrix6x7();
    void fill();
    const vector<vector<int>>& get_table() const;
    bool insert(int col, int player);
    int gravity(int col);
    bool explore(int R, int C, int dR, int dC);
    bool exploreDirections(int col);
};

#endif // MATRIX_H
