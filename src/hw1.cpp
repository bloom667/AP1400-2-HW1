#include "hw1.h"
#include <iostream>
#include <stdexcept>
using namespace std;

namespace algebra{
    Matrix createMatrix(size_t n, size_t m, double v){
        if (m <= 0 || n <= 0){
            throw logic_error("invalid row or col");
        }
        Matrix x;
        for(int i = 0; i < n; i++){
            vector<double> col(m,v);
            x.push_back(col);
        }
        return x;
    }

    Matrix zeros(size_t n, size_t m){
        return createMatrix(n, m, 0);
    }

    Matrix ones(size_t n, size_t m){
        return createMatrix(n, m, 1);
    }


}