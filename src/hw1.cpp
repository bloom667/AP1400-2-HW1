#include "hw1.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <ctime>
#include <iomanip>
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

    Matrix random(size_t n, size_t m, double min, double max){
        if(m <=0 || n <= 0){
            throw logic_error("invalid row or col");
        }
        if(min > max){
            throw logic_error("invalid scale");
        }
        uniform_real_distribution<double> u(min, max);
        default_random_engine e(time(NULL));
        Matrix x;
        for(int i = 0; i < n; i++){
            vector<double> col;
            for(int j = 0; j < m; j++){
                col.push_back(u(e));
            }
            x.push_back(col);
        }
        return x;
    }
    void show(const Matrix& matrix){
        for(const auto& row: matrix){
            for(const auto& x: row){
                cout<< fixed<< setprecision(3)<<x<<" ";
            }
            cout<<endl;
        }
    }


}