
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

std::ostream& operator<<(std::ostream& os, const algebra::Matrix& matrix) {
    for (const auto& row : matrix) {
        for (const auto& val : row) {
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // debug section
        algebra::Matrix a = algebra::random(3, 3, 2.34, 4.56);
        algebra::show(a);
        algebra::Matrix b = algebra::random(3, 3, 2.34, 4.56);
        algebra::show(b);
        algebra::Matrix c = algebra::concatenate(a,b,1);
        algebra::Matrix d = algebra::concatenate(a,b,0);
        std::cout << c << std::endl;
        std::cout << d << std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}