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

    Matrix multiply(const Matrix& matrix, double c){
        Matrix res;
        for(const auto& row: matrix){
            vector<double> rows;
            for(const auto& x: row){
                double temp = x*c;
                rows.push_back(temp);
            }
            res.push_back(rows);
        }
        return res;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2){
        int row1 = matrix1.size();
        int col1 = matrix1[0].size();
        int row2 = matrix2.size();
        int col2 = matrix2[0].size();
        if(col1 != row2){
            throw logic_error("invalid matrix format");
        }
        Matrix res;
        for(int k = 0; k < row1; k++){
            vector<double> rows;
            for(int i = 0; i < col2; i++){
                double sum = 0;
                for(int j = 0; j < col1; j++){
                    double element = matrix1[k][j]*matrix2[j][i];
                    sum += element;
                }
                rows.push_back(sum);
            }
            res.push_back(rows);
        }
        return res;
    }

    Matrix sum(const Matrix& matrix, double c){
        Matrix res;
        for(const auto& row: matrix){
            vector<double> rows;
            for(const auto& x: row){
                double temp = x+c;
                rows.push_back(temp);
            }
            res.push_back(rows);
        }
        return res;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2){
        int row1 = matrix1.size();
        int col1 = matrix1[0].size();
        int row2 = matrix2.size();
        int col2 = matrix2[0].size();
        if(row1 != row2 && col1 != col2){
            throw logic_error("invalid matrix format");
        }
        Matrix res;
        for(int k = 0; k < row1; k++){
            vector<double> rows;
            for(int i = 0; i < col1; i++){
                double sum = matrix1[k][i] + matrix2[k][i];
                rows.push_back(sum);
            }
            res.push_back(rows);
        }
        return res;
    }

}