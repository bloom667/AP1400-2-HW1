#include "hw1.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <ctime>
#include <iomanip>
#include <cmath>
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

    Matrix transpose(const Matrix& matrix){
        int row = matrix.size();
        int col = matrix[0].size();
        Matrix res;
        for(int i = 0; i < col; i++){
            vector<double> rows;
            for (int j = 0; j < row; j ++){
                rows.push_back(matrix[j][i]);
            }
            res.push_back(rows);
        }
        return res;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m){
        int row = matrix.size();
        int col = matrix[0].size();
        Matrix res;
        for(int i = 0; i < row; i++){
            if(i == n) continue;
            vector<double> rows;
            for (int j = 0; j < col; j ++){
                if(j == m) continue;
                rows.push_back(matrix[i][j]);
            }
            res.push_back(rows);
        }
        return res;
    }

    double determinant(const Matrix& matrix){
        int row = matrix.size();
        int col = matrix[0].size();
        if(row != col){
            throw logic_error("invalid matrix format");
        }
        if(row == 1){
            return matrix[0][0];
        }

        if(row == 2){
            return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
        }

        double res = 0;
        for(int i = 0; i < row; i++){
            Matrix minor = algebra::minor(matrix, 0, i);
            double minorDet = algebra::determinant(minor);
            res += (i%2 == 0? 1: -1)*matrix[0][i]*minorDet; 
        }
        return res;
    }

    Matrix augmented(const Matrix& matrix){
        int row = matrix.size();
        int col = matrix[0].size();
        if(row != col){
            throw logic_error("invalid matrix format");
        }
        Matrix res = matrix;
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(j == i) res[i].push_back(1.0);
                else res[i].push_back(0.0);
            }
        }
        return res;
    }

    Matrix div_augmented(const Matrix& matrix){
        int row = matrix.size();
        int col = matrix[0].size();
        if(col != 2*row){
            throw logic_error("invalid matrix format");
        }
        Matrix res;
        for(int i = 0; i < row; i++){
            vector<double> rows;
            for(int j = row; j < col; j++){
                rows.push_back(matrix[i][j]);
            }
            res.push_back(rows);
        }
        return res;
    }

    Matrix inverse(const Matrix& matrix){
        int row = matrix.size();
        int col = matrix[0].size();
        Matrix augmented = algebra::augmented(matrix);
        for(int i = 0; i < row; i++){
            if(fabs(augmented[i][i]) < 1e-9){//交换行避免主元为0
                bool found = false;
                for(int j = i+1; j < row; j++){
                    if(fabs(augmented[j][i]) > 1e-9){
                        augmented[i].swap(augmented[j]);
                    }
                    found = true;
                    break;
                }
                if(!found){
                    throw logic_error("Matrix is singular and cannot be inverted");
                }
            }

            //主元所在行归一化处理
            double pivot = augmented[i][i];
            for(auto& val : augmented[i]){
                val /= pivot;
            }

            //将主元外的元素化为0
            for(int k = 0; k < row; k++){
                if (k == i) continue;
                double factor = augmented[k][i];
                for(int x = 0; x < 2*row; x++){
                    augmented[k][x] -= factor*augmented[i][x];
                }
            }
        }

        Matrix res = algebra::div_augmented(augmented);
        return res;
    }

}